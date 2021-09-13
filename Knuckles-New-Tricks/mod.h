#pragma once

extern bool isCustomAnim;

enum knuxAction {
	Grinding = 86,
	HandGrinding
};

const uint8_t playerMax = 2;

extern AnimationInfo KnuxAnimationList_R[];
extern AnimationInfo RougeAnimationList_R[];


void KnuxTricks_Init();
void Init_Helper();
void Init_StartEndPos();
void Init_NewAnimation();