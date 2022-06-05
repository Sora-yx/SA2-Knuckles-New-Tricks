#include "pch.h"
#include "grind.h"
#include "punch.h"
#include "roll.h"

Trampoline* Knux_Main_t;
Trampoline* Knux_CheckNextActions_t;
Trampoline* Knux_RunsAction_t;


//Trampoline Usercall Function to get the control of "Check Next Actions" this need 3 functions to work.

int Knux_CheckNextActions_original(KnucklesCharObj2* a1, EntityData2* a2, EntityData1* a3, CharObj2Base* a4) {
	const auto KnuxCheck_ptr = Knux_CheckNextActions_t->Target();

	signed int result;

	__asm
	{
		push[a4] // a4
		mov ebx, a3 // a3
		mov ecx, a2 // a2
		mov edx, a1 // a1
		call KnuxCheck_ptr
		add esp, 4
		mov result, eax
	}

	return result;
}

signed int __cdecl Knux_CheckNextActions_r(KnucklesCharObj2* knuxCO2, EntityData2* data2, EntityData1* data1, CharObj2Base* co2) {


	switch (data1->NextAction)
	{
	case 1:
		if (CurrentLevel == LevelIDs_RadicalHighway)
			data1->Action = 1; //fix softlock last loop
		else
			data1->Action = 2;
		break;
	case 3:
		if (data1->Action == Action_SA1Rolling)
		{
			data1->Action = 1;
			co2->AnimInfo.Next = 1;
			data1->Status &= 0xFAFFu;
			return 1;
		}
		if (data1->Action != Grinding)
		{
			return 1;
		}
		data1->Action = 10;
		co2->AnimInfo.Next = 15;
		data1->Status &= 0xDFFFu;
		return 1;
	case 28:
		data1->Action = 56;
		data1->Status &= 0xDAFFu;
		return 1;
	case 31:
		if (!isRando()) {

			if (setGrindingNextAction(knuxCO2, co2, data1))
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
			if (SetHandGranding(data2, co2, data1)) {
				return 1;
			}
			else {
				return 0;
			}
		}
		break;
	case 38:
		data1->Action = 6;
		return 1;

	}

	return Knux_CheckNextActions_original(knuxCO2, data2, data1, co2);
}

static void __declspec(naked) Knux_CheckNextActionsASM()
{
	__asm
	{
		push[esp + 04h] 
		push ebx
		push ecx
		push edx
		call Knux_CheckNextActions_r
		pop edx 
		pop ecx 
		pop ebx 
		add esp, 4 
		retn
	}
}


void __cdecl Knux_RunsAction_r(EntityData1* data1, EntityData2* data2, KnucklesCharObj2* a3, KnucklesCharObj2* a4) {

	FunctionPointer(void, original, (EntityData1 * data1, EntityData2 * data2, KnucklesCharObj2 * a3, KnucklesCharObj2 * a4), Knux_RunsAction_t->Target());
	original(data1, data2, a3, a4);

	int currentAnim = a4->base.AnimInfo.Current;

	if (Knux_CheckNAct(a3, data2, data1, &a4->base))
	{
		return;
	}

	switch (data1->Action) {

	case Action_None:
	case Action_Run:

		if (Fast_SunglassesCheckInput(&a4->base, data1))
			return;

		if (Knux_CheckPunchInput(&a4->base, data1))
			return;

		if (RollCheckInput(data1, &a4->base))
			return;

		break;
	case Grinding:

		CheckGrindThing(data1, data2, &a4->base, a3);
		break;
	case HandGrinding: //Or whatever you call that thing in CG

		DoHandGrinding(data1, &a4->base);
		return;
	case Action_SA1Rolling:


		UnrollCheck(data1, data2, &a4->base);
		break;
	case Action_SA1Punch:

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
		PGetSpeed(data1, co2, data2);

		if (co2->AnimInfo.Current == punch01Anim && co2->Speed.x > 0.2)
		{
			co2->Speed.x = (0.2f - co2->Speed.x) * 0.5f + co2->Speed.x;
		}

		if (PSetPosition(data1, data2, co2))
		{
			NJS_VECTOR a3;
			GetBufferedPositionAndRot(co2->PlayerNum, 0, &a3, 1);
			data1->Position = a3;
			co2->Speed.z = 0.0f;
			co2->Speed.y = 0.0f;
			co2->Speed.x = 0.0f;
			data2->Velocity.z = 0.0f;
			data2->Velocity.y = 0.0f;
			data2->Velocity.x = 0.0f;
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

}