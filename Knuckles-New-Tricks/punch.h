#pragma once

extern Buttons punchButton;

signed int Knux_CheckPunchInput(CharObj2Base* co2, EntityData1* data);

struct KnComboEff
{
	unsigned __int16 jointnmb;
	__int16 hdkvec;
	float eff_start;
	float eff_end;
	float col_start;
	float col_end;
	float had_start;
};

void KnuxComboAction(EntityData2* a1, CharObj2Base* data2, EntityData1* data1);

enum KnuxPunch {
	punch01Anim = 230,
	punch02Anim,
	punch03Anim
};

void Knux_CheckPunchRefresh(EntityData1* data, CharObj2Base* co2);