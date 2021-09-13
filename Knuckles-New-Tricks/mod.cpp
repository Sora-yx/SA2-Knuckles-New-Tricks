#include "pch.h"

bool isCustomAnim = true;
HelperFunctions HelperFunctionsGlobal;

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{

		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isCustomAnim = config->getBool("General", "isCustomAnim", true);
		delete config;

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 8)
			MessageBoxA(MainWindowHandle, "WARNING: Your version of the Mod Loader is old, some functionality of Knuckles New Tricks will not be available.\N Please update your Mod Loader for best experience.", "Knux New Tricks Mod", MB_ICONWARNING);

		KnuxTricks_Init();
		Init_Helper();
		Init_StartEndPos();
		Init_NewAnimation();
	}

	__declspec(dllexport) void __cdecl OnFrame() {

	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}