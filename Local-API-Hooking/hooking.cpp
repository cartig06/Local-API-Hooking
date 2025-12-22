#include "hooking.h"

BOOL Hook(LPVOID target, LPVOID detour, LPVOID* original) {
	MH_STATUS status = MH_OK;
	
	// Init MinHook Library
	if ((status = MH_Initialize()) != MH_OK) {
		std::cerr << "[-] Failed to init MinHook library: " << status << std::endl;
		return FALSE;
	}

	// Create Hook for Function
	status = MH_CreateHook(target, detour, original);
	if (status != MH_OK) {
		std::cerr << "[-] Failed to create hook: " << status << std::endl;
		return FALSE;
	}

	// Enable Hook
	if ((status = MH_EnableHook(target)) != MH_OK) {
		std::cerr << "[-] Failed to enable hook: " << status << std::endl;
		return FALSE;
	}

	std::cout << "[+] Function Hooked!" << std::endl;

	return TRUE;
}

BOOL Unhook(LPVOID target) {
	MH_STATUS status = MH_OK;
	
	// Disable Hook
	if ((status = MH_DisableHook(target)) != MH_OK) {
		std::cerr << "[-] Failed to disable hook: " << status << std::endl;
		return FALSE;
	}

	// Remove
	status = MH_RemoveHook(target);
	if (status != MH_OK) {
		std::cerr << "[-] Failed to remove hook: " << status << std::endl;
		return FALSE;
	}

	// Uninitialize MinHook Library
	if ((status = MH_Uninitialize()) != MH_OK) {
		std::cerr << "[-] Failed to enable hook: " << status << std::endl;
		return FALSE;
	}

	std::cout << "[+] Function Unhooked!" << std::endl;

	return TRUE;
}