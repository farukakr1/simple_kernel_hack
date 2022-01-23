#pragma once
#include <Windows.h>
#include "KeInterface.hpp"

static KeInterface Driver = NULL;
DWORD pID;

DWORD ModuleBase = 0x00E90000;

/*e9 ? ? ? ? 8d 45 ? 50 e8 ? ? ? ? 8b 75 ? c7 45 ? ? ? ? ? 8b 46 ? 85 c0*/
#define CInstanceBase				0x1C6A098

/*8b 0d ? ? ? ? e8 ? ? ? ? e8 ? ? ? ? 8b e5 5d c3 cc cc cc cc cc cc cc 8b 0d ? ? ? ? e8 ? ? ? ? e9 ? ? ? ? 8b 0d ? ? ? ? e8 ? ? ? ? e9 ? ? ? ? 8b 0d*/
#define CPythonPlayer				0x1C6A0C4


/*8b 35 ? ? ? ? 57 8b 3d ? ? ? ? 3b f7 74 ? 8b 0e 85 c9 74 ? 8b 01 6a ? ff 10 83 c6 ? 3b f7 75 ? a1 ? ? ? ? a3 ? ? ? ? a1 ? ? ? ? 5f a3 ? ? ? ? 5e c3 a1 ? ? ? ? 5f 89 35 ? ? ? ? a3 ? ? ? ? 5e c3 cc cc*/
#define MobPointer					0x01B31C4C


#define Offset_player				0x18
#define Offset_base					0x214	

#define Offset_name					0x24
#define Offset_level				0x58

/*e8 ? ? ? ? 8b 7d ? 8b d8 8d 4f*/
#define Offset_vid_1				0x375
#define Offset_vid_2				0x438
#define Offset_vid_3				0x36C
#define Offset_vid_4				0x2F0
#define Offset_vid_5				0x3F8

/*e8 ? ? ? ? 85 c0 75 ? 8b ce e8 ? ? ? ? 85 c0 74 ? 56*/
#define Offset_instanceType_base	0x440
#define Offset_instanceType			0x36C

/*e8 ? ? ? ? 84 c0 75 ? 8b 46 ? 8d 4e ? 68 ? ? ? ? ff 50 ? 50*/
#define Offset_getTargetVid_base	0x74
#define Offset_getTargetVid			0x0004B004

/*handmade :(*/
#define Offset_setAttackVid			0x0004B0B4

#define Offset_setAttackStatus		0x54

/*e8 ? ? ? ? 8b 0d ? ? ? ? 8b 01*/
#define Offset_posx					0x38C
#define Offset_posy					0x390

/*handmade :(*/
#define Offset_attackType			0x4F8

/*handmade :(*/
#define Offset_isDead				0x418 //0x62C

/*e8 ? ? ? ? eb ? 80 7d ? ? 8b cb*/
#define PressActorCall				0x1D0AF0 

/*e8 ? ? ? ? eb ? 8d 45 ? 50 e8 ? ? ? ? 84 c0*/
#define ClickActorCall				0x1D0AF0 


/*e8 ? ? ? ? 84 c0 74 ? e8 ? ? ? ? 89 86*/
#define MainThreadPtr				0x1C6D0E0
#define MainProcessCall				0xEBB80
#define MainThread					0xEBB3B
