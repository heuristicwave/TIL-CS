#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <iostream>
#include <list>

using namespace std;

std::list<int> thread_list;

int Get_ThreadList(DWORD pid) {

	HANDLE hSnapshot = NULL;
	THREADENTRY32 te32;

	if (!(CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid))) {
		printf("CreateToolhelp32Snapshot Error %d\n",GetLastError());
		return -1;
	}

	te32.dwSize = sizeof(te32);

	if (!Thread32First(hSnapshot, &te32)) {
		printf("Thread32First Error %d\n", GetLastError());
		CloseHandle(hSnapshot);
		return -1;
	}

	do {
		if (te32.th32OwnerProcessID == pid) {
			printf("PID : %d, TID : %d\n", te32.th32OwnerProcessID, te32.th32ThreadID);
			thread_list.push_back(te32.th32ThreadID);
		}
	} while(Thread32Next(hSnapshot, &te32));

	return 0;
}

int Get_RegisterContext() {

	HANDLE hThread = NULL;
	CONTEXT ct;
	list<int>::iterator i;

	ct.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;

	for (i = thread_list.begin(); i != thread_list.end(); i++) {
		if (!(hThread = OpenThread(THREAD_ALL_ACCESS, NULL, *i))) {
			printf("OpenThread Error %d\n", GetLastError()); 
		}
		if (!GetThreadContext(hThread, &ct)) {
			printf("GetThreadContext Error %d\n", GetLastError());
		}

		printf("[*] DUMP Register of Thread \n");
		printf("EAX: 0x%08x / EBX: 0x%08x / ECX: 0x%08x / EDX: 0x%08x \n", ct.Eax, ct.Ebx, ct.Ecx, ct.Edx);
		printf("ESI: 0x%08x / EDI: 0x%08x / ESP: 0x%08x / EIP: 0x%08x \n", ct.Esi, ct.Edi, ct.Esp, ct.Eip);
		printf("------------------------------------------------------\n");

		CloseHandle(hThread);
	}

	return 0;
}

int Get_Context(DWORD pid) {
	
	// Thread List
	Get_ThreadList(pid);

	// Context
	Get_RegisterContext();
	return 0;
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
			Get_Context(dwPID);

			DebugActiveProcessStop(dwPID);
			printf("Exit Debugging Mode\n");
			
			return 0;
		}

		ContinueDebugEvent(d_event.dwProcessId, d_event.dwThreadId, DBG_CONTINUE);
	}

	return 0;
}