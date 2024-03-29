#pragma once



static const void* const Sub4372E0Ptr = (void*)0x4372E0;
static inline char Play3DSoundPosThing(int id, NJS_VECTOR* pos, int a3, char a4, char a5)
{
	char result;
	__asm
	{
		push[a5]
		push[a4]
		push[a3]
		mov esi, [pos]
		mov edi, [id]
		call Sub4372E0Ptr
		add esp, 12
		mov result, al
	}
	return result;
}


static const void* const somethingAboutTrickPtr = (void*)0x45ABE0;
static inline bool PlayerCheckBreakMaybe(EntityData1* a1, CharObj2Base* a2)
{
	int result;
	__asm
	{
		mov esi, [a2] // a2
		mov edi, [a1] // a1:
		call somethingAboutTrickPtr
		mov result, eax
	}
	return result;
}

static const void* const CheckPlayerStopPtr = (void*)0x475100;
static inline signed int CheckPlayerStop(EntityData1* a1, CharObj2Base* a2, EntityData2* a4)
{
	signed int result;
	__asm
	{
		push[a4]
		mov esi, [a2] 
		mov eax, [a1] 
		call CheckPlayerStopPtr
		add esp, 4
		mov result, eax
	}
	return result;
}

static const void* const KnuxJumpPtr = (void*)0x732B80;
static inline signed int KnuxJump(EntityData1* a1, CharObj2Base* a2)
{
	signed int result;
	__asm
	{
		push[a2]
		mov eax, [a1]
		call KnuxJumpPtr
		add esp, 4
		mov result, eax
	}
	return result;
}

FunctionPointer(signed int, sub_429710, (), 0x429710); //matrix stuff
FunctionPointer(signed int, sub_429000, (), 0x429000); //matrix stuff
FunctionPointer(void, PlayerGetRotation, (EntityData1* data, EntityData2* a3, CharObj2Base* co2), 0x45FA70);


static const void* const GetBufferedPositionAndRotPtr = (void*)0x46DBF0;
static inline signed int GetBufferedPositionAndRot(int a1, int a2, NJS_VECTOR* a3, char a4)
{
	signed int result;
	__asm
	{
		push[a4]
		mov esi, [a3]
		mov edi, [a2]
		mov eax, [a1]
		call GetBufferedPositionAndRotPtr
		add esp, 4
		mov result, eax
	}
	return result;
}


ObjectFunc(PrisonLaneDoor4, 0x606A10);


static const void* const PConvertVP2GPtr = (void*)0x468E70;
static inline void PConvertVector_P2G(EntityData1* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov esi, [a2]
		mov edi, [a1] // a1
		call PConvertVP2GPtr
	}
}

static const void* const PConvertVPtr = (void*)0x468DF0;
static inline void PConvertVector_G2P(EntityData1* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov esi, [a2]
		mov edi, [a1]
		call PConvertVPtr
	}
}



static const void* const SlowDownThingPtr = (void*)0x45F840;
static inline float SlowDownThing(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	float result;
	__asm
	{
		mov ebx, a3
		mov eax, a2
		mov ecx, a1
		// Call your __cdecl function here:
		call SlowDownThingPtr
		fstp result
	}
	return result;
}


static const void* const KnuxSetPunchPtr = (void*)0x734E50;
static inline signed int Knux_SetPunchAction(EntityData1* data, CharObj2Base* a2, KnucklesCharObj2* a3)
{
	signed int result;
	__asm
	{
		push[a3]
		mov edi, [a2]
		mov eax, [data]
		call KnuxSetPunchPtr
		add esp, 4
		mov result, eax
	}
	return result;
}

static const void* const KnuxSetPunchRunPtr = (void*)0x734EC0;
static inline signed int Knux_SetPunchRunAction(EntityData1* data, CharObj2Base* a2, KnucklesCharObj2* a3)
{
	signed int result;
	__asm
	{
		push[a3]
		mov edi, [a2]
		mov eax, [data]
		call KnuxSetPunchRunPtr
		add esp, 4
		mov result, eax
	}
	return result;
}


static const void* const KnuxSetGlassesPtr = (void*)0x736170;
static inline void Knux_SetSunglasses(EntityData1* data, CharObj2Base* co2)
{
	__asm
	{
		mov ebx, [co2]
		mov eax, [data]
		call KnuxSetGlassesPtr
	}
}

static const void* const KnuxCheckGlassesPtr = (void*)0x735EC0;
static inline signed int Knux_CheckSunglasses(CharObj2Base* co2)
{
	signed int result;
	__asm
	{
		mov eax, [co2]
		call KnuxCheckGlassesPtr
		mov result, eax
	}

	return result;
}


static const void* const KnuxAnimPtr = (void*)0x734FE0;
static inline signed int KnuxResetActionAnim(CharObj2Base* a1, EntityData1* a2, KnucklesCharObj2* a3)
{
	signed int result;

	__asm
	{
		push[a3]
		mov esi, [a2]
		mov eax, [a1]
		call KnuxAnimPtr
		add esp, 4
		mov result, eax
	}

	return result;
}



static const void* const PGetGravityPtr = (void*)0x45F9E0;
static inline void PGetGravityMaybe(EntityData1* a1, EntityData2* data2, CharObj2Base* a3)
{
	__asm
	{
		mov ebx, [a3]
		mov eax, [data2]
		mov ecx, [a1]
		call PGetGravityPtr
	}
}

static const void* const KnuxCheckWindowPtr = (void*)0x7338F0;
static signed int Knux_CheckActionWindow_(CharObj2Base* co2, EntityData2* data2, EntityData1* data1, KnucklesCharObj2* knuxCO2)
{
	signed int result;
	__asm
	{
		push[knuxCO2]
		push[data1]
		mov edx, [data2]
		mov eax, [co2]
		call KnuxCheckWindowPtr
		add esp, 8
		mov result, eax
	}
	return result;
}