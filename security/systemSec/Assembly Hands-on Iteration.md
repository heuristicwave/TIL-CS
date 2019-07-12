## Hands on Iteration



### 반복문 연습

```assembly
section .data
		msg db "A"
section .text			; 코드영역 기입
		global _start
		
_start:
		mov	rax, 1		; 1 == system call write
		mov	rdi, 1		; rdi에 1(fd)을 넣어서 표준출력임을 알림
		mov	rsi, msg	; 문자열 위치를 rsi가 가질 수 있도록
		mov	rdx, 1		; 해당 문자열의 길이, 한글자 출력
		mov	r10, 1		; 반복문을 위해 사용하는 레지스터, 1로 초기화
again:
		cmp	r10, 100	; r10과 100을 서로 비교
		je done			; 왼쪽과 오른쪽 항이 서로 같으면 done함수 실행
		syscall			; 사전에 rax에 1이 있으니, 시스템 콜 실행
		mov	rax, 1		; rax에 1을 넣음. 함수종료, rax에 결과가 담겨 다시 1로초기화
		inc r10			; r10 레지스터의 값을 1 증가 (increment)
		jmp again		; again 함수로 점프
done:					; exit 시스템 콜 실행시키기 위한 절차
		mov	rax, 60		; 없다면 세그멘테이션 오류 발생
		mov rdi, 0
		syscall
		
```

#### 파일 생성

```shell
nasm -f elf64 -o loop -o loop.s	// 컴파일해서 오브젝트 파일로 생성
ld -o loop loop.o	// 파일을 링킹해서 실직적인 실행 파일을 생성
```



> 궁금증?
> [Assembly Files: Difference between .a .s .asm](https://stackoverflow.com/questions/34098596/assembly-files-difference-between-a-s-asm)



**Create Star.asm**

```assembly
section .data
	STAR	db '*'
	EMPTY	db 0x0a	; 개행문자
	
section .text
	global _start
	
_start:
	mov		rax, 1	; WRITE 시스템 콜 설정
	mov		rdi, 1	; 기본 출력 모드
	mov		rdx, 1	; 출력 길이 설정하기
	mov		r10, 0	; 인덱스
	mov 	r9, [rsp+16] ; 사용자가 인자 값으로 입력한 문자열의 값을 읽어 r9저장
	; rsp가 가리키는 곳은 처음의 rbp와 동일하고, 인자 값은 16바이트 아래에 있기 때문
    
    cmp 	r9, 0	; 사용자의 입력이 없는 경우
    je		_done	; 프로그램 종료
    
    mov		cl, [r9] ; 한 바이트만 cl에 저장하기
    movzx	r9, cl	; 문자 형태의 cl을 r9에 저장하기
    sub		r9, 0x30 ; 인덱스 i 설정하기, 16진수로 30의 값을 빼줌(0x30 == '0')
    
    cmp		r9, 0	; 입력이 0인 경우
    je		_one	;	별 하나 출력하고 종료하기
    
    mov		r8, r9  ; r8에 저장하기
    xor		r9, r9	; i를 초기화하기
    call	_syscall
    
_small:	; 첫번째 포문, j번 역할 수행 i - 별의 개수
	cmp		r9, r8 	; j가 r8이 된 경우
	je		_down  	; 내려가는 함수 실행하기
	mov		rsi, EMPTY	; 공백출력 설정하기
	syscall	;	출력 함수 실행하기
	mov		rax, 1 	; WRITE 시스템 콜 설정
	mov		r10, 0 	; 인덱스 초기화
	add		r9, 1	; i를 1증가시키기
	jmp _small		; 다시 출력하기
	
_up:
    cmp		r9, r8	; j가 r8이 된 경우
    je		_down 	; 내려가는 함수 실행하기
    mov		rsi, EMPTY	; 공백출력 설정하기
    syscall	; 출력 함수 실행하기
    mov		rax, 1 	; WRITE 시스템 콜 설정하기
    mov 	r10, 0 	; 인덱스 초기화
    add 	r9, 1	; i를 1 증가시키기
    jmp _small 		; 다시 출력하기
    
_down:	; 아래쪽 0이 될때까지 출력
	cmp		r9, 0	; i가 0이 된 경우
	je		_done	; 내려가는 함수 실행하기
	mov		rsi, EMPTY ; 공백 출력 설정하기
	syscall	; 출력 함수 실행하기
	mov		rax, 1 ; WRITE 시스템 콜 설정하기
	mov		r10, 0 ; 인덱스 초기화
	sub		r9, 1,	; i를 1 감소시키기
	jmp	_big		; 다시 출력하기
	
_big:
	cmp		r10, r9	; i번 출력한 경우
	je		_down 	; down으로 이동하기
    mov		rsi, STAR ; 별 출력 설정하기
    syscall	; 출력 함수 실행하기
    mov		rax, 1;	WRITE 시스템 콜 설정하기
    inc		r10 ; j를 1 중가시키기
    jmp		_big	; 다시 출력하기
    
_one:
	mov		rsi, STAR ; 별 출력 설정하기
	syscall	; 출력 함수 실행하기
	mov		rax, 1 ; WRITE 시스템 콜 설정하기
	mov		rsi, EMPTY ; 공백출력 설정하기
	syscall	; 출력 함수 실행하기
	call _done ; 프로그램 종료하기
	
_done:
	mov		rax, 60
	mov		rdi, 0
	syscall
	
_syscall:
	syscall
	ret
	
```

입력값(8)이 스택의 최하위에 들어가고 그위에 ret(8) 그위에 rsp 담겨, 16만큼 더해 r9에 넣어줌



---

해당 자료는 [나동빈님 블로그](https://blog.naver.com/PostView.nhn?blogId=ndb796&logNo=221055387529&parentCategoryNo=&categoryNo=98&viewDate=&isShowPopularPosts=false&from=postList)를 참조하여 공부하였습니다.