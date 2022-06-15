#pragma once

bool isSA2Miles();
bool isCharaSelect();
bool isRando();
ModelInfo* LoadMDL(const char* name, ModelFormat format);
void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs);
bool isSA1Char(uint8_t charID);
bool isHuntingCharacter();
bool isKnuxAttacking();
bool isAttackingBoxes();
void DoCollisionAttackStuff(EntityData1* data1);

void FreeModelsTex();
void FreeMDL(ModelInfo* pointer);