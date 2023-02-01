#include "pch.h"

Trampoline* BrokenDownSmoke_t = nullptr;
static Trampoline* GoalRing_t = nullptr;

Trampoline* LoadEmeraldManager_t;

bool __cdecl CheckEmeraldManager()
{
	if (MissionNum == 1 || MissionNum == 2)
		return false;
	if (*(int*)0x1AF014C)
		return false;
	switch ((short)CurrentLevel)
	{
	case LevelIDs_PumpkinHill:
	case LevelIDs_AquaticMine:
	case LevelIDs_SecurityHall:
	case LevelIDs_WildCanyon:
	case LevelIDs_DryLagoon:
	case LevelIDs_DeathChamber:
	case LevelIDs_EggQuarters:
	case LevelIDs_MeteorHerd:
	case LevelIDs_WildCanyon2P:
	case LevelIDs_MadSpace:
	case LevelIDs_DryLagoon2P:
	case LevelIDs_PoolQuest:
	case LevelIDs_PlanetQuest:
	case LevelIDs_DeathChamber2P:
		return true;
	}
	return false;
}


void LoadEmeraldManager_r() {

	if (CheckEmeraldManager()) {
		auto original = reinterpret_cast<decltype(LoadEmeraldManager_r)*>(LoadEmeraldManager_t->Target());
		original();
	}
}

void GoalRing_Main_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	for (uint8_t i = 0; i < StageSelectLevels.size(); i++)
	{
		if ((CurrentLevel == StageSelectLevels[i].Level) && (StageSelectLevels[i].Character == Characters_Knuckles || StageSelectLevels[i].Character == Characters_Rouge))
		{
			if (MissionNum == 1)
			{
				data->Rotation.x = 2;
				data->Action = 1;
				if (!MainCharObj1[0] || MainCharObj1[0]->Timer < 120u)
				{
					return;
				}
			}
			else if (data->Rotation.x % 3 != 1)
			{
				return;
			}
		}
	}

	ObjectFunc(origin, GoalRing_t->Target());
	origin(obj);
}

#pragma region LevelBounds

static Trampoline* Knuckles_LevelBounds_t = nullptr;

static inline int Knuckles_LevelBounds_origin(EntityData1* a1, KnucklesCharObj2* a2)
{
	auto target = Knuckles_LevelBounds_t->Target();

	int result;
	__asm
	{
		mov ecx, [a2]
		mov eax, [a1]
		call target
		mov result, eax
	}
	return result;
}

int Knuckles_LevelBounds_r(EntityData1* a1, KnucklesCharObj2* a2)
{
	for (uint8_t i = 0; i < StageSelectLevels.size(); i++)
	{
		if ((CurrentLevel == StageSelectLevels[i].Level))
		{
			if (StageSelectLevels[i].Character == Characters_Knuckles || StageSelectLevels[i].Character == Characters_Rouge) {

				return Knuckles_LevelBounds_origin(a1, a2);
			}
		}
	}

	return 0;
}

static void __declspec(naked) Knuckles_LevelBounds_ASM()
{
	__asm
	{
		push ecx
		push eax
		call Knuckles_LevelBounds_r
		add esp, 4
		pop ecx
		retn
	}
}

#pragma endregion

void BrokenDownSmoke_r(ObjectMaster* a1) {

	if (MainCharObj2[0]->CharID != Characters_MechTails && MainCharObj2[0]->CharID != Characters_MechEggman)
		DeleteObject_(a1);
	else {
		ObjectFunc(origin, BrokenDownSmoke_t->Target());
		origin(a1);
	}
}


void init_Patches()
{

	if (!isCharaSelect()) {
		Knuckles_LevelBounds_t = new Trampoline((int)0x737B50, (int)0x737B5A, Knuckles_LevelBounds_ASM); //fix boundary
		GoalRing_t = new Trampoline((int)GoalRing_Main, (int)GoalRing_Main + 0x6, GoalRing_Main_r); //make goal ring spawn for knux
		WriteJump((void*)0x6c63de, (void*)0x6c6431); //fix goal ring for the hunters
		LoadEmeraldManager_t = new Trampoline((int)LoadEmeraldManager, (int)LoadEmeraldManager + 0x6, LoadEmeraldManager_r);
	}

	BrokenDownSmoke_t = new Trampoline((int)BrokenDownSmokeExec, (int)BrokenDownSmokeExec + 0x7, BrokenDownSmoke_r);

	WriteData<5>((int*)0x6cdf58, 0x90); //remove speed nerf when destroying boxes	
	WriteData<5>((int*)0x6D6B99, 0x90);
	WriteData<5>((int*)0x77BFFB, 0x90);

	WriteData<3>((int*)0x732ECB, 0x90); //Remove path action, we will manually call it (fix RH last loop)
	WriteData<2>((int*)0x4cd255, 0x90); //remove chara sonic check in cannon core (fix softlock after the first rail)
}