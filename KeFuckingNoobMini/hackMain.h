#pragma once
#include <Windows.h>
#include <string>
#include <vector>
typedef struct D3DXVECTOR3 {
	float x;
	float y;
	float z;
} D3DXVECTOR3, * LPD3DXVECTOR3;

typedef struct InstanceObj {
	DWORD Instance;
	DWORD VID;
	D3DXVECTOR3 Pos;
	DWORD Type;
	DWORD Distance;
}InstanceObj, *PInstanceObj;



void init_hack(LPCSTR RegistryPath, DWORD pid);


DWORD getMainActorInstance();
DWORD getVid(DWORD instance);
std::string getName(DWORD instance);
DWORD getInstanceType(DWORD instance);
DWORD getTargetVid();
D3DXVECTOR3 getPixelPosition(DWORD instance);

DWORD getAttackVid();
void setAttackVid(DWORD vid);

bool setFixedRange(bool status);

std::vector<InstanceObj> GetMobList(bool AttackMob, bool AttackMetin);
InstanceObj getAttacableMob(DWORD Distance, bool AttackMob, bool AttackMetin);

void FarmBotThread(DWORD distance);