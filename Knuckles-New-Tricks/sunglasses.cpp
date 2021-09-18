#include "pch.h"

Trampoline* KnucklesSunglassesMan_t;
Buttons glassesBtn = Buttons_Up;


void __cdecl KnucklesSunglassesMan_r(ObjectMaster* a1)
{

	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* p1 = MainCharObj1[0];

	if (Jump_Pressed[0] || Jump_Pressed[1])
		return;

	if ((Controllers[0].press & glassesBtn) && p1->Action <= Action_Run)
	{
		a1->MainSub = DeleteObject_;
		return;
	}

	ObjectFunc(origin, KnucklesSunglassesMan_t->Target());
	origin((ObjectMaster*)a1);
}


signed int Fast_SunglassesCheckInput(CharObj2Base* co2, EntityData1* data1) {

	if (!fastGlasses)
		return 0;

	if ((Controllers[co2->PlayerNum].press & glassesBtn))
	{
		if (Knux_CheckSunglasses(co2)) {
			Knux_SetSunglasses(data1, co2);
			return 1;
		}
	}

	return 0;
}


void init_SunglassesChange() {

	if (noFilter)
		WriteData<1>((int*)0x735FA0, 0xC3); //Remove that blue filter when using sunglasses (C3 = add return at the beginning of the function.)

	if (!fastGlasses)
		return;

	KnucklesSunglassesMan_t = new Trampoline((int)KnucklesSunglassesMan, (int)KnucklesSunglassesMan + 0x5, KnucklesSunglassesMan_r);
}