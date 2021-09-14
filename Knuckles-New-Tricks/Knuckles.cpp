#include "pch.h"
#include "grind.h"

Trampoline* Knux_Main_t;
Trampoline* Knux_CheckNextActions_t;
Trampoline* Knux_RunsAction_t;


//Trampoline Usercall Function to get the control of "Check Next Actions" this need 3 functions to work.
static const void* const Knux_CheckNextActionPtr = (void*)0x732E00;
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
		mov result, eax
		add esp, 4 // a4
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
		if (a3->Action == Rolling)
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
		return 1;;
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
	FunctionPointer(void, original, (EntityData1* data1, EntityData2* data2, KnucklesCharObj2 * a3, KnucklesCharObj2* a4), Knux_RunsAction_t->Target());
	original(data1, data2, a3, a4);

	switch (data1->Action) {

	case Grinding:

		if (Knux_CheckNextActions_r(data2, a3, data1, &a4->base))
			return;

		CheckGrindThing(data1, data2, &a4->base, a3);
		break;
	}

}

void Knux_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Knux_Main_t->Target());
	origin(obj);

	/**KnucklesCharObj2* co2Knux = (KnucklesCharObj2*)&obj->Data2;
	CharObj2Base* co2 = &co2Knux->base;
	EntityData1* data1 = obj->Data1.Entity;
	EntityData2* data2 = (EntityData2*)obj->EntityData2;*/


	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];
	EntityData2* data2 = EntityData2Ptrs[0];
	KnucklesCharObj2* co2Knux = (KnucklesCharObj2*)MainCharObj2[0];


	switch (data1->Action) {

	case Grinding:
		DoGrindThing(data1, data2, co2, co2Knux);
		PlayGrindAnimation(data1, co2); //not called by the game, custom function to play animation for Knux
		MoveCharacterOnRail(data1, co2, data2);
		LoadRailParticules(co2Knux, data2);
		break;
	}



}

void KnuxTricks_Init() {
	Knux_Main_t = new Trampoline((int)Knuckles_Main, (int)Knuckles_Main + 0x6, Knux_Main_r);
	Knux_CheckNextActions_t = new Trampoline(0x732E00, 0x732E05, Knux_CheckNextActionsASM);
	Knux_RunsAction_t = new Trampoline((int)Knuckles_ChecksDamage, (int)Knuckles_ChecksDamage + 0x5, Knux_RunsAction_r);


	//Custom anim + new moves
	Init_NewAnimation();

	Init_StartEndPos();
}