# include "pch.h"


NJS_TEXNAME SA1_Eff[36];
NJS_TEXLIST SA1_EffTexlist = { arrayptrandlengthT(SA1_Eff, Uint32) };


NJS_TEXANIM smokeTexAnim[] = {
  { 0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 1, 0},
  { 0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 2, 0 },
  {0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 3, 0},
  {0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 4, 0},
  {0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 5, 0},
  {0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 6, 0},
  {0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 7, 0},
  {0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 7, 0},
  {0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 7, 0},
};

sp_info spinfo_smoke = { &SA1_EffTexlist, smokeTexAnim, 0xA, 8, 6 };

particle_entry particle_smoke = { &spinfo_smoke, 0, 0, 0 };

particle_info default_smoke = { 1.0, 0.037999999, 0.19, 0.059999999, 0.025, {0}, {0}, { 1.0, 1.0, 1.0, 1.0 } };


void SpFreeTask(sp_task* tp)
{
	tp->exec = 0;
}

void EffectSmoke(sp_task* spTask, sp_link* spLink)
{
	double frame; // fp0
	particle_info* v3; // r11
	__int16 frameCopy; // r10
	int animNum; // r9
	int animNumSPLink; // r10
	double v7; // fp11
	double v8; // fp10
	double v9; // fp9
	double v10; // fp8
	double v11; // fp7
	double v12; // fp6
	double v13; // fp5
	double v14; // fp4
	double v15; // fp1

	frame = spTask->frame;
	v3 = (particle_info*)spTask->work[0].l;
	frameCopy = (int)frame;
	animNum = frameCopy;
	spTask->no = frameCopy;
	animNumSPLink = spLink->info->animnum;
	if (animNum < (__int16)animNumSPLink)
	{
		if (frame >= 6.0)
			spTask->frame = (float)(v3->animspd * (float)2.0) + (float)frame;
		else
			spTask->frame = v3->animspd + (float)frame;
		v7 = spTask->spd.z;
		v8 = spTask->spd.y;
		v9 = spTask->pos.x;
		v10 = (float)((float)1.0 - v3->friction);
		v11 = spTask->pos.y;
		v12 = spTask->pos.z;
		v13 = spTask->scl;
		v14 = (float)(spTask->spd.x * (float)((float)1.0 - v3->friction));
		spTask->spd.x = spTask->spd.x * (float)((float)1.0 - v3->friction);
		v15 = (float)((float)((float)v8 * (float)v10) + v3->yacc);
		spTask->spd.y = (float)((float)v8 * (float)v10) + v3->yacc;
		spTask->spd.z = (float)v7 * (float)v10;
		spTask->pos.x = (float)v9 + (float)v14;
		spTask->pos.y = (float)v15 + (float)v11;
		spTask->pos.z = (float)v12 + (float)((float)v7 * (float)v10);
		spTask->scl = (float)(v3->sclspd * (float)0.15000001) + (float)v13;
	}
	else
	{
		spTask->no = animNumSPLink - 1;
		SpFreeTask(spTask);
	}
}



void Load_Particles() {

	LoadTextureList("EFF_REGULAR", &SA1_EffTexlist);

}