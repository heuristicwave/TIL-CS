### What is Assembly?

기계어(binary, hex)와 함께 둘 뿐인 low level



**분석**

```assembly
// AT&T
push	%rbp
mov		%rsp, %rbp
sub		$0x8, %rsp
mov		$0x1, %rax	// 0x1를 rax로

// intel은 AT&T와 반대이며 $, %가 없음
```

[인텔 메뉴얼](https://software.intel.com/en-us/articles/intel-sdm)



#### Assembler Type

- NASM (Netwide Assembler)
- GAS (Gnu Assembler)

>[Assemble & Linking](https://www.brainkart.com/article/Assembly-and-Linking_11818/)
>
>고수준 [컴파일러] -> 어셈블리코드[어셈블러] -> 목적코드[링커] -> Executable 바이너리[로더] -> 실행



#### Hands-on

```assembly
global_start
	
section .text
_start:	// 스타트 함수 정의
	push 	rbp			// rbp가 가진 값을 넣음
	mov 	rbp, rsp	// rsp를 rbp로 옮김
	
	mov		rsp, rbp
	ret
```



**nano helloworld.s**

```assembly
section .data	// 문자열 데이터 저장
	msg db "Hello World"
	
section .text	
	global_start
	
_start:	// 스타트 함수 정의
	mov rax, 1	// rax라는 레지스터에 1이라는 값을 (mov)
	mov rdi, 1
	mov rsi, msg
	mov rdx, 12
	syscall	// 여기까진 출력
	mov rax, 60
	mov rdi, 0	// 안전하게 종료
	syscall	// 시스템 종료
```

목적파일 및 실행파일

```shell
nasm -f elf64 -o helloworld.o helloworld.s
ld -o helloworld helloworld.o
```

##### 이것도 가능

```shell
nasm -felf64 hello.asm	// 목적코드 생성
lf -o hello hello.o
```



### Disassembly

```shell
objdump -M intel -d hello
```



### 레지스터

- 어셈블리에서 사용되는 기본 변수 이름

  - 다른 언어와 달리, 하드웨어적으로 구현
  - **이름 변경 불가능**
  - cpu 종류 별로 레지스터 이름이 다 다름
  - 레지스터 별로, 정해진 용도 존재

- 앞선 message는 레지스터가 아님

  -> nasm이 정의 한 symbol

  

[x64 Architecture](https://docs.microsoft.com/sr-cyrl-rs/windows-hardware/drivers/debugger/x64-architecture)

![레지스터+1](https://t1.daumcdn.net/cfile/tistory/2405813A55BDD82633)

- RAX = 64, EAX = 32,  AX = 16, AH, AL = 8
  - RBX, RCX, RDX 마찬가지
  - RSI의 32, 16, 8비트 표현은? =>  esi, si, sil
  - R8는? => r8d, r8w, r8b



##### 데이터 레지스터

rax : 함수가 실행된 다음에 결과가 담김, 함수 반환값에 담김

rbx : 메모리 주소가 지정, RSI, RDI와 함께

rcx :  카운터 레지스터, 반복문(loop counter)에 사용

rdx : 데이터 레지스터, 연산시 rax와 자주 사용



##### 포인터 레지스터

rsi : 메모리 이동 및 비교 시 출발지(Source) 주소 / 문자열 관련 Instruction 사용 시

rdi : 메모리 이동 및 비교 시 목적지(Destination) 주소 / 문자열 관련 Instruction 사용 시

rbp : 함수의 파람 및 변수의 주소를 가리킬 때 사용 / 현재 함수의 Base Pointer

rsp : 스택의 가장 위에 있는 주소를 가리킴, Push/Pop에 의해 항상 바뀜.

rip: 다음에 수행 될 코드 역을 가리키고 있음.



```shell
nano sum.c

gcc -S -fno-stack-protector -mpreferred-stack-boundary=4 -z execstack -o sum.a sum.c 
```



#### mips register



#### arm core registers in arm state



### MOV

-  mov [reg|addr], [imm|reg|mem]
-  값 이동



### LEA

- LEA [reg], [mem]
- 주소 이동



### MOV VS LEA

- MOV eax, [rbp-16] 
  - eax = *(rbp-16)
- LEA eax, [rbp-16]
  - eax = (rbp -16)
  - sub rbp, 16 ; mov eax, rbp와 같음.
- 2줄 짜리 MOV 명령어를 1개의 Instruction으로 만듦



#### jmp

- 그냥 JMP 다음의 주소로 이동(JMP 다음에 오는 LABEL, 프로시저로 이동2)

  

#### call

- call 다음에 있는 주소를 호출함
- call 다음 명령어 주소를 스택에 **PUSH**



#### RET

- 현재 RSP 가 가리키고 있는 값으로 점프한다.
- 스택 최상위에 있는 값으로 점프한다.
- RSP를 8증가 시킨다.



#### CMP

- CMP [imm|reg|mem], [reg,mem]



#### REP

- RCX 레지스터를 1씩 감소 시키면서, 문자열 관련 명령어를 처리



#### STOS

- AX를 EDI가 가리키는 주소에 넣음.
- rep stos byte ptr [EDI]



#### PUSH [reg] / POP [reg]

- PUSH ; 스택 최상위에 값 넣음 ; RSP 레지스터 증가
- POP ; 스택 최상위에서 값 빼옴 ; RSP 감소



### 스택 관련 레지스터

#### RSP

- 항상 스택 최상위를 가리킴 / PUSH/POP에 의해 증감

#### RBP

- 현재 함수 안에서 변수들의 기준점이 됨