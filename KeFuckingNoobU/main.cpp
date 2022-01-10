#include <iostream>

#include "KeInterface.hpp"

#include <array>


DWORD CInstanceBase = 0x00030000 + 0x1234F28;
DWORD Offset_posx = 0x570;
DWORD Offset_posy = 0x574;
DWORD Offset_attackS = 0x5A6;

int main()
{
	KeInterface Driver("\\\\.\\kefucking");

	DWORD Pid = 6568;
	
	DWORD PlayerBase = Driver.ReadVirtualMemory<DWORD>(Pid, CInstanceBase, sizeof(ULONG));
	DWORD PlayerPtr = Driver.ReadVirtualMemory<DWORD>(Pid, PlayerBase + 0xC, sizeof(ULONG));
	static std::array<char, 14> playerName = Driver.ReadVirtualMemory<std::array<char, 14>>(Pid, PlayerPtr + 0x10, sizeof(std::array<char, 14>));
	std::cout << "Player Name: " << playerName.data() << std::endl;

	Driver.WriteVirtualMemory<short>(Pid, PlayerPtr + Offset_attackS, 16700, sizeof(short));


	return 0;
}