#pragma once


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