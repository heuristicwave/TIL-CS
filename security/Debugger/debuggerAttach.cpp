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
// openProcess
int _tmain(int argc, TCHAR* argv[]) {

	HANDLE hProcess = NULL, hThread = NULL;
	DWORD dwPID;
	DWORD exception;
	PVOID exception_addr;

	DEBUG_EVENT d_event = { 0, };

	if (argc < 2) {
		printf("usage : program.exe [PID to attach]\n");
		return -1;
	}

	dwPID = (DWORD)_tstol(argv[1]); // string to num

	// get process
	if (!OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)) {
		printf("OpenProcess Error : %d", GetLastError());
		return -1;
	}

	// attach
	if (!DebugActiveProcess(dwPID)) {
		printf("DebugActiveProcess Error : %d", GetLastError());
		return -1;
	}

	while (true) {
		if (!WaitForDebugEvent(&d_event, INFINITE)) {
			break;
		}

		if (d_event.dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
			exception = d_event.u.Exception.ExceptionRecord.ExceptionCode;
			exception_addr = d_event.u.Exception.ExceptionRecord.ExceptionAddress;

			printf("Exception Occured at 0x%08x [\n", exception_addr);

			if (exception == EXCEPTION_ACCESS_VIOLATION) {
				printf("Access Violation]\n");
			}
			else if (exception == EXCEPTION_BREAKPOINT) {
				printf("EXCEPTION_BREAKPOINT]\n");
			}
			else if (exception == EXCEPTION_SINGLE_STEP) {
				printf("EXCEPTION_SINGLE_STEP]\n");
			}

			DebugActiveProcessStop(dwPID);
			printf("Exit Debugging Mode\n");
			return 0;
		}

		ContinueDebugEvent(d_event.dwProcessId, d_event.dwThreadId, DBG_CONTINUE);
	}

	return 0;
}