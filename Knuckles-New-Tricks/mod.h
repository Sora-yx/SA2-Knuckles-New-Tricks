#pragma once

extern HelperFunctions HelperFunctionsGlobal;
extern bool isCustomAnim;
extern int isKnuxAdventure;
extern bool isRoll;
extern bool isSA2Punch;
extern bool isSA1Punch;

extern Buttons SA1PunchButton;
extern Buttons SA2PunchButton;
extern Buttons RollButton;

enum customButton {
	buttons_XB = 514,
};


enum knuxAction {
	Grinding = 86,
	HandGrinding,
	Action_SA1Rolling,
	Action_SA1Punch
};

const uint8_t playerMax = 2;

extern AnimationInfo KnuxAnimationList_R[];
extern AnimationInfo RougeAnimationList_R[];

void KnuxTricks_Init();
void Init_Helper();
void Init_StartEndPos();
void Init_NewAnimation();
signed int __cdecl Knux_CheckNextActions_r(EntityData2* a1, KnucklesCharObj2* a2, EntityData1* a3, CharObj2Base* a4);
void Load_KnuxPunch();
void DoCollisionAttackStuff(EntityData1* data1);
void Init_ActionRemap();
void ReadConfig(const char* path);