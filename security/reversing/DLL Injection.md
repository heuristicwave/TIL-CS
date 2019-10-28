## DLL Injection

### CreateRemoteThread()

```c
hThread = CreateRemoteThread(hProcess, 0, 0, pTreadProc, pRemoteBuf, 0, NULL);

if(!hThread) goto end;
```

@param1 : 스레드를 생성할 타깃 프로세스의 핸들 값[OpenProcess() API 활용]

@param4 : 호출하고자 하는 스레드 코드 위치 주소

@param5 : 스레드 코드 동작에 필요한 인자의 위치 주소



#### @param 1st 구하기

타깃 프로세스의 PID를 구하고 OpenProcess() API를 호출하면 프로세스의 핸들 값을 얻음

```c
hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, dwPID);
if(!hProcess) return 0;
```



프로세스의 PID 얻기

```c
// lpProName의 이름과 일치하는 것을 검색하여 PID의 값을 리턴
dwPID = FindProcess(lpProName)	// lpProName = "notepad.exe"
```



**FindProcess**

```c
// Using CreateToolhelp32Snapshot(), Process32First(), Process32Next() API
// Write to PROCESSENTRY32 structure
DWORD FindProcess(LPCTSTR lpProcessName) {
    PROCESSENTRY32		pe;
    HANDLE				hSnapShot = INVALID_HANDLE_VALUE;
    DWORD				dwPID = 0;
    
    pe.dwSize = sizeof (PROCESSENTRY32);
    
    hSnapShot = CreateToolhelp32Snapshot (TH32CS_SNAPALL, NULLL);
    if(hSnapShot == INVALID_HANDLE_VALUE)
        return dwPID;
    
    Process32First(hSnapShot, &pe);
    
    do {
        if(!strcmp (lpProcessName, (LPCTSTR)pe.szExeFile)){
            dwPID = pe.th32ProcessID;
            break;
        }
    } while(Process32Next (hSnapShot, &pe));
    
    CloseHandle(hSnapShot);
    
    return dwPID;
}
```

---

#### @param 4th 구하기

스레드 코드의 위치 주소 대신 LoadLibrary() API의 호출 주소 넣기

> ASLR 기능이 적용되지 않은 WIN7이하는 kernel32.dll의 베이스 주소를 일정하게 관리, 때문에 Injector.exe에서 알아낸 LoadLibrary() API 주소를 타깃 프로세스에 넘겨도 문제가 되지 않음

```C
hModule = GetModuleHandle("kernel32.dll");
if(!hModule) goto end;

// GetProcAddress()를 사용해 LoadLibrary() API의 주소를 얻음
pTreadProc = (LPTHREAD_START_ROUTINE) GetProcAddress (hModule, "LoadLibraryA");
if(!pTreadProc) goto end;
```

---

#### @param 5th 구하기

인자로 문자열의 위치 주소를 전달하려면, 먼저 해당 문자열의 타깃 프로세스의 메모리 공간에 기록해야 함.

VirtualAllocEx()로 타깃 프로세스 메모리 공간 할당, WriteProcessMemory()로 DLL 경로 기록

```c
pRemoteBuf = VirtualAllocEx(hProcess,
                            NULL, strlen(lpDllPath)+1, MEM_COMMIT, PAGE_READWRITE);
if(!pRemoteBuf) goto end;

bResult = WriteProcessMemory(hProcess, pRemoteBuf, lpDllPath, strlen(lpDllPath)+1, NULL);
if(!bResult) goto end;
```





## DLL 파일 분석

원하는 위치의 DLL에서 분석하기

Option -> debugging options -> break_on_new_module(DLL)

해당위치 진입 후, BP설정 -> 다시 옵션 풀기



---

위 자료은 `리버싱 이 정도는 알아야지 - 이시우`를 읽고 정리한 내용 입니다.