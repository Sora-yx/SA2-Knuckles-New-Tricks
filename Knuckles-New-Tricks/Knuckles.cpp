#include "pch.h"
#include "grind.h"
#include "punch.h"
#include "roll.h"

Trampoline* Knux_Main_t;
Trampoline* Knux_CheckNextActions_t;
Trampoline* Knux_RunsAction_t;


//Trampoline Usercall Function to get the control of "Check Next Actions" this need 3 functions to work.

int Knux_CheckNextActions_original(EntityData2* a1, KnucklesCharObj2* a2, EntityData1* a3, CharObj2Base* a4) {
	const auto KnuxCheck_ptr = Knux_CheckNextActions_t->Target();

	signed int result;

	__asm
	{
		push[a4] // a4
		mov ebx, a3 // a3
		mov ecx, a2 // a2
		mov edx, a1 // a1

		// Call your __cdecl function here:
		call KnuxCheck_ptr
		add esp, 4
		mov result, eax
	}

	return result;
}

signed int __cdecl Knux_CheckNextActions_r(EntityData2* a1, KnucklesCharObj2* a2, EntityData1* a3, CharObj2Base* a4) {


	switch (a3->NextAction)
	{
	case 1:
		if (CurrentLevel == LevelIDs_RadicalHighway)
			a3->Action = 1; //fix softlock last loop
		else
			a3->Action = 2;
		break;
	case 3:
		if (a3->Action == Action_SA1Rolling)
		{
			a3->Action = 1;
			a4->AnimInfo.Next = 1;
			a3->Status &= 0xFAFFu;
			return 1;
		}
		if (a3->Action != Grinding)
		{
			return 1;
		}
		a3->Action = 10;
		a4->AnimInfo.Next = 15;
		a3->Status &= 0xDFFFu;
		return 1;
	case 20: //pulley, fix crash when trying to grab it with custom moves.
		a4->Speed = { 0, 0, 0 };
		a3->Status &= 0xDAFFu;
		a3->Action = 51;
		a4->AnimInfo.Next = 75;
		return 1;
	case 28:
		a3->Action = 56;
		a3->Status &= 0xDAFFu;
		return 1;
	case 31:
		if (!isRando()) {

			if (setGrindingNextAction(a2, a4, a3))
				return 1;
			else
				return 0;
		}
		break;
	case 32:
		if (!isRando()) {
			if (!CharacterAnimations[200].Animation) {
				return 1;
			}
			if (SetHandGranding(a1, a4, a3)) {
				return 1;
			}
			else {
				return 0;
			}
		}
		break;
	case 38:
		a3->Action = 6;
		return 1;

	}

	return Knux_CheckNextActions_original(a1, a2, a3, a4);
}

static void __declspec(naked) Knux_CheckNextActionsASM()
{
	__asm
	{
		push[esp + 04h] // a4
		push ebx // a3
		push ecx // a2
		push edx // a1

		// Call your __cdecl function here:
		call Knux_CheckNextActions_r

		pop edx // a1
		pop ecx // a2
		pop ebx // a3
		add esp, 4 // a4
		retn
	}
}


void __cdecl Knux_RunsAction_r(EntityData1* data1, EntityData2* data2, KnucklesCharObj2* a3, KnucklesCharObj2* a4) {

	a3->base.AnimInfo.Next = a3->base.AnimInfo.Next;

	FunctionPointer(void, original, (EntityData1 * data1, EntityData2 * data2, KnucklesCharObj2 * a3, KnucklesCharObj2 * a4), Knux_RunsAction_t->Target());
	original(data1, data2, a3, a4);

	int currentAnim = a4->base.AnimInfo.Current;


	switch (data1->Action) {

	case Action_None:
	case Action_Run:


		if (data1->NextAction != 0 || (data1->Status & Status_DoNextAction))
			return;

		if (Fast_SunglassesCheckInput(&a4->base, data1))
			return;

		if (Knux_CheckPunchInput(&a4->base, data1))
			return;

		if (RollCheckInput(data1, &a4->base))
			return;

		break;
	case Grinding:

		if (data1->NextAction != 0 || (data1->Status & Status_DoNextAction))
			return;

		CheckGrindThing(data1, data2, &a4->base, a3);
		break;
	case HandGrinding: //Or whatever you call that thing in CG

		if (data1->NextAction != 0 || (data1->Status & Status_DoNextAction))
			return;

		DoHandGrinding(data1, &a4->base);
		return;
	case Action_SA1Rolling:

		if (data1->NextAction != 0 || (data1->Status & Status_DoNextAction))
			return;

		UnrollCheck(data1, data2, &a4->base);
		break;
	case Action_SA1Punch:

		if (data1->NextAction != 0 || (data1->Status & Status_DoNextAction))
			return;

		if ((a4->base.AnimInfo.Current) == 0 || a4->base.AnimInfo.Current == 8) {

			data1->Collision->CollisionArray[1].attr |= 0x10u;
			if (data1->Action != Action_Death)
			{
				data1->Action = Action_None;
				data1->Status &= 0xFBFFu;
			}

			return;
		}

		if ((currentAnim == punch01Anim || currentAnim == punch01Anim + 5) && data1->Action == Action_Dig) {
			data1->Status &= 0xFBFFu;
			return;
		}

		Knux_CheckPunchRefresh(data1, &a4->base);
		return;
	}
}

void Knux_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Knux_Main_t->Target());
	origin(obj);

	CharObj2Base* co2 = obj->Data2.Character;
	EntityData1* data1 = obj->Data1.Entity;
	EntityData2* data2 = (EntityData2*)obj->EntityData2;
	KnucklesCharObj2* co2Knux = (KnucklesCharObj2*)obj->Data2.Character;

	switch (data1->Action) {

	case Grinding:
		DoGrindThing(data1, data2, co2, co2Knux);
		PlayGrindAnimation(data1, co2); //not called by the game, custom function to play animation for Knux
		MoveCharacterOnRail(data1, co2, data2);
		LoadRailParticules(co2Knux, data2);
		break;
	case HandGrinding: //Or whatever you call that thing in CG
		SomethingAboutHandGrind(data1, data2, co2Knux);
		MoveCharacterOnRail(data1, co2, data2);
		SomethingAboutHandGrind2(data1, data2, co2Knux);
		break;
	case Action_SA1Rolling:
		RollPhysicControlMain(data1, data2, co2);
		DoCollisionAttackStuff(data1);
		UnrollCheckInput(data1, co2);
		break;
	case Action_SA1Punch:
		KnuxComboAction(data2, co2, data1);
		PlayerGetRotation(data1, data2, co2);
		PGetFriction(data1, data2, co2);
		PlayerGetSpeed(data1, co2, data2);

		if (co2->AnimInfo.Current == punch01Anim && co2->Speed.x > 0.2)
		{
			co2->Speed.x = (0.2 - co2->Speed.x) * 0.5 + co2->Speed.x;
		}

		if (PlayerSetPosition(data1, data2, co2))
		{
			Vector3 a3;
			GetBufferedPositionAndRot(co2->PlayerNum, 0, &a3, 1);
			data1->Position = a3;
			co2->Speed.z = 0.0;
			co2->Speed.y = 0.0;
			co2->Speed.x = 0.0;
			data2->Velocity.z = 0.0;
			data2->Velocity.y = 0.0;
			data2->Velocity.x = 0.0;
		}

		PResetPosition(data1, data2, co2);
		break;
	}
}



void KnuxTricks_Init() {
	Knux_Main_t = new Trampoline((int)0x728D70, (int)0x728D76, Knux_Main_r);
	Knux_CheckNextActions_t = new Trampoline(0x732E00, 0x732E05, Knux_CheckNextActionsASM);
	Knux_RunsAction_t = new Trampoline((int)0x72A520, (int)0x72A525, Knux_RunsAction_r);

	init_SunglassesChange();

	//WriteData<1>((int*)0x443130, 0xC3);

}