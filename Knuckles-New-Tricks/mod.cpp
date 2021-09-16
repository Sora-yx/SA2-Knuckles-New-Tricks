#include "pch.h"


HelperFunctions HelperFunctionsGlobal;

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 8)
			MessageBoxA(MainWindowHandle, "WARNING: Your version of the Mod Loader is old, some functionality of Knuckles New Tricks will not be available.\N Please update your Mod Loader for best experience.", "Knux New Tricks Mod", MB_ICONWARNING);

		ReadConfig(path); //get mod settings by the user
		KnuxTricks_Init();
		Init_Helper(); //everything related to objects edit and extra stuff to beat more stage than vanilla.
		Init_StartEndPos();

		Init_NewAnimation();
		Init_ActionRemap();
	}

	__declspec(dllexport) void __cdecl OnFrame() {

	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}