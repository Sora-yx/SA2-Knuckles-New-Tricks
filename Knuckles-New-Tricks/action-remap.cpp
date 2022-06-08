#include "pch.h"

//Original Code by SonicFreak94, edited here to let the player change controls of the actions.

//We trampoline "ActionWindow" to take the control of it, since it's an usercall, this as always need 3 functions to work.

Trampoline* Knux_CheckActionWindow_t = nullptr;
Trampoline* Knux_PunchManagement_t = nullptr;

signed int Knuckles_CheckActionWindow_Origin(CharObj2Base* co2, EntityData2* data2, EntityData1* data1, KnucklesCharObj2* knuxCO2)
{
	auto target = Knux_CheckActionWindow_t->Target();

	int result;
	__asm
	{
		push[knuxCO2]
		push[data1]
		mov edx, [data2]
		mov eax, [co2]
		call target
		add esp, 8
		mov result, eax
	}
	return result;
}

static signed int Knuckles_CheckActionWindow_r(CharObj2Base* co2, EntityData2* data2, EntityData1* data1, KnucklesCharObj2* knuxCO2)
{
	// This code is based on the pseudocode of the original function

	int  pnum = co2->PlayerNum;
	char action = co2->field_D[0];
	int  count = co2->ActionWindowItemCount;
	int  i = 0;

	count = co2->ActionWindowItemCount;

	if (co2->ActionWindowItemCount)
	{
		i = 0;
		if (count > 0)
		{
			do
			{
				if (co2->field_D[0] == co2->ActionWindowItems[i])
				{
					break;
				}
				i++;
			} while (i < count);
			action = co2->field_D[0];
		}
		if (count != i || (action = co2->ActionWindowItems[0], CurrentLevel != LevelIDs_ChaoWorld) || action != Action_Punch && action != Action_Punch1Run && action != Action_SpiralUpper)
		{
			switch (action)
			{
			case Action_Punch:
			{
				co2->field_D[1] = action;

				// Just nope right out of here if punch button isn't pressed.
				if (!(Controllers[pnum].press & SA2PunchButton))
				{
					return 0;
				}

				Knux_SetPunchAction(data1, co2, knuxCO2);
			}
			return 1;

			case Action_Punch1Run:
			{
				co2->field_D[1] = action;

				// Just nope right out of here if punch button isn't pressed.
				if ((Controllers[pnum].press & SA2PunchButton) == 0)
				{
					return 0;
				}

				if (isRoll && co2->Speed.x > 1.3 && SA2PunchButton == RollButton)
					return 0;

				Knux_SetPunchRunAction(data1, co2, knuxCO2);
			}
			return 1;
			}
		}
	}

	// If all those conditions fail, let the original code handle it.
	return Knuckles_CheckActionWindow_Origin(co2, data2, data1, knuxCO2);
}

static void __declspec(naked) Knuckles_CheckActionWindowASM()
{
	__asm
	{
		push[esp + 08h] // knuxCO2
		push[esp + 08h] // data1
		push edx // data2
		push eax // co2

		// Call your __cdecl function here:
		call Knuckles_CheckActionWindow_r

		add esp, 4 // co2<eax> is also used for return value
		pop edx // data2
		add esp, 4 // data1
		add esp, 4 // knuxCO2
		retn
	}
}

void Knux_InputCheckPunchRefresh(int pID, char action, KnucklesCharObj2* knuxCo2) {

	if ((Controllers[pID].press & SA2PunchButton))
	{
		knuxCo2->field_1BC[413] = action;
	}
	else if (((Controllers[pID].on & SA2PunchButton) == 0) && knuxCo2->field_1BC[413] != action)
	{
		knuxCo2->field_1BC[413] = Action_Run;
	}
}

//Hack to customise punch button, this is based on ida's pseudcode.

signed int Knux_PunchManagement_r(EntityData1* data, KnucklesCharObj2* knuxCo2, CharObj2Base* co2)
{

	__int16 FieldCopy; // dx
	int pID; // eax
	int soundID; // esi
	int vibeID; // eax
	signed int result; // eax
	int Sound3DID; // al
	int Sound3DID3;
	char AltCostume; // al
	NJS_VECTOR* PlayerPos; // esi
	bool isActionHeld; // zf
	bool isSpeed;
	int VibeID2; // [esp-4h] [ebp-14h]

	char action = data->Action;
	if (action != Action_Punch3 && action != Action_Punch3Run && ((data->Status & (Status_OnObjectColli | Status_Ground)) == 0
		|| (data->Status & Status_HoldObject) != 0 || action == Action_DrillClaw))
	{
		return 0;
	}

	FieldCopy = ++*(WORD*)&knuxCo2->field_1BC[484];
	switch (data->Action)
	{
	case Action_Punch:
		pID = co2->PlayerNum;

		Knux_InputCheckPunchRefresh(pID, (char)Action_Punch2, knuxCo2);

		if ((co2->AnimInfo.field_C & 1) == 0)
		{
			return 0;
		}

		data->Action = knuxCo2->field_1BC[413];

		if (data->Action == Action_Run)
		{
			KnuxResetActionAnim(co2, data, knuxCo2);
			return 1;
		}
		knuxCo2->field_1BC[413] = Action_Run;
		*(WORD*)&knuxCo2->field_1BC[484] = Action_None;
		if (co2->CharID2 == Characters_Chaos)
		{
			soundID = 8217;
		}
		soundID = 8203;
		if (co2->CharID != Characters_Knuckles)
		{
			soundID = 8205;
		}

		PlaySoundProbably(soundID, 0, 0, 0);
		VibeID2 = 6;
		vibeID = 0;
		VibeThing(vibeID, 30, co2->PlayerNum, VibeID2);
		result = 1;
		break;
	case Action_Punch2:
		pID = co2->PlayerNum;

		Knux_InputCheckPunchRefresh(pID, (char)Action_Punch3, knuxCo2);

		if ((co2->AnimInfo.field_C & 2) == 0)
		{
			return 0;
		}

		data->Action = knuxCo2->field_1BC[413];
		if (data->Action != Action_Punch3)
		{
			KnuxResetActionAnim(co2, data, knuxCo2);
			return 1;
		}
		knuxCo2->field_1BC[413] = Action_Run;
		*(WORD*)&knuxCo2->field_1BC[484] = Action_None;
		co2->Speed.y = 2.4000001f;
		if (co2->CharID2 == Characters_Chaos)
		{
			PlaySoundProbably(8218, 0, 0, 0);
			VibeThing(1, 15, co2->PlayerNum, 3);
			result = 1;
			break;
		}
		if (co2->CharID == Characters_Knuckles)
		{
			PlaySoundProbably(8204, 0, 0, 0);
			AltCostume = co2->CharID2;
			if (AltCostume == Characters_Knuckles)
			{
				PlayerPos = &data->Position;
				Sound3DID3 = 12295;
			}
			else
			{
				if (AltCostume != Characters_Tikal)
				{
					VibeThing(1, 15, co2->PlayerNum, 3);
					result = 1;
					break;
				}
				PlayerPos = &data->Position;
				Sound3DID3 = 12324;
			}
		}
		else
		{
			PlaySoundProbably(8206, 0, 0, 0);
			if (co2->CharID2 != Characters_Rouge)
			{
				VibeThing(1, 15, co2->PlayerNum, 3);
				result = 1;
				break;
			}
			PlayerPos = &data->Position;
			Sound3DID3 = 12312;
		}
		Play3DSound_Pos(Sound3DID3, PlayerPos, 0, 0, 127);
		//LABEL_65:
		VibeThing(1, 15, co2->PlayerNum, 3);
		result = 1;
		break;
	case Action_Punch3:
		isSpeed = co2->Speed.y <= 0.0;
		if (!isSpeed)
		{
			return 0;
		}
		KnuxResetActionAnim(co2, data, knuxCo2);
		return 1;
	case Action_Punch1Run:
		pID = co2->PlayerNum;

		Knux_InputCheckPunchRefresh(pID, (char)Action_Punch2Run, knuxCo2);

		if ((co2->AnimInfo.field_C & 1) == 0)
		{
			return 0;
		}

		data->Action = knuxCo2->field_1BC[413];
		if (data->Action == Action_Run)
		{
			KnuxResetActionAnim(co2, data, knuxCo2);
			return 1;
		}
		knuxCo2->field_1BC[413] = Action_Run;
		*(WORD*)&knuxCo2->field_1BC[484] = Action_None;
		if (co2->CharID2 == Characters_Chaos)
		{
			soundID = 8217;
		}
		else
		{
			soundID = 8203;
			if (co2->CharID != Characters_Knuckles)
			{
				soundID = 8205;
			}
		}
		PlaySoundProbably(soundID, 0, 0, 0);
		VibeID2 = 6;
		vibeID = 0;
		VibeThing(vibeID, 30, co2->PlayerNum, VibeID2);
		result = 1;
		break;
	case Action_Punch2Run:
		pID = co2->PlayerNum;

		Knux_InputCheckPunchRefresh(pID, (char)Action_Punch3Run, knuxCo2);

		if ((co2->AnimInfo.field_C & 2) == 0)
		{
			return 0;
		}
		data->Action = knuxCo2->field_1BC[413];
		if (data->Action != Action_Punch3Run)
		{
			KnuxResetActionAnim(co2, data, knuxCo2);
			return 1;
		}
		knuxCo2->field_1BC[413] = Action_Run;
		*(WORD*)&knuxCo2->field_1BC[484] = Action_None;
		if (co2->CharID2 == Characters_Chaos)
		{
			PlaySoundProbably(8217, 0, 0, 0);
			VibeID2 = 4;
			vibeID = 1;
			VibeThing(vibeID, 30, co2->PlayerNum, VibeID2);
			result = 1;
		}
		if (co2->CharID == Characters_Knuckles)
		{
			PlaySoundProbably(8204, 0, 0, 0);
			AltCostume = co2->CharID2;
			if (AltCostume == Characters_Knuckles)
			{
				PlayerPos = &data->Position;
				Sound3DID = 12295;
			}
			else
			{
				if (AltCostume != Characters_Tikal)
				{
					VibeID2 = 4;
					vibeID = 1;
					VibeThing(vibeID, 30, co2->PlayerNum, VibeID2);
					result = 1;
					break;
				}
				PlayerPos = &data->Position;
				Sound3DID = 12324;
			}
		}
		else
		{
			PlaySoundProbably(8206, 0, 0, 0);
			if (co2->CharID2 != Characters_Rouge)
			{
				VibeID2 = 4;
				vibeID = 1;
				VibeThing(vibeID, 30, co2->PlayerNum, VibeID2);
				result = 1;
				break;
			}
			PlayerPos = &data->Position;
			Sound3DID = 12312;
		}
		Play3DSound_Pos(Sound3DID, PlayerPos, 0, 0, 127);
		//LABEL_47:
		VibeID2 = 4;
		vibeID = 1;
		VibeThing(vibeID, 30, co2->PlayerNum, VibeID2);
		result = 1;
		break;
	case Action_Punch3Run:
		if (FieldCopy > 40)
		{
			KnuxResetActionAnim(co2, data, knuxCo2);
			return 1;
		}
		if (FieldCopy <= 10)
		{
			return 0;
		}
		pID = co2->PlayerNum;
		isActionHeld = ((Controllers[pID].on & SA2PunchButton)) == 0;

		if (!isActionHeld)
		{
			return 0;
		}
		KnuxResetActionAnim(co2, data, knuxCo2);
		return 1;
	default:
		return 0;
	}
	return result;
}

static void __declspec(naked) Knux_PunchManagementASM()
{
	__asm
	{
		push[esp + 04h] // a3
		push ecx // a2
		push eax // a1

		// Call your __cdecl function here:
		call Knux_PunchManagement_r

		add esp, 4 // a1<eax> is also used for return value
		pop ecx // a2
		add esp, 4 // a3
		retn
	}
}


void Init_ActionRemap() {

	if (SA2PunchButton == buttons_XB)  //if vanilla input
		return;

	Knux_CheckActionWindow_t = new Trampoline((int)0x7338F0, (int)0x7338FB, Knuckles_CheckActionWindowASM);
	Knux_PunchManagement_t = new Trampoline((int)0x734AA0, (int)0x734AA6, Knux_PunchManagementASM);
}