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

	DWORD esi = instance + Offset_base;

	DWORD eax = Driver.ReadVirtualMemory<uint8_t>(pID, esi + Offset_vid_1, sizeof(uint8_t));
	DWORD edi = Driver.ReadVirtualMemory<uint8_t>(pID, esi + Offset_vid_2, sizeof(uint8_t));

	eax = Driver.ReadVirtualMemory<DWORD>(pID, esi + eax * 4 + Offset_vid_3, sizeof(DWORD));

	for (int edx = 0; edx < 0x19; edx++) {
		if (edx == edi) {
			eax -= Driver.ReadVirtualMemory<uint8_t>(pID, esi + Offset_vid_4, sizeof(uint8_t));
		}
		else if (edx < 0x5) {
			eax -= 0x3;
		}
		else if (edx > 0xE) {
			eax += 0x7;
		}
		else {
			eax -= Driver.ReadVirtualMemory<uint8_t>(pID, esi + edx + Offset_vid_5, sizeof(uint8_t));
		}
	}
	return eax;
}

std::string getName(DWORD instance) {
	if (!instance) { return ""; }
	static std::array<char, 14> name = Driver.ReadVirtualMemory<std::array<char, 14>>(pID, instance + Offset_name, sizeof(14));
	return name.data();
}

DWORD getInstanceType(DWORD instance) {
	if (!instance) { return 0; }
	DWORD eax = Driver.ReadVirtualMemory<uint8_t>(pID, instance + Offset_base + Offset_instanceType_base, sizeof(uint8_t));
	return  Driver.ReadVirtualMemory<DWORD>(pID, instance + Offset_base + eax * 4 + Offset_instanceType, sizeof(DWORD));
}

DWORD getTargetVid() {
	if (!getMainActorInstance()) { return 0; }
	DWORD PythonPlayerPtr = Driver.ReadVirtualMemory<DWORD>(pID, ModuleBase + CPythonPlayer, sizeof(DWORD));
	DWORD eax = Driver.ReadVirtualMemory<uint8_t>(pID, PythonPlayerPtr + Offset_getTargetVid_base, sizeof(uint8_t));
	return  Driver.ReadVirtualMemory<DWORD>(pID, PythonPlayerPtr + eax * 4 + Offset_getTargetVid, sizeof(DWORD));
}

D3DXVECTOR3 getPixelPosition(DWORD instance) {
	if (!instance) { return { 0 }; }
	float x = Driver.ReadVirtualMemory<float>(pID, instance + Offset_base + Offset_posx, sizeof(float));
	float y = Driver.ReadVirtualMemory<float>(pID, instance + Offset_base + Offset_posy, sizeof(float));
	return { abs(x), abs(y), 0 };
}

DWORD getAttackStatus() {
	if (!getMainActorInstance()) { return 0; }
	DWORD PythonPlayerPtr = Driver.ReadVirtualMemory<DWORD>(pID, ModuleBase + CPythonPlayer, sizeof(DWORD));
	return  Driver.ReadVirtualMemory<short>(pID, PythonPlayerPtr + Offset_setAttackStatus, sizeof(short));
}

bool getIsDead(DWORD instance) {
	if (!instance) { return { 0 }; }
	return Driver.ReadVirtualMemory<bool>(pID, instance + Offset_base + Offset_isDead, sizeof(bool));
}

//fonksiyonun mantýðý kýsaca oyunun ana döngüsüne ara bir komut ekliyoruz ve bu komutla istediðimiz herþeyi internal olarak çaðýrabiliyoruz
//kötü yazýlmýþ olabilir kusuruma bakmayýn artýk :)
void PressActor(DWORD vid) {
	if (!vid) { return; }
	ULONG AllocatedMem = 0;
	for (int i = 0; i < 10; i++) {
		AllocatedMem = Driver.AllocMem(pID, PAGE_SIZE);
		if (AllocatedMem) {
			break;
		}
		else {
			Sleep(50);
		}
	}
	ULONG OldProtect;
	ULONG dummy;
	if (AllocatedMem) {

		unsigned char Buffer[44] = {
			0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov ecx, classPtr
			0x68, 0x01, 0x00, 0x00, 0x00, //push 0x1
			0x68, 0x00, 0x00, 0x00, 0x00, //push targetVID
			0x68, 0x00, 0x00, 0x00, 0x00, //push MainActorPtr
			0xE8, 0x00, 0x00, 0x00, 0x00, //call OnPressActor
			//main func
			0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov ecx, classPtr
			0xE8, 0x00, 0x00, 0x00, 0x00, //call Process Call
			0x90, 0x90,
			0xE9, 0x00, 0x00, 0x00, 0x00 //jmp main loop
		};



		DWORD buffer_offset = 0;


		buffer_offset = (sizeof(Buffer) - 42);
		*(DWORD*)(Buffer + buffer_offset) = (DWORD)(ModuleBase + CPythonPlayer); //mov  ecx, classPtr

		buffer_offset = (sizeof(Buffer) - 32);
		*(DWORD*)(Buffer + buffer_offset) = (DWORD)(vid); //push targetvid

		buffer_offset = (sizeof(Buffer) - 27);
		*(DWORD*)(Buffer + buffer_offset) = (DWORD)(getMainActorInstance()); //push MainActorPtr

		buffer_offset = (sizeof(Buffer) - 22);
		*(DWORD*)(Buffer + buffer_offset) = (DWORD)((ULONG_PTR)(ModuleBase + PressActorCall) - ((ULONG_PTR)AllocatedMem + buffer_offset) - 5 + 1); //call onpressactor


		buffer_offset = (sizeof(Buffer) - 16);
		*(DWORD*)(Buffer + buffer_offset) = (DWORD)(ModuleBase + MainThreadPtr); //mov ecx, classPtr

		buffer_offset = (sizeof(Buffer) - 11);
		*(DWORD*)(Buffer + buffer_offset) = (DWORD)((ULONG_PTR)(ModuleBase + MainProcessCall) - ((ULONG_PTR)AllocatedMem + buffer_offset) - 5 + 1); //call Process Call

		buffer_offset = (sizeof(Buffer) - 4);
		*(DWORD*)(Buffer + buffer_offset) = (DWORD)((ULONG_PTR)(ModuleBase + MainThread + 0x5) - ((ULONG_PTR)AllocatedMem + buffer_offset) - 5 + 1); //jmp main loop

		std::array<unsigned char, sizeof(Buffer)> ThreadBuffer;
		for (int i = 0; i < sizeof(Buffer); i++) {
			ThreadBuffer.at(i) = Buffer[i];
		}

		Driver.WriteVirtualMemory<std::array<unsigned char, sizeof(Buffer)>>(pID, AllocatedMem, ThreadBuffer, sizeof(Buffer));


		DWORD MainThreadAddr = ModuleBase + MainThread;


		unsigned char BufferOld[5] = {
			0xE8, 0x00, 0x00, 0x00, 0x00
		};
		*(DWORD*)(BufferOld + 0x1) = (DWORD)((ULONG_PTR)(ModuleBase + MainProcessCall) - ((ULONG_PTR)MainThreadAddr) - 5);
		std::array<unsigned char, sizeof(BufferOld)> BufferOldArray;
		for (int i = 0; i < sizeof(BufferOld); i++) {
			BufferOldArray.at(i) = BufferOld[i];
		}

		unsigned char BufferNew[5] = {
			0xE9, 0x00, 0x00, 0x00, 0x00
		};

		*(DWORD*)(BufferNew + 0x1) = (DWORD)((ULONG_PTR)AllocatedMem - ((ULONG_PTR)MainThreadAddr) - 5);
		std::array<unsigned char, sizeof(BufferNew)> BufferNewArray;
		for (int i = 0; i < sizeof(BufferNew); i++) {
			BufferNewArray.at(i) = BufferNew[i];
		}

		Driver.VirtualProtect(pID, MainThreadAddr, sizeof(BufferNewArray), PAGE_EXECUTE_READWRITE, &OldProtect);
		Driver.WriteVirtualMemory<std::array<unsigned char, 5>>(pID, MainThreadAddr, BufferNewArray, 5);

		Sleep(50);

		Driver.WriteVirtualMemory<std::array<unsigned char, sizeof(BufferOld)>>(pID, MainThreadAddr, BufferOldArray, sizeof(BufferOld));
		Driver.VirtualProtect(pID, MainThreadAddr, sizeof(BufferNewArray), OldProtect, &dummy);
	}
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

std::vector<InstanceObj> getMobList(bool AttackMob, bool AttackMetin) {
	std::vector<InstanceObj> ObjList;
	DWORD MainActorInstance = getMainActorInstance();
	if (!MainActorInstance) { return ObjList; }
	D3DXVECTOR3 MainActorPos = getPixelPosition(MainActorInstance);
	DWORD MobPtr = Driver.ReadVirtualMemory<DWORD>(pID, ModuleBase + MobPointer, sizeof(DWORD));
	for (int i = 0; i < 400; i++) {
		DWORD MobInstance = Driver.ReadVirtualMemory<DWORD>(pID, MobPtr + (i * 4), sizeof(DWORD));
		if (!MobInstance)
			continue;

		if (MobInstance == MainActorInstance)
			continue;

		DWORD MobType = getInstanceType(MobInstance);

		if ((MobType == 0 && !AttackMob) || (MobType == 2 && !AttackMetin) || (MobType != 0 && MobType != 2))
			continue;

		bool IsDead = getIsDead(MobInstance);
		if (IsDead)
			continue;

		DWORD MobVid = getVid(MobInstance);
		if (!MobVid)
			continue;

		D3DXVECTOR3 MobPos = getPixelPosition(MobInstance);
		if (!abs(MobPos.x) || !MobPos.y)
			continue;

		DWORD MobDistance = getDistance(MainActorPos, MobPos);

		ObjList.push_back({ MobInstance, MobVid, MobPos, MobType, MobDistance });
	}
	if (ObjList.size() > 1) {
		std::sort(ObjList.begin(), ObjList.end(), CompareInstanceObj);
	}
	return ObjList;
}

InstanceObj getAttackableMob(DWORD Distance, bool AttackMob, bool AttackMetin) {
	DWORD MainActorInstance = getMainActorInstance();
	if (!MainActorInstance) { return { 0 }; }

	D3DXVECTOR3 MainActorPos = getPixelPosition(MainActorInstance);

	std::vector<InstanceObj> MobList = getMobList(AttackMob, AttackMetin);
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
	if (getAttackStatus()) { return; }
	InstanceObj MobObj = getAttackableMob(distance, FarmBot_AttackMob, FarmBot_AttackMetin);
	if (MobObj.VID) {
		PressActor(MobObj.VID);
	}
}

void dummyfunc() {
	//int sz = getMobList(true, false).size();
	int sz = getMobList(false, true).size();
	System::Windows::Forms::MessageBox::Show(sz.ToString());

	FarmBotThread(5000);
}