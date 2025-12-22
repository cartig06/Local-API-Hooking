#ifndef HOOKING
#define HOOKING

#include <Windows.h>
#include <iostream>
#include "MinHook.h"

#pragma comment(lib, "libMinHook.x64.lib")

// Create Function Prototype for the Function You Want to Hook (Currently MessageBoxA)
typedef int(WINAPI* fnMessageBoxA)(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT   uType
);

BOOL Hook(LPVOID target, LPVOID detour, LPVOID* ppOriginal);

BOOL Unhook(LPVOID target);

#endif