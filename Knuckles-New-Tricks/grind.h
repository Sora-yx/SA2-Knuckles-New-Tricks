#pragma once


enum KnuxAnimsRail : unsigned __int16 {
	Anm_RailL = 217,
	Anm_RailR,
	Anm_RailCrouchL,
	Anm_RailCrouchR,
	Anm_RailFastL,
	Anm_RailFastR,
	Anm_RailFastCL,
	Anm_RailFastCR,
	Anm_RailBalanceL,
	Anm_RailBalanceR,
	Anm_RailTrick1, // Awesome
	Anm_RailTrick2, // Cool
	Anm_RailTrick3 // Nice
};

static const void* const sub_45B2C0Ptr = (void*)0x45B2C0;
static inline int sub_45B2C0(CharObj2Base* a1, int a2, EntityData1* a3)
{
	int result;

	__asm
	{
		mov esi, [a3]
		mov ecx, [a2]
		mov edx, [a1]

		call sub_45B2C0Ptr
		mov result, edx
	}

	return result;
}

static const void* const CheckGrindPtr = (void*)0x726D00;
static inline signed int CheckTrickASM(KnucklesCharObj2* a1, CharObj2Base* a2, EntityData1* a3)
{
	signed int result;

	__asm
	{
		push[a3]
		mov edi, [a2]
		mov eax, [a1]

		call CheckGrindPtr
		add esp, 8 // a2
		mov result, eax
	}
	return result;
}



static const void* const somethingAboutTrick3Ptr = (void*)0x474F80;
static inline int somethingAboutTrick3(CharObj2Base* a1, EntityData1* a2)
{
	int result;
	__asm
	{
		push[a2]
		mov ebx, [a1]
		// Call your __cdecl function here:
		call somethingAboutTrick3Ptr
		add esp, 4
		mov result, eax
	}
	return result;
}

static const void* const sub_4EC330Ptr = (void*)0x4EC330;
static inline void sub_4EC330(int a1, int a2, int a3)
{
	__asm
	{
		mov ecx, [a3] // a3
		mov ebx, [a2] // a2
		mov edx, [a1] // a1
		// Call your __cdecl function here:
		call sub_4EC330Ptr
	}
}



//Math stuff that allow character to move on the rail
static const void* const sub_46D040Ptr = (void*)0x46D040;
static inline void sub_46D040(EntityData1* a1, CharObj2Base* a2, EntityData2* a3)
{
	__asm
	{
		push[a3]
		mov ebx, [a2]
		mov eax, [a1]
		call sub_46D040Ptr
		add esp, 4 // a3
	}
}

static const void* const sub_46D140Ptr = (void*)0x46D140;
static inline void getRailAccel(CharObj2Base* a1, EntityData1* a2, EntityData2* a3)
{
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]

		// Call your __cdecl function here:
		call sub_46D140Ptr
		add esp, 8 // a2
	}
}

//Sparkles Rail thing
//void __usercall sub_754EC0(int playernum@<ebx>)
static const void* const sub_754EC0Ptr = (void*)0x754EC0;
static inline void sub_754EC0(int playernum)
{
	__asm {
		mov ebx, [playernum]
		call sub_754EC0Ptr
	}
}

FunctionPointer(void, DoGrindThing, (EntityData1* data, EntityData2* data2, CharObj2Base* co2, KnucklesCharObj2* co2Knux), 0x725F30);
FunctionPointer(double, SomethingAboutHandGrind, (EntityData1* a1, EntityData2* a2, KnucklesCharObj2* a3), 0x7271D0);
FunctionPointer(signed int, SomethingAboutHandGrind2, (EntityData1* a1, EntityData2* a2, KnucklesCharObj2* a3), 0x46D6D0);
FunctionPointer(int, calcGrindRotationMaybe, (NJS_VECTOR* v, Rotation* rot), 0x4905A0);
FunctionPointer(int, sub_447580, (NJS_OBJECT* v), 0x447580);
FunctionPointer(void, SetNewRot, (int a1, int a2, int a3), 0x46C490);

int setGrindingNextAction(KnucklesCharObj2* a2, CharObj2Base* a3, EntityData1* a4);
signed int SetHandGranding(EntityData2* data2, CharObj2Base* co2, EntityData1* data1);
void PlayGrindAnimation(EntityData1* data1, CharObj2Base* co2);
void MoveCharacterOnRail(EntityData1* a1, CharObj2Base* a2, EntityData2* a3);
void LoadRailParticules(KnucklesCharObj2* co2, EntityData2* data2);
void CheckGrindThing(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, KnucklesCharObj2* co2Knux);