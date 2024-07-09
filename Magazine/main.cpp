#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <Windows.h>
#include "utilities/memory.h"

//Menu Colors
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string yellow = "\033[33m";
const std::string blue = "\033[34m";
const std::string magenta = "\033[35m";
const std::string cyan = "\033[36m";
const std::string white = "\033[37m";
const std::string reset = "\033[0m";

// 1.3.0.2 Offsets for assault cube
constexpr auto localPlayer = 0x17B0B8;
constexpr auto health = 0xEC;
constexpr auto armor = 0xF0;
constexpr auto mtpAmmo = 0x140;
constexpr auto mtpAmmoMag = 0x128;
constexpr auto mtpGernade = 0x158;
constexpr auto nameOffsetWithinPadding = 0x0214;

// Logo
std::vector<std::string> logo
{
	"  __  __                   _          ",
	"|  \\/  |__ _ __ _ __ _ __(_)_ _  ___ ",
	"| |\\/| / _` / _` / _` |_ / | ' \\/ -_)",
	"|_|  |_\\__,_\\__, \\__,_/__|_|_||_\\___|",
	"             |___/                    "
};

class N00000000
{
public:
	char pad_0000[4160]; //0x0000
}; //Size: 0x1040

class NamePadding
{
public:
	char preNamePadding[516]; //0x0000
	char maxCharactersInName[16]; //0x0204
	char postNamePadding[3640]; //0x0214
}; //Size: 0x104C




// Modify health, armor, ammo

int main()
{
	Memory memory{ "ac_client.exe" };
	const auto ModuleBaseAddress = memory.GetModuleAddress("ac_client.exe");
	// dereference the pointer
	const auto localPlayerAddress = memory.Read<std::uintptr_t>(ModuleBaseAddress + localPlayer);
	const auto healthAddress = localPlayerAddress + health;
	const auto armorAddress = localPlayerAddress + armor;
	const auto mtpAmmoAddress = localPlayerAddress + mtpAmmo;
	const auto mtpGernadeAddress = localPlayerAddress + mtpGernade;
	const auto mtpAmmoMagAddress = localPlayerAddress + mtpAmmoMag;
	const auto nameAddress = localPlayerAddress + nameOffsetWithinPadding;

	std::string name = memory.Read<NamePadding>(nameAddress).preNamePadding;

	std::cout << std::endl;

	for (const auto& line : logo)
	{
		std::cout << cyan << line << std::endl;
	}

	std::cout << std::endl << yellow << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << reset << std::endl << std::endl;


	std::cout << "Welcome to desynced, " << magenta << name << "\n" << std::endl;
	std::cout << green << "F1: Health Hack" << reset << std::endl;
	std::cout << green << "F2: Armor Hack" << reset << std::endl;
	std::cout << green << "F3: Rifle Ammo Hack" << reset << std::endl;
	std::cout << green << "F4: Gernade Amount Hack" << reset << std::endl;
	std::cout << green << "F5: Rifle Ammo Magazine Hack" << reset << std::endl << std::endl;
	std::cout << "Source Code is Here" << magenta << std::endl << "https://github.com/ChaseTheGoat2244" << std::endl;

		
	while (true) {
		if (GetAsyncKeyState(VK_F1) & 0x8000) { memory.Write<int>(healthAddress, 1000); std::cout << red << "Health hacked!" << std::endl; }
		else if (GetAsyncKeyState(VK_F2) & 0x8000) { memory.Write<int>(armorAddress, 1000); std::cout << red << "Armor hacked!" << std::endl; }
		else if (GetAsyncKeyState(VK_F3) & 0x8000) { memory.Write<int>(mtpAmmoAddress, 1000); std::cout << red << "Infinite Ammo hacked!" << std::endl; }
		else if (GetAsyncKeyState(VK_F4) & 0x8000) { memory.Write<int>(mtpGernadeAddress, 20); std::cout << red << "Gernade Amount hacked!" << std::endl; }
		else if (GetAsyncKeyState(VK_F5) & 0x8000) { memory.Write<int>(mtpAmmoMagAddress, 1000); std::cout << red << "Infinite Reload hacked!" << std::endl; }
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}