#include "pch.h"
#include "punch.h"

NJS_TEXNAME Knux_EffTex[11];
NJS_TEXLIST Knux_EffTexList = { arrayptrandlengthT(Knux_EffTex, Uint32) };

ModelInfo* PunchMDL = nullptr;
Buttons punchButton = Buttons_Y;


NJS_TEXANIM anim_k_kira = { 0x10, 0x10, 8, 8, 0, 0, 0xFF, 0xFF, 9, 0 };
NJS_SPRITE knuHadokenSprite = { { 0 } , 1.2, 1.2, 0x8000, &Knux_EffTexList, &anim_k_kira };

NJS_TEXANIM anim_knu_punch[]{
	{0xA, 0xA, 5, 5, 0, 0, 0xFF, 0xFF, 3, 0},
	{0xA, 0xA, 5, 5, 0, 0, 0xFF, 0xFF, 4, 0},
	{0xA, 0xA, 5, 5, 0, 0, 0xFF, 0xFF, 5, 0},
	{0xA, 0xA, 5, 5, 0, 0, 0xFF, 0xFF, 6, 0},
	{0xA, 0xA, 5, 5, 0, 0, 0xFF, 0xFF, 7, 0},
	{0xA, 0xA, 5, 5, 0, 0, 0xFF, 0xFF, 8, 0},
};

NJS_SPRITE knu_punchSprite = { { 0 } , 1.0, 1.0, 0x8000, &Knux_EffTexList, anim_knu_punch };

CollisionData Hadoken_Col = { 0, CollisionShape_Sphere, 0x70, 0x41, 0x400, {0}, 8.0, 0.0, 0.0, 0.0, 0, 0, 0 };

void __cdecl KnuxeffectComboFire(ObjectMaster* obj)
{
	EntityData1* Data; // esi
	double v3; // st7
	Angle v4; // eax
	Angle v5; // eax
	Angle v6; // eax
	double v7; // st7
	float thisa; // [esp+Ch] [ebp+4h]

	Data = obj->Data1.Entity;
	if (Data->Scale.x >= 25.0)
	{
		v3 = 30.0 - Data->Scale.x;
	}
	else
	{
		v3 = Data->Scale.x - 20.0;
	}

	thisa = v3 * 0.15000001;

	SetMaterialColor(thisa, 1.0, 1.0, 1.0);
	njPushMatrix(0);
	njTranslateV(0, &Data->Position);
	v4 = Data->Rotation.z;
	if (v4)
	{
		njRotateZ(0, v4);
	}
	v5 = Data->Rotation.x;
	if (v5)
	{
		njRotateX(0, v5);
	}
	v6 = Data->Rotation.y;
	if (v6 != 0x8000)
	{
		njRotateY(0, (0x8000 - v6));
	}
	v7 = Data->Scale.x * 6553.6001;
	if (v7)
	{
		njRotateX(0, v7);
	}
	njScale(0, 1.0, 2.0, 2.0);
	njSetTexture(&Knux_EffTexList);
	DrawObject(PunchMDL->getmodel());

	njPopMatrix(1u);
	ResetMaterialColorOffset();
	DeleteObject_(obj);
}

void __cdecl dispEffectKnuPunch(ObjectMaster* a1)
{
	EntityData1* data; // esi

	data = a1->Data1.Entity;
	EntityData2* data2 = a1->Data2.Entity;
	if (data2->Forward.x < 6)
	{
		SetMaterialColor(0.5, 1.0, 1.0, 1.0);
		njSetTexture(&Knux_EffTexList);
		njPushMatrix(0);
		njTranslateV(0, &data->Position);
		NJDrawSprite3D(data2->Forward.x, &knu_punchSprite, NJD_SPRITE_ALPHA | NJD_SPRITE_SCALE | NJD_SPRITE_COLOR);
		njPopMatrix(1u);
		ResetMaterialColorOffset();
	}
}

void __cdecl EffectKnuPunch(ObjectMaster* a1)
{
	EntityData1* data; // eax
	double v2; // st7

	data = a1->Data1.Entity;
	EntityData2* data2 = a1->Data2.Entity;

	if (data->Action)
	{
		if (data->Action == 1)
		{
			v2 = data2->Forward.x + (float)0.5;
			data2->Forward.x = v2;
			if (v2 >= 6.0)
			{
				DeleteObject_(a1);
				return;
			}
		}
	}
	else
	{
		data2->Forward.x = 0.0f;
		data->Action = 1;
		a1->DisplaySub = dispEffectKnuPunch;
	}

	ClipSetObject(a1);
}

void __cdecl dispEffectKnuHadoken(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	float r; // [esp+0h] [ebp-14h]

	v1 = a1->Data1.Entity;

	EntityData2* data2 = a1->Data2.Entity;

	r = data2->Velocity.x * 0.80000001;

	SetMaterialColor(r, 1.0, 1.0, 1.0);
	njSetTexture(&Knux_EffTexList);
	njPushMatrix(0);
	njTranslateV(0, &v1->Position);
	NJDrawSprite3D(0, &knuHadokenSprite, NJD_SPRITE_ALPHA | NJD_SPRITE_SCALE | NJD_SPRITE_COLOR);
	njPopMatrix(1u);
	ResetMaterialColorOffset();
}

void __cdecl EffectKnuxHadoken(ObjectMaster* obj)
{

	EntityData1* data; // r31
	double timer; // fp0
	CollisionInfo* v4; // r10
	double v5; // fp6
	double v6; // fp5

	data = obj->Data1.Entity;
	EntityData2* data2 = obj->Data2.Entity;
	if (data->Action)
	{
		if (data->Action == 1)
		{
			timer = (float)(data2->Velocity.x - (float)0.083333336);
			data2->Velocity.x = data2->Velocity.x - (float)0.083333336;
			if (timer <= 0.0)
			{
				DeleteObject_(obj);
				return;
			}
			v4 = data->Collision;
			v5 = (float)(data->Scale.y + data->Position.y);
			v6 = (float)(data->Scale.z + data->Position.z);
			data->Position.x = data->Scale.x + data->Position.x;
			data->Position.y = v5;
			data->Position.z = v6;
			v4->CollisionArray->param1 = (float)timer * (float)8.0;
			AddToCollisionList(obj);
		}
	}
	else
	{
		data2->Velocity.x = 1.0;
		InitCollision(obj, &Hadoken_Col, 1, 4u);

		data->Action = 1;
		obj->DisplaySub_Delayed3 = dispEffectKnuHadoken;
	}
}

KnComboEff PunchComboArray[10] = {
	{ 0, 1, -19.0, 20.0, 2.0, 20.0, 8.0 },
	{ 1, 1, -16.0, 17.0, 2.0, 18.0, 8.0 },
	{ 0, 0, 18.0, 22.0, 2.0, 49.0, 16.0 },
	{ 1, 0, 20.0, 24.0, 16.0, 28.0, 20.0},
	{ 1, 0, 17.0, 23.0, 16.0, 38.0, 25.0},
	{ 0, 3, -4.0, 8.0, 2.0, 16.0, 8.0 },
	{ 1, 3, -2.0, 8.0, 2.0, 16.0, 4.0 },
	{ 0, 0, 10.0, 18.0, 2.0, 24.0, 16.0 },
	{ 3, 0, 10.0, 16.0, 8.0, 20.0, 18.0 },
	{ 1, 0, 8.0, 14.0, 4.0, 18.0, 10.0 },
};

void KnuxComboAction(EntityData2* a1, CharObj2Base* co2, EntityData1* data1)
{
	double curFrames; // st7
	double v7; // st7
	float v8; // eax
	ObjectMaster* v9; // eax
	unsigned __int16 curAnim; // ax
	int v11; // eax
	KnComboEff* knCombo; // ebp
	NJS_VECTOR v13; // ecx
	Angle v14; // eax
	Angle v15; // eax
	ObjectMaster* punchObj; // ebx
	ObjectMaster* v17; // eax
	Vector3 a2; // [esp+4h] [ebp-18h] BYREF
	Vector3 a3; // [esp+10h] [ebp-Ch] BYREF

	co2->Powerups |= Powerups_Invincibility;

	if (co2->AnimInfo.Current == punch03Anim)
	{
		curFrames = co2->AnimInfo.field_10;
		if (curFrames >= 15.0)
		{
			if (curFrames >= 20.0)
			{
				if (curFrames >= 30.0)
				{
					v7 = (curFrames - 15.0) * 0.2 * 4.0;
					co2->Speed.x = v7;
				}
				else {
					co2->Speed.x = 4.0;
					a2.x = data1->Position.x;
					v8 = data1->Position.z;
					a2.y = data1->Position.y;
					a2.z = v8;
					a2.y = a2.y + 2.0;
					a3.y = 0.0;
					a3.x = a1->Velocity.x * -0.2;
					a3.z = a1->Velocity.z * -0.2;
					//CreateSmoke(&a2, &a3, 1.0);
					a3.z = 0.0;
					a3.x = 0.0;
					//CreateSmoke(&a2, &a3, 1.0);
					v9 = LoadObject(2, "comoboFire", KnuxeffectComboFire, LoadObj_Data1); //Final punch with charge
					if (v9)
					{
						v9->Data1.Entity->Position = data1->Collision->CollisionArray->center;
						v9->Data1.Entity->Rotation = data1->Rotation;
						v9->Data1.Entity->Scale.y = co2->AnimInfo.field_10;
					}
					VibeThing(co2->PlayerNum, 0, 0, 0);
				}
			}
		}
	}

	data1->Collision->CollisionArray->damage &= 0xFCu;
	data1->Collision->CollisionArray->damage &= 0xF3u;
	data1->Collision->CollisionArray[1].attr |= 0x10u;

	curAnim = co2->AnimInfo.Current;

	if (curAnim < punch01Anim || curAnim > punch03Anim + 4)
		return;

	v11 = curAnim - punch01Anim;
	knCombo = &PunchComboArray[v11];
	v13 = { 0, 0, 0 };
	a2 = v13;
	njPushMatrix(_nj_unit_matrix_);
	v14 = data1->Rotation.z;
	if (v14)
	{
		njRotateZ(0, v14);
	}
	v15 = data1->Rotation.x;
	if (v15)
	{
		njRotateX(0, v15);
	}
	if (data1->Rotation.y != 0x8000)
	{
		njRotateY(0, (0x8000 - LOWORD(data1->Rotation.y)));
	}
	njCalcPoint(&a2, &a3, nj_current_matrix_ptr_); //nj calc vector maybe
	njPopMatrix(1u);
	njAddVector(&a3, &data1->Collision->CollisionArray->center);
	if (co2->AnimInfo.Current == punch01Anim + 4)
	{
		a3.y = a3.y + 2.5;
	}
	data1->Status &= 0xFBu;
	if (co2->AnimInfo.field_10 >= knCombo->col_start && co2->AnimInfo.field_10 <= knCombo->col_end)
	{
		data1->Collision->CollisionArray->damage &= 0xFCu;
		data1->Collision->CollisionArray->damage |= 0xCu;
		data1->Collision->CollisionArray[1].attr &= 0xFFFFFFEF;
		data1->Collision->CollisionArray[1].center = a3;
		data1->Status |= 4u;
	}
	if (knCombo->hdkvec)
	{
		//if (co2->AnimInfo.field_10 >= knCombo->had_start && knCombo->had_start + 1.0 > co2->AnimInfo.field_10)
		if (co2->AnimInfo.field_10 == 3.0) //let's hardcode this for now
		{
			punchObj = LoadObject(2, "KnuxHadoken", EffectKnuxHadoken, 10); //"ball SFX thing"
			if (punchObj)
			{
				switch (knCombo->hdkvec)
				{
				case 1:
					a2.x = 2.0;
					a2.y = 0.0;
					goto LABEL_34;
				case 2:
					a2.x = -2.0;
					a2.y = 0.0;
					goto LABEL_34;
				case 3:
					a2.y = 2.0;
					goto LABEL_33;
				case 4:
					a2.y = -2.0;
				LABEL_33:
					a2.x = 0.0;
				LABEL_34:
					a2.z = 0.0;
					break;
				default:
					break;
				}
				PConvertVector_P2G(data1, &a2);
				punchObj->Data1.Entity->Position = a3;
				punchObj->Data1.Entity->Scale = a2;
			}
		}
	}
	if (co2->AnimInfo.field_10 >= knCombo->col_start
		&& knCombo->col_start + 1.0 > co2->AnimInfo.field_10
		&& co2->AnimInfo.field_10 >= 0x36u)
	{
		if (co2->AnimInfo.Current <= punch02Anim)
		{
			//PlaySound(781, 0, 0, 0);
			VibeThing(co2->CharID, 0, 0, 0);
		}
		else if (co2->AnimInfo.Current == punch03Anim)
		{
			//PLAY SOUND
			 //PLAY SOUND
		}
	}
	if (knCombo->eff_start >= 0.0
		&& co2->AnimInfo.field_10 >= knCombo->eff_start
		&& co2->AnimInfo.field_10 <= knCombo->eff_end)
	{
		v17 = LoadObject(2, "EffectPunch", EffectKnuPunch, 10);
		if (v17)
		{
			v17->Data1.Entity->Position = a3;
			v17->Data1.Entity->Scale.x = 1.0;
		}
	}

}


signed int Knux_CheckPunchInput(CharObj2Base* co2, EntityData1* data)
{
	if ((punchButton & Controllers[co2->PlayerNum].press) == 0)
	{
		return 0;
	}

	data->Action = Punch;
	co2->AnimInfo.Next = punch01Anim;
	// co2->AnimationThing.Index = 54; //anim punch

	return 1;
}


void Load_KnuxPunch() {
	PunchMDL = LoadMDL("Punch", ModelFormat_Chunk);
	LoadTextureList("KNU_EFF_HD", &Knux_EffTexList);
}