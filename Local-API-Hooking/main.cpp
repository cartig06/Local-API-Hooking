// I was curious to try my hand at API hooking during my research into malware development/analysis. Upon
// looking into the topic, I found TsudaKageyu's MinHook library and figured this would be a good tool for
// my basic implementation. This is the result of my practice. Enjoy!      

#include "hooking.h"

// Global Pointer to Unhooked Function (This is to allow me to call the unaltered function after running trampoline code)
fnMessageBoxA origMessageBoxA = NULL;

// Detour Function that is Called in Place of Target
int Detour(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	std::cout << "[+] Window Caption: " << lpCaption << std::endl;
	std::cout << "[+] Window Text: " << lpText << std::endl;

	// Calling unaltered function to maintain functionality
	return origMessageBoxA(hWnd, lpText, lpCaption, uType);
}

int main() {
	if (!Hook(&MessageBoxA, &Detour, (LPVOID*)&origMessageBoxA)) {
		std::cerr << "[-] Failed to hook function! Exiting." << std::endl;
		return EXIT_FAILURE;
	}

	MessageBoxA(NULL, "Hello, World!", "Test", MB_OK);

	if (!Unhook(&MessageBoxA)) {
		std::cerr << "[-] Failed to unhook function. Exiting." << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}