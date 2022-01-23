#pragma once
#include <Windows.h>
#include "KeInterface.hpp"

static KeInterface Driver = NULL;
DWORD pID;

DWORD ModuleBase = 0;

/*8b 0d ? ? ? ? e8 ? ? ? ? 3b d8*/
#define CInstanceBase				0x16F7754

/*8b 0d ? ? ? ? e8 ? ? ? ? e8 ? ? ? ? 8b e5 5d c3 cc cc cc cc cc cc cc 8b 0d ? ? ? ? e8 ? ? ? ? e9 ? ? ? ? 8b 0d ? ? ? ? e8 ? ? ? ? e9 ? ? ? ? 8b 0d*/
#define CPythonPlayer				0x16F7780


/*8b 35 ? ? ? ? 57 8b 3d ? ? ? ? 3b f7 74 ? 8b 0e 85 c9 74 ? 8b 01 6a ? ff 10 83 c6 ? 3b f7 75 ? a1 ? ? ? ? a3 ? ? ? ? a1 ? ? ? ? 5f a3 ? ? ? ? 5e c3 a1 ? ? ? ? 5f 89 35 ? ? ? ? a3 ? ? ? ? 5e c3 cc cc*/
#define MobPointer					0x1610958


#define Offset_player				0x18
#define Offset_base					0x214	

#define Offset_name					0x24
#define Offset_level				0x58

/*e8 ? ? ? ? 8b 7d ? 8b d8 8d 4f*/
/*#define Offset_vid_1				0x375
#define Offset_vid_2				0x438
#define Offset_vid_3				0x36C
#define Offset_vid_4				0x2F0
#define Offset_vid_5				0x3F8*/
#define Offset_vid_base				0x3D4
#define Offset_vid					0x35C


/*e8 ? ? ? ? 85 c0 75 ? 8b ce e8 ? ? ? ? 85 c0 74 ? 56*/
#define Offset_instanceType_base	0x3A8
#define Offset_instanceType			0x35C

/*e8 ? ? ? ? 84 c0 75 ? 8b 46 ? 8d 4e ? 68 ? ? ? ? ff 50 ? 50*/
#define Offset_getTargetVid_base	0x74
#define Offset_getTargetVid			0x0004B004

/*handmade :(*/
#define Offset_setAttackVid			0x0004B0B4

#define Offset_setAttackStatus		0x54

/*e8 ? ? ? ? 8b 0d ? ? ? ? 8b 01*/
#define Offset_posx					0x418
#define Offset_posy					0x41C

/*handmade :(*/
#define Offset_isDead				0x350

/*e8 ? ? ? ? eb ? 80 7d ? ? 8b cb*/
#define PressActorCall				0x1D3200 

/*e8 ? ? ? ? eb ? 8d 45 ? 50 e8 ? ? ? ? 84 c0*/
#define ClickActorCall				0x1D2FD0 


/*e8 ? ? ? ? 84 c0 74 ? e8 ? ? ? ? 89 86*/
#define MainThreadPtr				0x16FA79C
#define MainProcessCall				0xEE1F0
#define MainThread					0xEE1AB
