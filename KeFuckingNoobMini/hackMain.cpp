#include "hackMain.h"
#include "KeInterface.hpp"
#include <vector>
#include <string>
#include <array>
#include "data.h"
#include <algorithm>

bool FarmBot_FixedRange = false;
D3DXVECTOR3 FarmBot_FixedRangePos;

bool FarmBot_AttackMob = false;
bool FarmBot_AttackMetin = false;
DWORD FarmBot_Distance = false;

bool CompareInstanceObj(InstanceObj i1, InstanceObj i2) {
	return (i1.Distance < i2.Distance);
}

DWORD getDistance(D3DXVECTOR3 pos_1, D3DXVECTOR3 pos_2) {
	float diff_x = abs(pos_1.x - pos_2.x);
	float diff_y = abs(pos_1.y - pos_2.y);
	DWORD diff_pos = (DWORD)(sqrt((diff_x * diff_x) + (diff_y * diff_y)));
	return diff_pos;
}

void init_hack(LPCSTR RegistryPath, DWORD pid) {
	pID = pid;
	Driver = KeInterface(RegistryPath);
}

DWORD getMainActorInstance() {
	DWORD PlayerBase = Driver.ReadVirtualMemory<DWORD>(pID, ModuleBase + CInstanceBase, sizeof(DWORD));
	return Driver.ReadVirtualMemory<DWORD>(pID, PlayerBase + Offset_player, sizeof(DWORD));
}

DWORD getVid(DWORD instance) {
	if (!instance) { return 0; }
	return Driver.ReadVirtualMemory<DWORD>(pID, instance + Offset_vid, sizeof(DWORD));
}

std::string getName(DWORD instance) {
	if (!instance) { return ""; }
	static std::array<char, 14> name = Driver.ReadVirtualMemory<std::array<char, 14>>(pID, instance + Offset_name, sizeof(14));
	return name.data();
}

DWORD getInstanceType(DWORD instance) {
	if (!instance) { return 0; }
	return  Driver.ReadVirtualMemory<DWORD>(pID, instance + Offset_instanceType, sizeof(DWORD));
}

DWORD getTargetVid() {
	if (!getMainActorInstance()) { return 0; }
	DWORD PythonPlayerPtr = Driver.ReadVirtualMemory<DWORD>(pID, ModuleBase + CPythonPlayer, sizeof(DWORD));
	return  Driver.ReadVirtualMemory<DWORD>(pID, PythonPlayerPtr + Offset_getTargetVid, sizeof(DWORD));
}

D3DXVECTOR3 getPixelPosition(DWORD instance) {
	if (!instance) { return { 0 }; }
	float x = Driver.ReadVirtualMemory<float>(pID, instance + Offset_posx, sizeof(float));
	float y = Driver.ReadVirtualMemory<float>(pID, instance + Offset_posy, sizeof(float));
	return { x, y, 0 };
}

DWORD getAttackVid() {
	if (!getMainActorInstance()) { return 0; }
	DWORD PythonPlayerPtr = Driver.ReadVirtualMemory<DWORD>(pID, ModuleBase + CPythonPlayer, sizeof(DWORD));
	return  Driver.ReadVirtualMemory<DWORD>(pID, PythonPlayerPtr + Offset_setAttackVid, sizeof(DWORD));
}

void setAttackVid(DWORD vid) {
	if (!getMainActorInstance()) { return; }
	DWORD PythonPlayerPtr = Driver.ReadVirtualMemory<DWORD>(pID, ModuleBase + CPythonPlayer, sizeof(DWORD));
	Driver.WriteVirtualMemory<DWORD>(pID, PythonPlayerPtr + Offset_setAttackVid, vid, sizeof(DWORD));
	Driver.WriteVirtualMemory<DWORD>(pID, PythonPlayerPtr + Offset_setAttackStatus, 3, sizeof(DWORD));
}

bool setFixedRange(bool status) {
	if (status) {
		DWORD MainActorInstance = getMainActorInstance();
		if (!MainActorInstance) {
			FarmBot_FixedRange = false;
			FarmBot_FixedRangePos = { 0 };
			return false;
		}
		FarmBot_FixedRangePos = getPixelPosition(MainActorInstance);
		FarmBot_FixedRange = true;
	}
	else {
		FarmBot_FixedRange = false;
		FarmBot_FixedRangePos = { 0 };
	}
	return true;
}

std::vector<InstanceObj> GetMobList(bool AttackMob, bool AttackMetin) {
	std::vector<InstanceObj> ObjList;
	DWORD MainActorInstance = getMainActorInstance();
	if (!MainActorInstance) { return ObjList; }
	D3DXVECTOR3 MainActorPos = getPixelPosition(MainActorInstance);
	DWORD MobPtr = Driver.ReadVirtualMemory<DWORD>(pID, ModuleBase + MobPointer, sizeof(DWORD));
	for (int i = 0; i < 200; i++) {
		DWORD MobInstance = Driver.ReadVirtualMemory<DWORD>(pID, MobPtr + (i * 4), sizeof(DWORD));
		if (!MobInstance)
			continue;

		if (MobInstance == MainActorInstance)
			continue;

		DWORD MobType = getInstanceType(MobInstance);

		if ((MobType == 0 && !AttackMob) || (MobType == 2 && !AttackMetin) || (MobType != 0 && MobType != 2))
			continue;

		DWORD MobVid = getVid(MobInstance);
		if (!MobVid)
			continue;

		D3DXVECTOR3 MobPos = getPixelPosition(MobInstance);
		if (!MobPos.x || !MobPos.y)
			continue;

		DWORD MobDistance = getDistance(MainActorPos, MobPos);

		ObjList.push_back({ MobInstance, MobVid, MobPos, MobType, MobDistance });
	}
	if (ObjList.size() > 1) {
		std::sort(ObjList.begin(), ObjList.end(), CompareInstanceObj);
	}
	return ObjList;
}

InstanceObj getAttacableMob(DWORD Distance, bool AttackMob, bool AttackMetin) {
	DWORD MainActorInstance = getMainActorInstance();
	if (!MainActorInstance) { return { 0 }; }

	D3DXVECTOR3 MainActorPos = getPixelPosition(MainActorInstance);

	std::vector<InstanceObj> MobList = GetMobList(AttackMob, AttackMetin);
	if (!MobList.size()) { return { 0 }; }

	for (InstanceObj Mob : MobList) {
		DWORD MobDistance = Mob.Distance;
		if (FarmBot_FixedRange)
			MobDistance = getDistance(FarmBot_FixedRangePos, Mob.Pos);

		if (MobDistance <= Distance)
			return Mob;
	}
	return { 0 };
}

void FarmBotThread(DWORD distance) {
	if (!getMainActorInstance()) { return; }
	if (getAttackVid()) { return; }
	InstanceObj MobObj = getAttacableMob(distance, FarmBot_AttackMob, FarmBot_AttackMetin);
	if (MobObj.VID) {
		setAttackVid(MobObj.VID);
	}
}