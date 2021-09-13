#include "pch.h"

Trampoline* Knux_Main_t;
Trampoline* Knux_CheckNextActions_t;
Trampoline* Knux_RunsAction_t;


void Knux_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Knux_Main_t->Target());
	origin(obj);

}

void KnuxTricks_Init() {
	Knux_Main_t = new Trampoline((int)Knuckles_Main, (int)Knuckles_Main + 0x6, Knux_Main_r);


	//Custom anim + new moves
	Init_NewAnimation();

	Init_StartEndPos();
}