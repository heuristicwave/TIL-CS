## PE File Format

PE File Format을 공부한다는 것은 PE 헤더 구조체를 공부한다는 것

> 어떻게 메모리 적재, 어디서부터 실행, 실행에 필요한 DLL, 필요한 stack/heap 메모리의 크기



### 기본 구조

![pe파일포멧](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/112015_2323_2MalwareRes1.jpg)

Dos header 부터 section header 까지 PE 헤더, 그 밑의 section들을 합쳐서 PE 바디라고 함

파일 - offset / 메모리 - VA(virtual address)

>VA는 프로세스 가상메모리의 절대주소 / RVA는 ImageBase로부터 상대주소
>
>RVA + Imagebase = VA
>
>32bit, 각 프로세스에게 4gb 크기의 가상 메모리 할당
>
>-> va의 범위는 00000000 ~ FFFFFFFF



섹션 헤더 : section에 대한 파일/메모리에서의 크기, 위치, 속성 등 정의

PE 헤더 : 끝 부분과 각 섹션의 끝에서 NULL padding이라 불리는 영역 존재

파일/메모리에서 섹션의 시작 위치는 각 파일/메모리의 최소 기본 단위의 배수에 해당하는 위치, 빈 공간은 null로 채움



### PE Header

##### DOS Header

PE를 만들 때 사용되던 DOS파일과의 호환성을 위해서 만듬

##### DOS Stub

코드와 데이터의 혼합으로 존재 여부는 옵션



##### NT Header

파일의 개략적인 속성을 나타내는 IMAGE_FILE_HEADER 구조체

1. Machine

   cpu별로 고유한 값을 가짐

2. NumberOfSections

   pe는 코드, data, 자원 등이 각각의 섹션에 나뉘는데 이런 섹션의 개수를 나타냄

3. SizeOfOptionalHeader

   구조체의 마지막 벰버의 크기를 나타냄

4. Characteristics

   파일의 속성을 나타내는 값 (DLL, 실행가능 파일)



#### IMAGE_OPTIONAL_HEADER32

1. MAGIC

   구조체인 경우 10B, 64bit의 경우 20B의 값을 가짐

2. AddressOfEntryPoint

   entry poiny의 RVA 값을 가지고 있다. 최초로 실행되는 코드의 시작 주소

3. ImageBase

   PE 파일이 로딩되는 시작 주소

   > EXE, DLL : 0 ~ 7FFFFFFF (user memory 영역)
   >
   > SYS파일 : 80000000 ~ FFFFFFFF (kernel memory 영역)

   PE 로더는 PE 파일을 실행시키기 위해 프로세스를 생성하고 파일을 메모리에 로딩한 후 EIP 레지스터 값을 ImageBase + AddressOfEntryPoint 값으로 세팅

4. SectionAlignment, FileAlignment

   파일 섹션의 최소 단위 : FileAlignment

   메모리 섹션 최소 단위 : SectionAlignment

   파일 / 메모리 섹션의 크기는 배수가 되어야 한다

5. SizeOfImage

   가상 메모리에서 PE Image가 차지하는크기

6. SizeOfHeader

   PE 헤더의 전체 크기, FileAlignment의 배수

7. Subsystem

   파일 종류 구분

8. NumberOfRvaAndSizes

   구조체 정의에 크기가 명시되어 있지만, PE로더는 이 값을 보고 배열의 크기 인식

9. DataDirectory

   IMAGE_DATA_DIRECTORY 구조체의 배열로 배열의 각 항목 마다 정의된 값을 가짐



#### 섹션 헤더

섹션의 속성을 정의 (여려 개의 섹션 구조 - 안정성)



##### IMAGE_SECTION_HEADER

섹션 헤더는 각 섹션별 IMAGE_SECTION_HEADER 구조체의 배열로 되어 있다.

(아직 이해를 못 했는데.... 나중에 다시 정리 해야지)



### RVA to RAW

메모리의 주소와 파일 offset을 매핑

rva가 속한 섹션을 찾아 비례식을 통해 파일 옵셋(raw)계산

```C
RAW - PointerToRawData = RVA - VirtualAddress
				   RAW = RVA - VirtualAddress + PointerToRawData
```

(VA 주소를 찾는 방법을 모르겠따)



### IAT

Import Address Table 어떤 라이브러리에서 어떤 함수를 사용하고 있는지를 기술한 테이블 (process, memory, DLL)



#### DLL

멀티 태스킹을 지원하기 때문에 라이브러리 포함 방식이 비효율적(메모리 낭비)이라 dll 고안

Implicit linking : 프로그램 종료 시, 메모리 해제

Explicit liking : 프로그램 사용 시, 로딩하고 사용이 끝나면 메모리 해제



#### IMAGE_IMPORT_DESCRIPTOR

PE 파일은 자신이 어떤 라이브러리를 import하는지 위 구조체에 명시한다. 라이브러리의 개수만큼 구조체의 배열 형식으로 존재

> pe헤더에서 table은 배열을 뜻함



---

본 내용은 `리버싱 핵심 원리 - 이승원 `을 보고 정리한 내용입니다.