#pragma once


struct sp_info
{
	NJS_TEXLIST* texlist;
	NJS_TEXANIM* texanim;
	int animnum;
	int srcblend;
	int dstblend;
};

struct sp_task;

struct sp_link
{
	sp_link* next;
	sp_task* head;
	void(__cdecl* exec)(sp_link*);
	unsigned int numtask;
	sp_info* info;
	unsigned int sysflag;
	void* work;
};


union sp_task_work
{
	__int16 w[2];
	int l;
	float f;
	void* ptr;
};



struct __declspec(align(4)) sp_task
{
	sp_task* next;
	void(__cdecl* exec)(sp_task*, sp_link*);
	unsigned __int8 mode;
	unsigned __int8 flag;
	__int16 no;
	int ang;
	float frame;
	float scl;
	NJS_POINT3 pos;
	NJS_POINT3 spd;
	NJS_ARGB argb;
	float offset;
	sp_task_work work[2];
	unsigned __int8 wrtZflg;
};

struct particle_info
{
	float scl;
	float sclspd;
	float animspd;
	float friction;
	float yacc;
	NJS_POINT3 pos;
	NJS_POINT3 velo;
	NJS_ARGB argb;
};

struct particle_entry
{
	sp_info* info;
	unsigned int wksize;
	void(__cdecl* exec)(sp_link*);
	sp_link* link;
};

void CreateSmoke(NJS_POINT3* pos, NJS_POINT3* velo, double scl);