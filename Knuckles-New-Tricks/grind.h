#pragma once


enum KnuxAnimsRail : unsigned __int16 {
	Anm_RailL = 203,
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
static inline signed int CheckTrickASM(TailsCharObj2* a1, CharObj2Base* a2, EntityData1* a3)
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