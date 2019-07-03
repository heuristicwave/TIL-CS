## Computer Architecture and C lang

CISC = Complex Instruction Set Computer

RISC = Reduced Instruction Set Computer

=> datepath 당 명령어의 개수

오늘날의 컴퓨터는 기준에따라 cisc이기도 risc이기도 함.



폰 노이만 (X),

=> Address Bus, Data Bus (Instruction, Operand)



Harvard Architecture(O) - 현대의 컴퓨터 구조

=> Address Bus, Data Bus, Instruction Bus + Cache Hierarchy(현대의 컴퓨터 구조가 되기 위한 요소)



Cache Hierarchy's Pros

- Procedure 반복이 빨라짐
- Shard Cache 구조를 이용한 멀티코어 작동이 가능 => 멀티 태스팅에 용이



C컴파일러 종류

PIC, ATmega, ARM, MIPS, PPC, TriCore, CBE, Spare ...

zlib 덕분에 각기 다른 cpu에서 컴파일 할 수 있도록 소스코드가 작성되어 있음



> 64비트 int 64byte가 아님 64로 쓰려면 longint
>
> 32비트에서는 int가 32bit
>
> 
>
> **bytes vs word**
>
> cpu가 한번에 처리할 수 있는 데이터의 폭 => word (현재는 기준이 모호함)
>
> 1 word = ? bit : ACC reg size(누산기 레지스터의 사이즈)



> Tensor ?
>
> 3가지 상태를 갖는 하나의 자리수 ex) true, false, not none(알 수 없음)
>
> 8bit를 읽어옴



> Turing Machine VS Finite State Machine
>
> TM은 FSM의 명집합(super set)
>
> 
>
> 튜링머신 : 열린형태의 state machine (데이터를 무궁무진하게 저장 및 활용)
>
> -> 프로그래밍이 가능
>
> FSM : 유한한 / (HTML -> FSM)
>
> 
>
> 프로그래밍
>
> 무한한 상태를 유한한 상태로 만듬 (무한한 하드웨어를 소프트웨어로 제어하여 구현)



### 명령문

명령문(Statements)

- 연산을 제외한 함수의 호출, 프로그램의 흐름 제어, 시스템 및 os 제어 담당하는 프로그램의 조각
- 5가지의 명령문
  + compound (블럭 또는 함수의 시작과 끝 정의) + label
  + expression (연산, 변수, 함수의 선언, 값의 할당, 함수 호출 등)
  + selection (조건에 따른 선택)
  + iteration (반복)
  + jump (프로그램 흐름 이동)



### 자료형

- 상수(프로그램 안에 기록) - 2진수로 표현할 수 있는 모든 자료형태
- 변수 - 저장하는 자료의 유형에 따라
  - 정수 / 실수 / 문자 / 메모리 주소 (배열, 구조체, 공용체, 포인터)
- 함수 - 반환하는 값의 유형에 따라
  - null (널포인터를 참조하도록 프로그램을 짜면 안됨)
  - 정수 / 실수 / 문자형
  - 메모리 주소



> **문자형**
>
> encoding : UTF8
>
> 문자형 데이터 문자맵을 통해 1대1 매칭하여 화면 표현
>
> 현재는, 문자 캐릭터 맵에 대한 드라이버를 만들어 보급
>
> 
>
> ACPI, APIC, DMA SMBus -> x86 플랫폼의 필수장치 => 메모리구조를 잘 이해해야 함
>
> direct memory access(모든 저장장치가 가지고 있음)
>
> smbus 멀티코어에서 사용



> windows kernel vs linux kernel
>
> 실행파일의 구조(프로세스 구조)가 다름
>
> windows security ( Micro ) != unix/linux security ( Monolitic : 단일형 커널 )
>
> 모놀리식(수직적) : [입출력](https://ko.wikipedia.org/wiki/%EC%9E%85%EC%B6%9C%EB%A0%A5) 기능, [네트워크](https://ko.wikipedia.org/wiki/%EC%BB%B4%ED%93%A8%ED%84%B0_%EB%84%A4%ED%8A%B8%EC%9B%8C%ED%81%AC) 기능, [장치](https://ko.wikipedia.org/wiki/%EC%9E%A5%EC%B9%98) 지원 등 운영 체제의 일반적인 기능을 커널과 동일한 메모리 공간에 적재, 실행하는 기법을 말한다.
>
> 윈도우 커널(수평적)의 필수 요소 : 프로세스, 가상메모리, IPC
>
> 계층이 있더라도 서로 간섭하지 않음 (게임에 유리, 보안에 취약한 점이 많음, 때문에 ipc는 조심해야 함)
>
> 프로세스간 부모 자식 관계가 없음 -> fork의 개념이 없음
>
> 재밋당! 더 조사가 필요!



### 고급 언어와 저급 언어

고급언어 일수록 메모리의 값을 주거나 받지 않음

- 메모리 주소값을 참조하고 할당하는지
- 메모리 주소 접근을 제한 할 수 있는 장치가 있는지
- 객체의 경계를 확인하는지 (혹은 객체의 존재 여부)
- null 객체의 접근을 허용하는지 여부



cf. 객체 (object)

객체는 데이터 -> 바이너리로 이뤄진 메모리 영역

메모리 공간에 저장된 바이너리 덤프, 제어 및 관리, 보호가 가능한 자료단위



객체?의 구성 혹은 구조

객체에는 (메모리덤프할때 발생하는) 클래스 인스턴스 id가 존재

id를 상실하면 고아가되고 메모리상에서 garbage가 됨

클래스 id가 사라지면 메모리누수.... and 보호해야함(암호화)

> 객체에는 메소드 함수가 있을까?
>
> 메소드 함수 자체는 없지만, symbolic table이 있음 -> 사용하려면 인증절차를 포함해야함
>
> 즉, dll 하이재킹 시, 다른 프로그램에게 참조됨 -> 암호화된 데이터 외부 유출



> c언어는 가장 현대적 cpu 동작에 가까운 저급언어이자 고급언어



### 컴퓨터 .... 4분대 전



### 컴퓨터 구조의 변화와 OS변화에 따른 C변화

c++은 c의 superset



### ISO C Working Group



### C언어는 왜 발전하는가?

- 유통되는 컴퓨터의 구조가 변화

  -> 주로 사용하는 OS의 기능 및 구현체가 변화

  -> 그에 맞는 소프트웨어를 제작하기 위한 언어의 기능



### 주요 컴파일러

#### MSVC

- Microsoft Visual C++
  - 실제로는 c/c++ 컴파일러



#### GCC

gnu c compiler 또는 gnu compiler collection

중간언어 계층



#### clang

gnu public license의 엄격한 제한을 우려, bsd 라이센스의 컴파일러 제작

컴파일러의 프론트엔드를 clang, 백엔드를 llvm으로 구성 (애플의 최적화)



### 전처리기

c언어의 전처리는 튜링테스트가 가능 (#define 때문에 가능)