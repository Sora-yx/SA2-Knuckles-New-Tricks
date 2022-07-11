#include "pch.h"

static Trampoline* CheckBreakObject_t = nullptr;
static Trampoline* Dynamite_t = nullptr;
static Trampoline* DynamiteHiddenBase_t = nullptr;
static Trampoline* DynamiteSandOcean_t = nullptr;
static Trampoline* PrisonLaneDoor_t = nullptr;
static Trampoline* PrisonLaneDoor4_t = nullptr;
static Trampoline* DoorIG_t = nullptr;
static Trampoline* DoorIG2_t = nullptr;
static Trampoline* RocketIG_t = nullptr;

static Trampoline* PowerSupply_event_t = nullptr;

static Trampoline* Init_LandColMemory_t = nullptr;

void __cdecl PowerSupply_EventTask(ObjectMaster* a1)
{
	if (CurrentCharacter != Characters_MechEggman && CurrentCharacter != Characters_MechTails)
	{
		DeleteObject_(a1);
		return;
	}

	ObjectFunc(origin, PowerSupply_event_t->Target());
	origin(a1);
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
			data->Timer = 0;
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
	if (MainCharObj1[0]->Action == 0x53 || CurrentCharacter > Characters_Shadow && (Controllers[0].press & (Buttons_X | Buttons_B)))
	{
		_asm jmp loc_776D23
	}
	else {
		_asm jmp loc_776D5F
	}
}


void CheckAndSetHackObject(CharObj2Base* co2) {
	if (co2->CharID == Characters_MechTails || co2->CharID == Characters_MechEggman) {
		WriteData<1>((int*)0x715b58, 0x6);
		WriteData<1>((int*)0x715aa8, 0x6);
		WriteData<1>((int*)0x7158bf, 0x6);

		WriteData<1>((int*)0x79b427, 0x6);
		WriteData<1>((int*)0x79b959, 0x6);
		WriteData<1>((int*)0x79be57, 0x6);
		return; //if one player has a mech, we don't need to hack the door
	}

	//hack so non mech character can destroy the doors
	if (CurrentLevel == LevelIDs_HiddenBase) {
		//Hidden base door Col Stuff
		WriteData<1>((int*)0x715b58, 0x1);
		WriteData<1>((int*)0x715aa8, 0x1);
		WriteData<1>((int*)0x7158bf, 0x1);
	}

	if (CurrentLevel == LevelIDs_CannonsCoreT) {
		//CC door col Stuff
		WriteData<1>((int*)0x79b427, 0x1);
		WriteData<1>((int*)0x79b959, 0x1);
		WriteData<1>((int*)0x79be57, 0x1);
	}

	return;
}

//used to load object hack and new anim for knux / rouge
void InitLandColMemory_r()
{
	bool isHunter = false;

	for (int i = 0; i < 4; i++) {

		if (isHunter)
			break;

		if (MainCharObj2[i]) {

			if (MainCharObj2[i]->CharID == Characters_Knuckles || MainCharObj2[i]->CharID == Characters_Rouge)
			{
				Load_KnuxPunch();
				CheckAndSetHackObject(MainCharObj2[i]);
				Load_KnuxNewAnim();
				Fix_TikalAnim(i);
				isHunter = true;
				break;
			}
		}
	}

	if (!isHunter)
	{
		KnuxCharObj2Ptr = nullptr; //reset the pointer because the vanilla game never do lol
	}

	VoidFunc(origin, Init_LandColMemory_t->Target());
	origin();
}


void Init_Objects() {

	CheckBreakObject_t = new Trampoline((int)CheckBreakObject, (int)CheckBreakObject + 0x7, CheckBreakObject_r);
	Dynamite_t = new Trampoline((int)Dynamite_Main, (int)Dynamite_Main + 0x5, CheckBreakDynamite);
	DynamiteHiddenBase_t = new Trampoline((int)DynamiteHiddenBase_Main, (int)DynamiteHiddenBase_Main + 0x5, CheckBreakDynamiteHiddenBase);
	DynamiteSandOcean_t = new Trampoline((int)DynamiteSandOcean_Main, (int)DynamiteSandOcean_Main + 0x6, CheckBreakDynamiteSandOcean);
	PrisonLaneDoor_t = new Trampoline((int)PrisonLaneDoor, (int)PrisonLaneDoor + 0x6, CheckPrisonLaneDoor);
	PrisonLaneDoor4_t = new Trampoline((int)PrisonLaneDoor4, (int)PrisonLaneDoor4 + 0x6, CheckPrisonLaneDoor4);

	DoorIG_t = new Trampoline((int)DoorIG, (int)DoorIG + 0x6, doorIG_r);
	DoorIG2_t = new Trampoline((int)DoorIG2, (int)DoorIG2 + 0x6, doorIG2_r);
	RocketIG_t = new Trampoline((int)RocketIG, (int)RocketIG + 0x6, rocketIG_r);

	Init_LandColMemory_t = new Trampoline((int)0x47BB50, (int)0x47BB57, InitLandColMemory_r);


	if (!isSA2Miles()) {
		PowerSupply_event_t = new Trampoline((int)0x78A450, (int)0x78A455, PowerSupply_EventTask);
		WriteJump(reinterpret_cast<void*>(0x776D1E), CheckGravitySwitch);
		WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
		WriteJump(reinterpret_cast<void*>(0x6A82FA), CheckBreakBirdBox);
	}
}