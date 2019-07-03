```shell
nano helloworld.s


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

```bash
nasm -f elf64 -o helloworld.o helloworld.s
ld -o helloworld helloworld.o
```



[x64 Architecture](<https://docs.microsoft.com/sr-cyrl-rs/windows-hardware/drivers/debugger/x64-architecture> )

데이터 레지스터

rax : 함수가 실행된 다음에 결과가 담김

rbx : 메모리 주소가 지정

rcx :  카운터 레지스터, 반복문에 사용

rdx : 데이터 레지스터, 연산시 rax와 자주 사용



포인터 레지스터

rsi : 메모리 이동 및 비교 시 출발지 주소

rdi : 메모리 이동 및 비교 시 목적지 주소

rbp : 함수의 파람 및 변수의 주소를 가리킬 때 사용

rsp : 스택의 가장 위에 있는 주소를 가리킴



```shell
nano sum.c

gcc -S -fno-stack-protector -mpreferred-stack-boundary=4 -z execstack -o sum.a sum.c 
```

