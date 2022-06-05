#pragma once

extern HelperFunctions HelperFunctionsGlobal;
extern bool isCustomAnim;
extern int isKnuxAdventure;
extern bool isRoll;
extern bool isSA1Punch;
extern bool fastGlasses;
extern bool noFilter;

extern Buttons SA1PunchButton;
extern Buttons SA2PunchButton;
extern Buttons RollButton;

enum customButton {
	buttons_XB = 514,
};


enum knuxAction {
	Grinding = 90,
	HandGrinding,
	Action_SA1Rolling,
	Action_SA1Punch
};

const uint8_t playerMax = 2;

extern AnimationInfo KnuxAnimationList_R[];
extern AnimationInfo RougeAnimationList_R[];

void KnuxTricks_Init();
void Init_Objects();
void Init_StartEndPos();
void Init_NewAnimation();

void Load_KnuxPunch();
void DoCollisionAttackStuff(EntityData1* data1);
void Init_ActionRemap();
void ReadConfig(const char* path);
void RestorePhysic(CharObj2Base* co2);
signed int Fast_SunglassesCheckInput(CharObj2Base* co2, EntityData1* data1);

void init_SunglassesChange();

#define cur_matrix _nj_current_matrix_ptr_

extern HMODULE SA1Char;
void init_Patches();
void Load_KnuxNewAnim();
extern uint8_t alwaysHunter;