## API Hooking

Win32 API 호출을 중간에서 가로채서 제어권을 얻어내는 기법

코드 흐름을 변경 시켜서 공격자가 원하는 코드가 동작하도록 만듬



**주요 기능**

1. API에 넘어온 파라미터를 조작하거나 모니터링
2. API 함수의 리턴 값을 조작하거나 모니터링
3. API 호출 자체를 취소시키거나 사용자 코드의 실행 흐름을 변경



**후킹 방법**

1. IAT 영역

   타깃 프로세스의 IAT에 있는 API 주소를 후킹 함수 주소로 변경

   ex) notepad.exe의 IAT에는 WriteFile() 주소 값이 기록됨 이 값을 바꾸면 코드 흐름이 변경된 주소로 변화

   타깃 프로그램이 직접 호출 방식을 사용하는 경우 무용지물

2. Dll Code 영역

   타깃 프로세스 메모리에 로드된 dll의 API 실제 주로소 찾아가 코드를 직접 수정

   - 시작 코드를 jmp로 패치
   - 함수 일부를 덮어씀
   - 필요한 일부를 변경

3. Dll의 EAT에 기록된 API

   EAT에 기록된 API의 시작 주소를 후킹 함수 주소로 변경하는 방법



### Notepad Hooking Hands-on

DLL Code 영역 시작코드를 `JMP` 명령어로 패치하기, 메모장에 작성한 문서가 암호화 저장 되도록

1. Hook.dll `%System32%` 경로에 가져다둠

2. Injector.exe로 타깃프로세스에 hook.dll 로드

   WriteFile() API에 Hook를 걸어서 넘어오는 문자열 파라미터를 암호화 저장



**고려 사항**

NewWriteFile() : 메모장이 WriteFile() API를 호출할 때 전달하는 평문 문자열을 암호화 하는 함수

메모장의 WriteFile() API 시작 지점에 Hook를 설치하면 코드 흐름이 NewWriteFile()로 변경

1. 전달하는 인자 값을 그대로 전달 받아야 함
2. WriteFile() API의 2번째 인자에는 txt로 저장하고자 하는 문자열 위치 정보가 있어, 이 값을 이용해 문자열을 암호화 하고 저장
3. 암호화된 문자열을 저장할 때, NewWriteFile() 함수 내부에서 WriteFile() API를 호출해야 한다. 그런데 WriteFile() API 호출이 정상적으로 이루어지기 위해서는 WriteFile() API 시작 지점에 설치된 Hook를 풀어야 한다. 즉, hook을 먼저 풀고 암호화된 값을 2번째 인자로 넣고 WriteFile() API 호출
4. 암호화된 데이터가 텍스트로 만들어져, WriteFile()에 대한 리턴 값을 notepad.exe에 넘겨줌
5. Hook을 풀었기 때문에, 4에서 리턴 값을 돌려주기 전에 Hook을 걸어준다



**Hook.cpp**

```c
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch(fdwReason) {
        case DLL_PROCESS_ATTACH:
            // hook
            HookCode("kernel32.dll", "WriteFile", (PROC)NewWriteFile, g_pOrgCPIW);
            break;
        case DLL_PROCESS_DETACH:
            // unhook
            UnhookCode("kernel32.dll", "WriteFile", g_pOrgCPIW);
            break;
    }
    return TRUE;
}

BOOL HookCode(LPCSTR szDllName, LPCSTR szFuncName, PROC pFuncNew, PBYTE pOrgBytes) {
	FARPROC pFuncOrg;
    DWORD dwOldProtect, dwAddress;
    byte pBuf[5] = {0xE9, 0, };
    
    pFuncOrg = (FARPROC)GetProcAddress(GetModuleHandleA(szDllName), szFuncName); // 1
    VirtualProtect((LPVOID)pFuncOrg, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect);  // 2
    memcpy(pOrgBytes, pFuncOrg, 5);							// 3
    dwAddress = (DWORD)pFuncNew - (DWORD)pFuncOrg - 5;		// 4
    memcpy(&pBuf[1], &dwAddress, 4);						// 5
    memcpy(pFuncOrg, pBuf, 5);								// 6
    VirtualProtect((LPVOID)pFuncOrg, 5, dwOldProtect, &dwOldProtect);	// 7
    
    return TRUE;
}
```

1. GetProcAddress() API를 사용해서 WriteFile() API의 시작 주소를 알아낸다.
2. WriteFile() API의 시작 지점을 `JMP OpCode(1byte) + 주소입력공간(4byte)`만큼 권한을 바꿔줌. 해당 메모리 공간의 Origin권한을 `dwOldProtect`에 저장한다. 7에서 권한을 돌릴때 사용됨
3. WriteFile() API의 시작 지점에는 Original Code가 있다. Hook을 해제할 때 필요해, `pOrgBytes`에 저장
4. `JMP NewWriteFile 함수 시작 주소`에서 `NewWriteFile 함수 시작 주소`에는 상대 주소 값이 들어간다. WriteFile()주소가 400이고, NewWriteFile()주소가 500일 때, `JMP NewWriteFile 함수 시작 주소`코드는 WriteFile() 함수 시작 주소에 기록된다. 실제 점프가 이루어지는 지점은 시작주소에서 5byte 떨어져 있다. 즉, 500으로 가기 위해서 JMP 95가 되어야 한다.
5. `pBuf[0]`의 '0xE9'는 JMP 명령어의 OpCode이다. 여기에 4에서 구한 상대주소를 더해 `jmp newWriteFile 함수 시작주소`코드를 만든다
6. WriteFile() API 시작 지점에 'JMP NewWriteFile 함수 시작 주소'코드를 기록한다.
7. Hook 설치가 완료되면 2에서 변경한 권한을 돌려 놓는다.



**NewWriteFile**

```c
BOOL WINAPI NewWriteFile(
	HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD 	
	lpNumberOfBytesWritten, OVERLAPPED lpOverlapped
) // 1
{
	BOOL bRet;
	FARPROC pFunc;
	TCHAR lpCharVal[_MAX_PATH] = {0,};
	TCHAR *p = NULL;
	int iLeng = 0;
	
	UnhookCode("kernel32.dll", "WriteFile", g_pOrgCPIW);		// 2
	wsprintf(lpCharVal, "%s", lpBuffer);						// 3
	iLeng = strlen(lpCharVal);
	
	for(int i=0; i < iLeng; i++)								// 4
		lpCharVal[i] = lpCharVal[i]^0xFF;
		
	pFunc = GetProcAddress(GetModuleHandleA("kernel32.dll"), "WriteFile");
	bRet = ((PFWRITEFILE)pFunc)( hFile, lpCharVal,				// 5
    	nNumberOfBytesToWrite, lpNumverOfBytesWritten, lpOverlapped);
								
	HookCode("kernel32.dll", "WriteFile", (PROC)NewWriteFile, g_pOrgCPIW);	// 6
    _asm {				// 7
		mov esp, ebp
	}
	
	return bRet	// 5의 리턴 값을 넘겨주면 완료
}
```





---

위 자료은 `리버싱 이 정도는 알아야지 - 이시우`를 읽고 정리한 내용 입니다.