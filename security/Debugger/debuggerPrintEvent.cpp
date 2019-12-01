#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void PrintEvent(DEBUG_EVENT& d_event) {
	//printf("Event Code : %d\n", d_event.dwDebugEventCode);

	switch (d_event.dwDebugEventCode)
	{
	case CREATE_PROCESS_DEBUG_EVENT:
		printf("CREATE_PROCESS_DEBUG_EVENT\n");
		break;
	case EXIT_PROCESS_DEBUG_EVENT:
		printf("EXIT_PROCESS_DEBUG_EVENT\n");
		break;
	case CREATE_THREAD_DEBUG_EVENT:
		printf("CREATE_THREAD_DEBUG_EVENT\n");
		break;
	case EXIT_THREAD_DEBUG_EVENT:
		printf("EXIT_THREAD_DEBUG_EVENT\n");
		break;
	case LOAD_DLL_DEBUG_EVENT:
		printf("LOAD_DLL_DEBUG_EVENT\n");
		break;
	case UNLOAD_DLL_DEBUG_EVENT:
		printf("UNLOAD_DLL_DEBUG_EVENT\n");
		break;
	case OUTPUT_DEBUG_STRING_EVENT:
		printf("OUTPUT_DEBUG_STRING_EVENT\n");
		break;
	case RIP_EVENT:
		printf("RIP_EVENT\n");
		break;
	case EXCEPTION_DEBUG_EVENT:
		printf("EXCEPTION_DEBUG_EVENT\n");
		break;
	}
}

int _tmain(int argc, TCHAR* argv[]) {

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	// init var
	ZeroMemory(&si, sizeof(si)); 
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	DEBUG_EVENT d_event = { 0, };

	WCHAR szCmdLine[] = L"C:\\windows\\system32\\notepad.exe"; // debugee path
	
	if (!CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, DEBUG_PROCESS, NULL, NULL, &si, &pi)) {
		printf("CreateProcess Error !! %d \n", GetLastError());
		return -1;
	}

	while (true) {
		if (!WaitForDebugEvent(&d_event, INFINITE)) {
			break;
		}

		// handle event
		PrintEvent(d_event);

		ContinueDebugEvent(d_event.dwProcessId, d_event.dwThreadId, DBG_CONTINUE);
	}

	return 0;
}