#include "pch.h"

//Original Code by SonicFreak94, edited here to let the player change controls of the actions.

//We trampoline "ActionWindow" to take the control of it, since it's an usercall this as always need 3 functions to work.

Trampoline* Knux_CheckActionWindow_t;

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
		if (count != i || (action = co2->ActionWindowItems[0], CurrentLevel != LevelIDs_ChaoWorld) || action != 71 && action != 74 && action != 77)
		{
			co2->field_D[1] = action;
			switch (action)
			{
			case Action_Punch:

				if (!isSA2Punch)
					return 0;

				co2->field_D[1] = action;

				// Just nope right out of here if punch button isn't pressed.
				if (!(Controllers[pnum].press & SA2PunchButton))
				{
					return 0;
				}

				Knux_SetPunchAction(data1, co2, knuxCO2);
				return 1;

			case Action_Punch1Run:

				if (!isSA2Punch)
					return 0;

				co2->field_D[1] = action;

				// Just nope right out of here if punch button isn't pressed.
				if (!(Controllers[pnum].press & SA2PunchButton))
				{
					return 0;
				}


				if (isRoll && co2->Speed.x > 1.3 && SA2PunchButton == RollButton)
					return 0;

				Knux_SetPunchRunAction(data1, co2, knuxCO2);
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


void Init_ActionRemap() {

	if (SA2PunchButton == buttons_XB && isSA2Punch) //if vanilla input
		return;

	Knux_CheckActionWindow_t = new Trampoline((int)0x7338F0, (int)0x7338FB, Knuckles_CheckActionWindowASM);
}