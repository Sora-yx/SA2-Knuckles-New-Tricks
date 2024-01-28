#include "pch.h"

bool isCharaSelect() {
	HMODULE charaMod = GetModuleHandle(L"SA2CharSel");
	HMODULE charaModPlus = GetModuleHandle(L"CharacterSelectPlus");

	if (charaMod || charaModPlus)
		return true;

	return false;
}

bool isSA2Miles() 
{
	HMODULE miles = GetModuleHandle(L"SA2-Better-Miles");

	if (miles)
		return true;

	return false;
}


bool isRando() {
	HMODULE randoMod = GetModuleHandle(L"Rando");

	if (randoMod)
		return true;

	return false;
}

const char* ModelFormatStrings[]{
	"collision",
	"chunk",
	"battle"
};

//Load Object File
ModelInfo* LoadMDL(const char* name, ModelFormat format) {
	std::string fullPath;

	if (format == ModelFormat_Chunk) {
		fullPath = "resource\\gd_PC\\Models\\";
	}

	fullPath += name;

	switch (format) {
	case ModelFormat_Basic:
		fullPath += ".sa1mdl";
		break;
	case ModelFormat_Chunk:
		fullPath += ".sa2mdl";
		break;
	case ModelFormat_SA2B:
		fullPath += ".sa2bmdl";
		break;
	}

	const char* foo = fullPath.c_str();

	ModelInfo* temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == format) {
		PrintDebug("[Knux New Tricks Mod] Loaded %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}
	else {
		PrintDebug("[Knux New Tricks Mod] Failed loading %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}

	return temp;
}


void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs)
{
	vd->x += vs->x;
	vd->y += vs->y;
	vd->z += vs->z;
}

typedef bool (*isChar) (uint8_t charID);
bool isSA1Char(uint8_t charID) {

	if (!SA1Char)
		return false;

	isChar Obj = (isChar)GetProcAddress(SA1Char, "isSA1Char");

	if (Obj)
	{
		return Obj(charID);
	}

	return false;
}

bool isHuntingCharacter() {

	if (KnuxCharObj2Ptr) {

		CharObj2Base* co2 = &KnuxCharObj2Ptr->base;

		if (co2) {
			if (((MainCharObj2[KnuxCharObj2Ptr->base.PlayerNum]->CharID == Characters_Knuckles) || (MainCharObj2[KnuxCharObj2Ptr->base.PlayerNum]->CharID == Characters_Rouge)))
				return true;
		}
	}

	return false;
}


bool isKnuxAttacking() {

	if (!isHuntingCharacter())
		return false;

	EntityData1* data1 = MainCharObj1[KnuxCharObj2Ptr->base.PlayerNum];

	if (data1->Action == Action_Glide || data1->Action >= Action_Punch && data1->Action <= Action_DrillClaw || data1->Action == Action_Jump || data1->Action == Action_SA1Rolling || data1->Action == Action_SA1Punch) {

		return true;
	}


	return false;
}


bool isAttackingBoxes(char pNum)
{

	EntityData1* data1 = MainCharObj1[pNum];

	if (!data1 || !isHuntingCharacter())
		return false;


	if (data1->Action >= Action_Punch && data1->Action <= Action_Punch3Run || data1->Action == Action_SA1Rolling
		|| data1->Action == Action_SA1Punch) {

		return true;
	}

	return false;
}

void FreeMDL(ModelInfo* pointer) {
	if (pointer) 
		delete(pointer);
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
