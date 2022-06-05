#include "pch.h"


HelperFunctions HelperFunctionsGlobal;
const char* error = "[Knux New Tricks]: WARNING: Your version of the Mod Loader is old, the mod won't work properly.\nPlease update your Mod Loader for the best experience.";

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		Sleep(10);

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 8) {
			PrintDebug(error);
			MessageBoxA(MainWindowHandle, error, "Knuckles New Tricks Mod", MB_ICONWARNING);
		}

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