#include "pch.h"

Trampoline* CheckBreakObject_t;
Trampoline* Dynamite_t;
Trampoline* DynamiteHiddenBase_t;
Trampoline* DynamiteSandOcean_t;
Trampoline* PrisonLaneDoor_t;
Trampoline* PrisonLaneDoor4_t;
Trampoline* DoorIG_t;
Trampoline* DoorIG2_t;
Trampoline* RocketIG_t;
Trampoline* BrokenDownSmoke_t;
Trampoline* LoadCharacters_t;

bool isHuntingCharacter() {

	if (MainCharObj2[0]->CharID == Characters_Knuckles || MainCharObj2[0]->CharID == Characters_Rouge)
		return true;

	return false;
}


bool isKnuxAttacking() {

	if (!isHuntingCharacter())
		return false;

	for (uint8_t i = 0; i < playerMax; i++) {

		EntityData1* data1 = MainCharObj1[i];

		if (!data1)
			continue;

		if (data1->Action == Action_Glide || data1->Action >= Action_Punch && data1->Action <= Action_DrillClaw || data1->Action == Action_Jump || data1->Action == Action_SA1Rolling || data1->Action == Action_SA1Punch) {

			return true;
		}
	}


	return false;
}


bool isAttackingBoxes() {

	if (!isHuntingCharacter())
		return false;

	EntityData1* data1 = MainCharObj1[0];

	if (data1->Action >= Action_Punch && data1->Action <= Action_Punch3Run || data1->Action == Action_SA1Rolling
		|| data1->Action == Action_SA1Punch) {

		return true;
	}

	return false;
}



void DoCollisionAttackStuff(EntityData1* data1) {
	data1->Status |= Status_Attack;
	data1->Collision->CollisionArray[0].damage &= 0xFCu;
	data1->Collision->CollisionArray[0].damage |= 0xCu;
	data1->Collision->CollisionArray[0].damage |= 0xEF;
	data1->Collision->CollisionArray[1].center = data1->Position;
	data1->Collision->CollisionArray[1].attr &= 0xFFFFFFEF;
	return;
}


Bool __cdecl CheckBreakObject_r(ObjectMaster* obj, ObjectMaster* other)
{

	if (isAttackingBoxes() && GetCollidingPlayer(obj))
		return 1;

	FunctionPointer(Bool, original, (ObjectMaster * obj, ObjectMaster * other), CheckBreakObject_t->Target());
	return original(obj, other);
}

void CheckBreakDynamite(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (obj) {
		if (data->Action == 0 && isKnuxAttacking() && GetCollidingPlayer(obj)) {
			data->Status |= 4u;
			obj->EntityData2->gap_44[0] = 0;
		}
	}

	ObjectFunc(origin, Dynamite_t->Target());
	origin(obj);
}

void CheckBreakDynamiteHiddenBase(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (obj) {
		if (data->NextAction != 7 && isKnuxAttacking() && GetCollidingPlayer(obj)) {
			data->field_6 = 0;
			data->NextAction = 7;
		}
	}

	ObjectFunc(origin, DynamiteHiddenBase_t->Target());
	origin(obj);
}

void CheckBreakDynamiteSandOcean(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (obj) {
		if (data->Action == 0 && isKnuxAttacking() && GetCollidingPlayer(obj)) {
			data->Status |= 4u;
			obj->EntityData2->gap_44[0] = 0;
		}
	}

	ObjectFunc(origin, DynamiteSandOcean_t->Target());
	origin(obj);
}

void CheckAndOpenPrisonLaneDoor(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	EntityData2* data2 = obj->Data2.Entity;

	if (obj) {

		if (!isHuntingCharacter())
			return;

		if (data->Action == 0 && data->Rotation.x == 3)
		{
			data->Rotation.x = 32;
		}
		else  if (data->Action < 1 && GetCollidingPlayer(obj)) {
			data->Rotation.x = 3;
			data->Action = 1;
		}
	}
}


void CheckPrisonLaneDoor(ObjectMaster* obj) {

	CheckAndOpenPrisonLaneDoor(obj);

	ObjectFunc(origin, PrisonLaneDoor_t->Target());
	origin(obj);
}


void CheckPrisonLaneDoor4(ObjectMaster* obj) {

	CheckAndOpenPrisonLaneDoor(obj);

	ObjectFunc(origin, PrisonLaneDoor4_t->Target());
	origin(obj);
}

void CheckAndOpenIronGateDoor(ObjectMaster* obj) {

	if (!isHuntingCharacter())
		return;

	EntityData1* data = obj->Data1.Entity;

	if (GetCollidingPlayer(obj)) {
		data->NextAction = 15;
	}
}


void doorIG_r(ObjectMaster* obj) {

	CheckAndOpenIronGateDoor(obj);

	ObjectFunc(origin, DoorIG_t->Target());
	origin(obj);
}

void doorIG2_r(ObjectMaster* obj) {

	CheckAndOpenIronGateDoor(obj);

	ObjectFunc(origin, DoorIG2_t->Target());
	origin(obj);
}

void rocketIG_r(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (isHuntingCharacter()) {

		if (GetCollidingPlayer(obj) && data->Action == 5)
		{
			data->Action = 6;
		}
	}

	ObjectFunc(origin, RocketIG_t->Target());
	origin(obj);
}

void BrokenDownSmoke_r(ObjectMaster* a1) {

	if (MainCharObj2[0]->CharID != Characters_MechTails && MainCharObj2[0]->CharID != Characters_MechEggman)
		DeleteObject_(a1);
	else {
		ObjectFunc(origin, BrokenDownSmoke_t->Target());
		origin(a1);
	}
}


static const void* const loc_6A82CC = (void*)0x6A82CC;
static const void* const loc_6A82FF = (void*)0x6A82FF;
__declspec(naked) void  CheckBreakBirdBox() {



	if (MainCharObj1[0]->Action == Action_DrillClaw || isKnuxAttacking())
	{
		_asm jmp loc_6A82FF
	}
	else {
		_asm jmp loc_6A82CC
	}

}


static const void* const loc_776339 = (void*)0x776339;
static const void* const loc_776580 = (void*)0x776580;
__declspec(naked) void  CheckBreakCGGlasses() {
	if (MainCharObj1[0]->Action == 13 || isKnuxAttacking())
	{
		_asm jmp loc_776339
	}
	else {
		_asm jmp loc_776580
	}
}


static const void* const loc_776D23 = (void*)0x776D23;
static const void* const loc_776D5F = (void*)0x776D5F;
__declspec(naked) void  CheckGravitySwitch() {
	if (MainCharObj1[0]->Action == 0x53 || (Controllers[0].press & (Buttons_X | Buttons_B)))
	{
		_asm jmp loc_776D23
	}
	else {
		_asm jmp loc_776D5F
	}
}


void LoadCharacters_r() {

	auto original = reinterpret_cast<decltype(LoadCharacters_r)*>(LoadCharacters_t->Target());
	original();

	Load_KnuxPunch();

	if (isCharaSelect()) {
		CheckAndForce_NewAnimList();

	}

	return;
}

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

Trampoline* LoadEmeraldManager_t;

void LoadEmeraldManager_r() {

	if (CheckEmeraldManager()) {
		auto original = reinterpret_cast<decltype(LoadEmeraldManager_r)*>(LoadEmeraldManager_t->Target());
		original();
	}
}

//Credits: MainMemory Character Select Mod

static const void* const Knuckles_LevelBounds_o = (void*)0x737B50;
__declspec(naked) void Knuckles_LevelBounds_r()
{
	__asm
	{
		mov	ebx, [CurrentLevel]
		mov ebx, [ebx]
		cmp	bx, LevelIDs_PumpkinHill
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_AquaticMine
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_SecurityHall
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_WildCanyon
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_DryLagoon
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_DeathChamber
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_EggQuarters
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_MeteorHerd
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_WildCanyon2P
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_MadSpace
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_DryLagoon2P
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_PoolQuest
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_PlanetQuest
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_DeathChamber2P
		je	j_Knuckles_LevelBounds
		xor eax, eax
		retn
		j_Knuckles_LevelBounds :
		jmp[Knuckles_LevelBounds_o]
	}
}

static const void* const loc_6C6431 = (void*)0x6C6431;
static const void* const loc_6C6412 = (void*)0x6C6412;
__declspec(naked) void loc_6C63E7()
{
	__asm
	{
		mov eax, MissionNum
		cmp	long ptr[eax], 1
		je	_loc_6C6412
		mov	eax, [ebp + 8]
		cdq
		mov	esi, 3
		idiv	esi
		cmp	edx, 1
		je _loc_6C6431
		mov	eax, CurrentLevel
		mov eax, [eax]
		cmp	ax, LevelIDs_PumpkinHill
		je	short loc_6C659A
		cmp	ax, LevelIDs_AquaticMine
		je	short loc_6C659A
		cmp	ax, LevelIDs_SecurityHall
		je	short loc_6C659A
		cmp	ax, LevelIDs_WildCanyon
		je	short loc_6C659A
		cmp	ax, LevelIDs_DryLagoon
		je	short loc_6C659A
		cmp	ax, LevelIDs_DeathChamber
		je	short loc_6C659A
		cmp	ax, LevelIDs_EggQuarters
		je	short loc_6C659A
		cmp	ax, LevelIDs_MeteorHerd
		je	short loc_6C659A
		cmp	ax, LevelIDs_WildCanyon2P
		je	short loc_6C659A
		cmp	ax, LevelIDs_MadSpace
		je	short loc_6C659A
		cmp	ax, LevelIDs_DryLagoon2P
		je	short loc_6C659A
		cmp	ax, LevelIDs_PoolQuest
		je	short loc_6C659A
		cmp	ax, LevelIDs_PlanetQuest
		je	short loc_6C659A
		cmp	ax, LevelIDs_DeathChamber2P
		jne	_loc_6C6431

		loc_6C659A :
		pop	esi
			pop	ebp
			pop	ebx
			retn
			_loc_6C6412 :
		mov ecx, 2
			jmp loc_6C6412
			_loc_6C6431 :
		mov ecx, 2
			jmp[loc_6C6431]
	}
}


void Init_Helper() {

	CheckBreakObject_t = new Trampoline((int)CheckBreakObject, (int)CheckBreakObject + 0x7, CheckBreakObject_r);
	Dynamite_t = new Trampoline((int)Dynamite_Main, (int)Dynamite_Main + 0x5, CheckBreakDynamite);
	DynamiteHiddenBase_t = new Trampoline((int)DynamiteHiddenBase_Main, (int)DynamiteHiddenBase_Main + 0x5, CheckBreakDynamiteHiddenBase);
	DynamiteSandOcean_t = new Trampoline((int)DynamiteSandOcean_Main, (int)DynamiteSandOcean_Main + 0x6, CheckBreakDynamiteSandOcean);
	PrisonLaneDoor_t = new Trampoline((int)PrisonLaneDoor, (int)PrisonLaneDoor + 0x6, CheckPrisonLaneDoor);
	PrisonLaneDoor4_t = new Trampoline((int)PrisonLaneDoor4, (int)PrisonLaneDoor4 + 0x6, CheckPrisonLaneDoor4);

	DoorIG_t = new Trampoline((int)DoorIG, (int)DoorIG + 0x6, doorIG_r);
	DoorIG2_t = new Trampoline((int)DoorIG2, (int)DoorIG2 + 0x6, doorIG2_r);
	RocketIG_t = new Trampoline((int)RocketIG, (int)RocketIG + 0x6, rocketIG_r);


	WriteData<5>((int*)0x6cdf58, 0x90); //remove speed nerf when destroying boxes	
	WriteData<5>((int*)0x6D6B99, 0x90);
	WriteData<5>((int*)0x77BFFB, 0x90);

	WriteData<3>((int*)0x732ECB, 0x90); //Remove path action, we will manually call it (fix RH last loop)
	WriteData<2>((int*)0x4cd255, 0x90); //remove chara sonic check in cannon core (fix softlock after the first rail)


	if (!isSA2Miles()) {
		WriteData<5>((void*)0x7899e8, 0x90); //remove powersupply
		BrokenDownSmoke_t = new Trampoline((int)BrokenDownSmokeExec, (int)BrokenDownSmokeExec + 0x7, BrokenDownSmoke_r);
		WriteJump(reinterpret_cast<void*>(0x776D1E), CheckGravitySwitch);
	}

	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
	WriteJump(reinterpret_cast<void*>(0x6A82FA), CheckBreakBirdBox);

	if (!isCharaSelect()) {

		//fix Knuckles boundary black screen thing
		WriteCall((void*)0x729D16, Knuckles_LevelBounds_r);
		WriteCall((void*)0x729DC5, Knuckles_LevelBounds_r);
		WriteCall((void*)0x72B0F1, Knuckles_LevelBounds_r);
		WriteCall((void*)0x72B2E8, Knuckles_LevelBounds_r);

		WriteJump((void*)0x6C63E7, loc_6C63E7); // Goal Ring

		LoadEmeraldManager_t = new Trampoline((int)LoadEmeraldManager, (int)LoadEmeraldManager + 0x6, LoadEmeraldManager_r);
	}

	LoadCharacters_t = new Trampoline((int)LoadCharacters, (int)LoadCharacters + 0x6, LoadCharacters_r);
}