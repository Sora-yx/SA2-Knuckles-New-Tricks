#include "pch.h"

bool isCharaSelect() {
	HMODULE charaMod = GetModuleHandle(L"SA2CharSel");
	HMODULE charaModPlus = GetModuleHandle(L"CharacterSelectPlus");

	if (charaMod || charaModPlus)
		return true;

	return false;
}

bool isSA2Miles() {
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

void ResetMaterialColorOffset()
{
	GlobalMatColorR = 0.0f;
	GlobalMatColorG = 0.0f;
	GlobalMatColorB = 0.0f;
	GlobalMatColorA = 0.0f;
	return;
}

void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs)
{
	vd->x += vs->x;
	vd->y += vs->y;
	vd->z += vs->z;
}