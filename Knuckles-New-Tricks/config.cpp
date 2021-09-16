#include "pch.h"

Buttons SA1PunchButton = Buttons_B;
Buttons SA2PunchButton = Buttons_X;
Buttons RollButton = Buttons_B;

bool isCustomAnim = true;
bool isRoll = true;
bool isSA2Punch = true;
bool isSA1Punch = true;


static const Buttons ButtonsList[]
{
	Buttons_B,
	Buttons_X,
	Buttons_Y,
	(Buttons)buttons_XB,
};

void ReadConfig(const char* path)
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	isCustomAnim = config->getBool("General", "isCustomAnim", true);
	isSA1Punch = config->getBool("General", "isSA1Punch", true);
	isRoll = config->getBool("General", "isRoll", true);
	isSA2Punch = config->getBool("General", "isSA2Punch", true);

	SA1PunchButton = ButtonsList[config->getInt("ActionRemap", "SA1PunchButton", 0)];
	RollButton = ButtonsList[config->getInt("ActionRemap", "RollButton", 0)];
	SA2PunchButton = ButtonsList[config->getInt("ActionRemap", "SA2PunchButton", 1)];

	delete config;	

	if (SA1PunchButton == SA2PunchButton || RollButton == SA2PunchButton) {
		PrintDebug("Same Input detected Error, Custom attack won't work.");
	}

}