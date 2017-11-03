#include <Windows.h>
#include <iostream>

int main(int argc, char* argv[])
{
	auto hModule = LoadLibraryA("TestModule.dll");
	if (!hModule) {
		printf("LoadLibraryA fail! Error code: %u\n", GetLastError());
		return EXIT_SUCCESS;
	}
	printf("Module at: %p\n", hModule);

	auto fpHandleWinEventAddr = (WINEVENTPROC)GetProcAddress(hModule, "WinEventProc");
	if (!fpHandleWinEventAddr) {
		printf("GetProcAddress fail! Error code: %u\n", GetLastError());
		return EXIT_SUCCESS;
	}
	printf("WinEventProc at: %p\n", fpHandleWinEventAddr);
	
	auto hSetEventHook = SetWinEventHook(EVENT_MIN, EVENT_MAX, hModule, fpHandleWinEventAddr, 0, 0, WINEVENT_INCONTEXT);
	if (!hSetEventHook) {
		printf("SetWinEventHook fail! Error code: %u\n", GetLastError());
		return EXIT_SUCCESS;
	}
	printf("SetWinEventHook completed!\n");

	std::cin.get();

	auto bUnHookRet = UnhookWinEvent(hSetEventHook);
	if (!bUnHookRet) {
		printf("UnhookWinEvent fail! Error code: %u\n", GetLastError());
		return EXIT_SUCCESS;
	}
	printf("SetWinEventHook unhook completed!\n");

	std::cin.get();
	return EXIT_SUCCESS;
}
