#include "pch.h"
#include "grind.h"


//Most of the functions here are directly copied pasted from the disassembly from Sonic grinding, with few extra fixes.
int setGrindingNextAction(KnucklesCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {
	NJS_VECTOR result;
	int v8 = 0;
	float* v21;
	signed int v37 = 0;
	int a2a = 0;
	int v20 = 0;
	double v22 = 0.0;
	double v23 = 0.0;
	double v24 = 0.0;
	int v25 = 0;
	float v39 = 0.0;
	float v40 = 0.0;
	float v41 = 0.0;
	a4->Status = a4->Status & 0xFAFF | 0x2000;

	result = { 1, 0, 0 };

	v21 = (float*)nj_current_matrix_ptr_;
	if (nj_current_matrix_ptr_)
	{
		memset(nj_current_matrix_ptr_, v20, 0x30u);
		*v21 = 1.0;
		v21[5] = 1.0;
		v21[10] = 1.0;
	}
	if (v37)
	{
		njRotateZ(v21, v37);
	}
	if (a2a)
	{
		njRotateX(v21, a2a);
	}
	if (a4->Rotation.y)
	{
		njRotateY((float*)v21, -a4->Rotation.y);
	}
	njCalcPoint(&result, &result, v21);
	v39 = fabs(a3->Speed.y);
	if (a3->Speed.x < 0.0)
	{
		v24 = v39;
		v41 = fabs(result.y);
		v23 = a3->Speed.x - v24 * v41;
	}
	else
	{
		v22 = v39;
		v40 = fabs(result.y);
		v23 = v22 * v40 + a3->Speed.x;
	}
	a3->Speed.x = v23 + 1.0;
	a4->Action = Grinding;

	if (isCustomAnim && (a3->CharID2 == Characters_Knuckles || a3->CharID2 == Characters_Rouge)) {
		if ((double)rand() * 0.000030517578125 <= 0.5) {
			a3->AnimInfo.Next = Anm_RailFastL;
		}
		else {
			a3->AnimInfo.Next = Anm_RailL;
		}
	}
	else {
		a3->AnimInfo.Next = 9;
	}

	if (CurrentLevel == LevelIDs_GreenForest)
	{
		v25 = 6;
	}
	else
	{
		v25 = 2;
		if (CurrentLevel != LevelIDs_WhiteJungle)
		{
			v25 = 4103;
		}
	}
	Play3DSoundPosThing(v25, &a4->Position, 0, 0, 127);
	VibeThing(0, 15, a3->PlayerNum, 6); //Vibe thing
	sub_429000();
	v8 = 1;
	a3->Speed.y = 0.0;
	return 1;
}

void CheckGrindThing(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, KnucklesCharObj2* co2Knux) {
	if (Knux_CheckNextActions_r(data2, co2Knux, data1, co2)) {
		return;
	}

	if ((data1->Status & Status_OnPath) == 0) {
		co2->AnimInfo.Next = 15;
		data1->Action = 10; //SA2Action_LaunchJumpOrFalling
		co2->AnimInfo.Current = 15; //Falling
		data1->Status &= 0xDFFFu;
		return;
	}

	/*if (CheckTrickASM(co2Miles, co2, data1))
	{
		return;
	}*/

	if (data1->Status & Status_DisableControl || !Jump_Pressed[co2->PlayerNum] || !sub_45B2C0(co2, co2->PlayerNum, data1) || sub_45B2C0(co2, co2->PlayerNum, data1) > 3) {

		if (KnuxJump(data1, co2)) {
			data1->Status &= 0xDFFFu;
		}
		else if (co2->Speed.x > 0.8) {
			if (!Action_Held[co2->PlayerNum])
			{
				co2->ActionWindowItems[co2->ActionWindowItemCount++ & 7] = 71;
			}
		}
		else {
			if (co2->AnimInfo.Current == Anm_RailBalanceL) {
				data1->Rotation.y -= 0x4000;
			}
			else if (co2->AnimInfo.Current == Anm_RailBalanceR) {
				data1->Rotation.y += 0x4000;
			}

			data2->Forward.y = data1->Rotation.y;
			if (co2->PhysData.RunSpeed > co2->Speed.x) {
				co2->Speed.x = co2->PhysData.RunSpeed;
			}

			data1->Action = 10; //SA2Action_LaunchJumpOrFalling
			co2->AnimInfo.Current = 15; //Falling
			data1->Status &= 0xDFFFu;
		}

		return;
	}

	data1->Status &= 0xDFFFu;
	data1->Action = 10; //SA2Action_LaunchJumpOrFalling
	PlaySoundProbably(8193, 0, 0, 0);

	Angle analog_angle;
	Float analog_mag;

	GetAnalog(data1, co2, &analog_angle, &analog_mag);

	analog_mag *= njSin((analog_angle - LOWORD(data1->Rotation.y)));

	if (analog_mag < 0) {
		data1->Rotation.y = data1->Rotation.y - (12288.0 - njScalor(&co2->Speed) * 800.0);
	}
	else {
		data1->Rotation.y = 12288.0 - njScalor(&co2->Speed) * 800.0 + data1->Rotation.y;
	}
}



void MoveCharacterOnRail(EntityData1* a1, CharObj2Base* a2, EntityData2* a3) {
	sub_46D040(a1, a2, a3);
	if (a1->Action != HandGrinding)
		getRailAccel(a2, a1, a3);
	return;
}



void PowderExecute_Rails(KnucklesCharObj2* sco2, NJS_VECTOR* dir) {
	float idk = static_cast<float>(rand()) * 0.00003f * 3.0f;
	if (idk > 0.0f) {
		PowderExecute(dir, idk, (NJS_VECTOR*)&sco2->field_1BC[68], sco2->base.PlayerNum);
	}
}

void LoadRailParticules(KnucklesCharObj2* co2, EntityData2* data2) {
	if (fabs(co2->base.Speed.x) >= 3.7f) {
		NJS_VECTOR speed;
		speed.x = data2->Velocity.x * 0.9f;
		speed.y = data2->Velocity.y * 0.9f;
		speed.z = data2->Velocity.z * 0.9f;

		PowderExecute_Rails(co2, &speed);
		PowderExecute_Rails(co2, &speed);
		sub_754EC0(co2->base.PlayerNum);
	}
}

void RailAnim_ToNormal(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_RailCrouchL:
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		co2->AnimInfo.Next = Anm_RailL;
		break;
	case Anm_RailCrouchR:
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		co2->AnimInfo.Next = Anm_RailR;
		break;
	case Anm_RailFastCL:
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		co2->AnimInfo.Next = Anm_RailFastL;
		break;
	case Anm_RailFastCR:
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		co2->AnimInfo.Next = Anm_RailFastR;
		break;
	}
}

void RailAnim_ToCrouch(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_RailL:
		co2->AnimInfo.Next = Anm_RailCrouchL;
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		break;
	case Anm_RailR:
		co2->AnimInfo.Next = Anm_RailCrouchR;
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		break;
	case Anm_RailFastL:
		co2->AnimInfo.Next = Anm_RailFastCL;
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		break;
	case Anm_RailFastR:
		co2->AnimInfo.Next = Anm_RailFastCR;
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		break;
	}
}

void RailAnim_ToLeft(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_RailR:
	default:
		co2->AnimInfo.Next = Anm_RailL;
		break;
	case Anm_RailCrouchR:
		co2->AnimInfo.Next = Anm_RailCrouchL;
		break;
	case Anm_RailFastR:
		co2->AnimInfo.Next = Anm_RailFastL;
		break;
	case Anm_RailFastCR:
		co2->AnimInfo.Next = Anm_RailFastCL;
		break;
	}
}

void RailAnim_ToRight(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_RailL:
		co2->AnimInfo.Next = Anm_RailR;
		break;
	case Anm_RailCrouchL:
		co2->AnimInfo.Next = Anm_RailCrouchR;
		break;
	case Anm_RailFastL:
		co2->AnimInfo.Next = Anm_RailFastR;
		break;
	case Anm_RailFastCL:
		co2->AnimInfo.Next = Anm_RailFastCR;
		break;
	}
}

//SA2 hardcode all the grinding animations id
void PlayGrindAnimation(EntityData1* data1, CharObj2Base* co2) {
	if (isCustomAnim == false || data1->Action != Grinding || co2->AnimInfo.Next == 15 || co2->CharID2 != Characters_Knuckles && co2->CharID2 != Characters_Rouge) {
		return;
	}

	if (Action_Held[co2->PlayerNum] == 0) {
		RailAnim_ToNormal(co2);
	}
	else {
		RailAnim_ToCrouch(co2);
	}

	Angle analog_angle;
	Float analog_mag;

	GetAnalog(data1, co2, &analog_angle, &analog_mag);

	analog_mag *= njSin((analog_angle - LOWORD(data1->Rotation.y)));

	if (analog_mag < 0) {
		RailAnim_ToLeft(co2);
	}
	else {
		RailAnim_ToRight(co2);
	}
}



void CheckScoreTrick(EntityData1* data1, CharObj2Base* co2, EntityData2* data2, KnucklesCharObj2* KnuxCO2) {
	char getcharID2 = 0;
	int curSound = 0;
	int idk = 0;
	int idk2 = 0;
	int idk3 = 0;
	char idk4 = 0;
	ObjectMaster* dispScore;
	ObjUnknownB* idk5;
	char idk6;

	if (data1->NextAction != 0 || !(data1->Status & Status_OnPath))
		return;

	getcharID2 = co2->CharID2;

	if (getcharID2 == 8)
	{
		curSound = 8214;
	}
	else
	{
		curSound = 8218;
		if (getcharID2 != 12)
		{
			curSound = 8195;
		}
	}
	PlaySoundProbably(curSound, 0, 0, 0);
	if (PlayerCheckBreakMaybe(idk, data1, co2) && co2->Speed.x > 0.0)
	{
		data1->Action = 12;
		idk2 = 18;
		idk3 = 0;
		co2->AnimInfo.Next = 18;
		co2->AnimInfo.field_8 = 0;
	}
	else
	{
		if (CheckPlayerStopASM(data1, co2, data2))
		{
			data1->Rotation.x = data2->Forward.x;
			data1->Rotation.z = data2->Forward.z;
			if (njScalor((const NJS_VECTOR*)data2) >= (double)FLOAT_01283704)
			{
				if (njScalor((const NJS_VECTOR*)data2) >= 2.5)
				{
					co2->AnimInfo.Next = 17;
					VibeThing(0, 15, co2->PlayerNum, 6); //Vibe Thing
				}
				else
				{
					co2->AnimInfo.Next = 16;
				}
				idk3 = 0;
				data1->Action = 0;
				co2->IdleTime = 0;
			}
			else
			{
				co2->AnimInfo.Next = 1;
				idk3 = 0;
				data1->Action = 0;
				co2->IdleTime = 0;
			}
		}
		else
		{
			data1->Rotation.x = data2->Forward.x;
			data1->Rotation.z = data2->Forward.z;
			data1->Action = 1;
			somethingAboutTrick3(co2, data1);
		}
	}
	sub_4EC330(idk3, co2->PlayerNum, idk2);

	idk6 = KnuxCO2->field_400[1];
	if (!idk6)
	{
		DispTechniqueScore_Load(1000);
		return;
	}
	if (idk6 != 1)
	{
		//goto LABEL_241;
	}
	if (TwoPlayerMode)
	{
		return;
	}
	dispScore = AllocateObjectMaster(DispTechniqueScore_Main, 3, "DispTechniqueScore");
	if (!dispScore)
	{
		return;
	}
	idk5 = AllocateObjUnknownB();
	if (idk5)
	{
		//goto LABEL_240;
	}
	DeleteObject_(dispScore);
}

signed int SetHandGranding(EntityData2* data2, CharObj2Base* co2, EntityData1* data1) {
	NJS_VECTOR* vec = (NJS_VECTOR*)&co2->SomeVectors[4];

	data1->Status = data1->Status & 0xFAFF | Status_OnPath;

	NJS_VECTOR playerdir = { 1.0f, 0.0f, 0.0f };
	NJS_VECTOR playerup = { 0.0f, 1.0f, 0.0f };

	CalcVector_PlayerRot(data1, &playerdir);

	njPushUnitMatrix();
	njRotateZ(0, data1->Rotation.z);
	njRotateX(0, data1->Rotation.x);
	njCalcPoint_(&playerup, &playerup, 0);
	njPopMatrixEx();

	data1->Rotation.x = (asin(-playerup.z) * 10430.38043493439);
	data1->Rotation.z = (atan2f(-playerup.y, -playerup.x) * -10430.38043493439);

	njPushUnitMatrix();
	njRotateX(0, data1->Rotation.x);
	njRotateZ(0, data1->Rotation.z);
	njCalcPoint_(&playerdir, &playerup, 0);
	njPopMatrixEx();

	//data1->Rotation.y = (atan2f(playerup.x, playerup.z) * 10430.38043493439);
	data2->Forward.y = data1->Rotation.y;
	data1->Action = HandGrinding;
	if (isCustomAnim && (co2->CharID2 == Characters_Knuckles || co2->CharID2 == Characters_Rouge))
		co2->AnimInfo.Next = Anm_HandGrind;
	else
		co2->AnimInfo.Next = 75;
	co2->Speed.x += 2.3;
	co2->Speed.y = 0.0f;
	return 1;
}


static const void* const sub_7274F0Ptr = (void*)0x7274F0;
float* sub_7274F0(EntityData1* a1)
{
	float* result;
	__asm
	{
		mov eax, [a1] // eax0
		// Call your __cdecl function here:
		call sub_7274F0Ptr
		fstp result
	}
	return result;
}

void DoHandGrinding(EntityData1* data, CharObj2Base* co2) {
	if (data->NextAction != 0)
		return;

	int curStatus = data->Status;
	int curChar2 = co2->CharID2;
	int curSound = 0;

	if ((curStatus & 0x2000) != 0)
	{
		if ((data->Status & 0x4000) == 0 && Jump_Pressed[co2->PlayerNum])
		{
			data->Action = 10;
			data->Status = curStatus & 0xDFFF;

			if (curChar2 == 8)
			{
				curSound = 8212;
			}
			else if (curChar2 == 12)
			{
				curSound = 8215;
			}
			else
			{
				curSound = 8193;
				if (co2->CharID)
				{
					curSound = 0x2000;
				}
			}
			PlaySoundProbably(curSound, 0, 0, 0);
			if (co2->PhysData.RunSpeed > (double)co2->Speed.x)
			{
				co2->Speed.x = co2->PhysData.RunSpeed;
			}
			co2->AnimInfo.Next = 15;
			co2->Speed.y = -1.5;
			sub_7274F0(data);
		}
	}
	else
	{
		data->Action = 10;
		co2->AnimInfo.Next = 15;
		data->Status &= 0xDFFFu;
		sub_7274F0(data);
	}

	return;
}