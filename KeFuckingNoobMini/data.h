#pragma once
#include <Windows.h>
#include "KeInterface.hpp"

static KeInterface Driver = NULL;
DWORD pID;

DWORD ModuleBase = 0x001E0000;

/*e9 ? ? ? ? 8d 45 ? 50 e8 ? ? ? ? 8b 75 ? c7 45 ? ? ? ? ? 8b 46 ? 85 c0*/
#define CInstanceBase				0x4F3884

/*8b 0d ? ? ? ? e8 ? ? ? ? e8 ? ? ? ? 8b e5 5d c3 cc cc cc cc cc cc cc 8b 0d ? ? ? ? e8 ? ? ? ? e9 ? ? ? ? 8b 0d ? ? ? ? e8 ? ? ? ? e9 ? ? ? ? 8b 0d*/
#define CPythonPlayer				0x46E548


/*8b 35 ? ? ? ? 57 8b 3d ? ? ? ? 3b f7 74 ? 8b 0e 85 c9 74 ? 8b 01 6a ? ff 10 83 c6 ? 3b f7 75 ? a1 ? ? ? ? a3 ? ? ? ? a1 ? ? ? ? 5f a3 ? ? ? ? 5e c3 a1 ? ? ? ? 5f 89 35 ? ? ? ? a3 ? ? ? ? 5e c3 cc cc*/
#define MobPointer					0x0047695C


#define Offset_player				0x10

#define Offset_name					0x14
#define Offset_level				0x6C


#define Offset_vid					0x8D4	

#define Offset_instanceType			0x768


#define Offset_getTargetVid			0x0003775C

/*handmade :(*/
#define Offset_setAttackVid			0x84

#define Offset_setAttackStatus		0x88

/*e8 ? ? ? ? 8b 0d ? ? ? ? 8b 01*/
#define Offset_posx					0x7E0
#define Offset_posy					0x7E4

/*handmade :(*/
#define Offset_attackType			0x768



