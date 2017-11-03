#include <Windows.h>
#include <iostream>

extern "C" __declspec(dllexport) void WinEventProc(HWINEVENTHOOK hook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	static bool bFirstRun = true;
	if (bFirstRun)
	{
		bFirstRun = false;

		char szText[512];
		sprintf(szText, "DLL works on: %u", GetCurrentProcessId());
		MessageBoxA(0, szText, "", 0);
	}
}
