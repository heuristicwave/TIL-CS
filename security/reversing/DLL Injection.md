## DLL Injection

Injector.exe

```c
#include "windows.h"
#include "tchar.h"

BOOL InjectDLL(DWORD dwPID, LPCTSTR DllPath) {
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	HMODULE hMod = NULL;

	LPVOID pRemoteBuf = NULL;
	DWORD dwBufSize = (DWORD)(_tcslen(DllPath) + 1) * sizeof(TCHAR);
	LPTHREAD_START_ROUTINE pThreadProc;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);							// get process handle
	pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE); // create space in process
	WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)DllPath, dwBufSize, NULL);
	 
	hMod = GetModuleHandle(L"kernel32.dll"); 
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryW");
	
	hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL);

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return 1;
	 
}

int _tmain(int argc, TCHAR *argv[]) {

	if (argc != 3) {
		_tprintf(L"input: %s pid dll_path", argv[0]);
		return 1;
	}
	 
	if (InjectDLL((DWORD) _tstol(argv[1]), argv[2]))
		_tprintf(L"injection(%s) success \n", argv[2]);
	else
		_tprintf(L"injection(%s) failed \n", argv[2]);
		
} 
```



Lock.dll

```c
#include "windows.h"
#include "stdio.h"

//HMODULE g_hMod = NULL; 

DWORD WINAPI ThreadProc(LPVOID lparam) {
	if (!LockWorkStation()) {
		printf("Lock failed ! \n");
	}
	return 0;
}

BOOL WINAPI DLLMAIN(HINSTANCE hinstDLL, DWORD fdwReason, DWORD lpvReserved) {
	//HANDLE hThread = NULL;
	g_hMod = (HMODULE)hinstDLL;

	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"Lock injection success!");
		hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		CloseHandle(hThread);

		return TRUE;
		break;
	}

	return FALSE; 
}
```



빌드해서 일정 경로에 두고 삽입할 pid를 알아낸 후, 아래 명령어로 injection

```powershell
DLL_Injector.exe 4868 "PATH\Lock.dll"
```

