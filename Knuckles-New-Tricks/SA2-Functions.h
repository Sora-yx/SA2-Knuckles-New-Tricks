#pragma once

ObjectFunc(Dynamite_Main, 0x6da880);
ObjectFunc(DynamiteHiddenBase_Main, 0x714610);
ObjectFunc(DynamiteSandOcean_Main, 0x65AEA0);
ObjectFunc(PrisonLaneDoor, 0x606400);
ObjectFunc(PrisonLaneDoor4, 0x606A10);

ObjectFunc(RocketIG, 0x6A10A0);
ObjectFunc(DoorIG, 0x69D1D0);
ObjectFunc(DoorIG2, 0x69F460);
ObjectFunc(DoorCCThing, 0x79AFB0);
ObjectFunc(DoorHB, 0x715560);
ObjectFunc(CGTubeGlass, 0x776060);

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

static const void* const VibeThingPtr = (void*)0x438E70;
static inline void VibeThing(int a1, signed int a2, int a3, signed int a4)
{
	__asm
	{
		push[a4] // int a4
		mov ecx, a3 // a3
		mov edx, a2 // int a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call VibeThingPtr
		add esp, 4 // int a4
	}
}

static const void* const somethingAboutTrickPtr = (void*)0x45ABE0;
static inline bool PlayerCheckBreakMaybe(int a1, EntityData1* a2, CharObj2Base* a3)
{
	int result;
	__asm
	{
		mov esi, [a3] // a3
		mov edi, [a2] // a2
		mov ecx, [a1] // a1

		// Call your __cdecl function here:
		call somethingAboutTrickPtr
		mov result, ecx
	}
	return result;
}

static const void* const somethingAboutTrick2Ptr = (void*)0x475100;
static inline signed int CheckPlayerStopASM(EntityData1* a1, CharObj2Base* a2, EntityData2* a4)
{
	signed int result;
	__asm
	{
		push[a4]
		mov esi, [a2] // a2
		mov eax, [a1] // a1

		// Call your __cdecl function here:
		call somethingAboutTrick2Ptr
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

static const void* const PGetSpeedPtr = (void*)0x460860;
static inline void PlayerGetSpeed(EntityData1* a1, CharObj2Base* co2, EntityData2* data2)
{
	__asm
	{
		push[data2] // a3
		mov ebx, co2 // a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call PGetSpeedPtr

		add esp, 4 // a3
	}
}

static const void* const PSetPositionptr = (void*)0x4616E0;
static inline int PlayerSetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	int result;
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call PSetPositionptr
		add esp, 8
		mov result, eax
	}
	return result;
}

static const void* const sub_469050Ptr = (void*)0x469050;
static inline void PResetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	__asm
	{
		push[a3] // a3
		mov ebx, a2 // a2
		mov eax, a1 // a1
		call sub_469050Ptr
		add esp, 4 // a2
	}
}

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

static const void* const frictionPtr = (void*)0x45F4D0;
static inline void PGetFriction(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	__asm
	{
		push[a3] // a3
		mov eax, a2 // a2
		mov ecx, a1 // a1
		call frictionPtr
		add esp, 4 // a2
	}
}


FunctionPointer(void, DrawObject, (NJS_OBJECT* a1), 0x42E730);

FunctionPointer(void, SetMaterialColor, (float Alpha, float R, float G, float B), 0x44B2E0);

void ResetMaterialColorOffset();

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


static const void* const njdrawsprite3Dptr = (void*)0x77D690;
static inline void NJDrawSprite3D(int a1, NJS_SPRITE* a2, char a3)
{
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call njdrawsprite3Dptr
		add esp, 8
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
