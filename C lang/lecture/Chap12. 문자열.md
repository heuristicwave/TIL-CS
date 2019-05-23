## Chap12. 문자열



### 문자열

A	: 컴파일러는 변수의 이름으로 간주

'A'	: 문자 A

"A"	: 문자 A로 이루어진 문자열



문자열은 여러 개의 문자들이 모인 것이므로 char형의 배열을 이용하여 저장하고 문자열의 끝을 NULL문자로 표시

NULL이 없다면 쓰레기 문자가 함께 배열에 들어가고 어디까지가 의미있는 문자열인지 구분할 수 없기 때문에 활용한다. 따라서 문자 배열은 저장하고자 하는 문자열의 크기보다 항상 하나 커야한다.



#### 문자 배열의 초기화 방법

```c
// 1. 배열의 초기화 처럼 사용하기
char str[4] = { 'a', 'b', 'c', '\0'};
// 2. 문자열 상수를 사용하여 초기화 하기
char str[4] = "abc";

/// 문자 배열의 크기가 초기화 문자열 보다 크면 남는 공간은 NULL로 초기화 된다.
/// NULL 문자열로 초기화하기
char str[6] = "";

/// 컴파일러는 자동으로 배열의 크기를 초기화에 맞춘다
char str[0] = "abc";	// 배열의 크기는 4
```



#### 문자열의 변경

```c
/// 문법오류
char str[] = "hello";
str = "world";
/// strcpy()라이브러리 활용
strcpy(str, "world");
```



#### 문자열 상수와 포인터

문자열 상수는 "helloworld"와 같이 프로그램 소스 안에 포함된 문자열을 의미한다. 문자열 상수는 메모리 영역 중에서 **텍스트 세그먼트** 라고 불리는 특수한 메모리 영역에 저장된다. 텍스트 세그먼트는 읽기는 가능하지만, 변경할 수 없는 메모리 영역이다.

아래 코드는 문자열 상수 HelloWorld만 텍스트 세그먼트에 저장된 경우다.

```c
char *p = "HelloWorld";	// 문자열 상수 "HelloWorld"가 저장된 주소가 포인터 변수 p에 저장된다.
strcpy(p, "Hi");	// 실행오류

// P의 메모리주소 변경
p = "Hi";	// 가능, 포인터 변수 P는 데이터 세그먼트에 위치해 있기 때문이다.
```

> [메모리구조-데이터,텍스트,BSS](<https://thrillfighter.tistory.com/217> ) 



데어터 세그먼트에 문자열을 넣고 변경하기

```C
char p[] = "HelloWorld";
strcpy(p, "Goodbye");	// 변경가능
```



### 문자 입출력 라이브러리

#### getchar() 와 putchar()

<stdio.h>에 포함되어, 하나의 문자를 입력 받거나 출력한다.

```c
int getchar(void);
int putchar(int c);

// 함수 반환형이 char형이 아니라 int인 이유는 입력의 끝을 나타내는 EOF를 체크하기 위해서다.
// 콘솔에서는 ctrl+Z가 EOF를 의미한다
int ch;
while ((ch = getchar()) != EOF)
    putchar(ch);
```

> [EOF에 대한 이해](<https://m.blog.naver.com/PostView.nhn?blogId=zim12345&logNo=220136803595&proxyReferer=https%3A%2F%2Fwww.google.com%2F> )

getchar()는 버퍼를 사용하기 때문에, 엔터키를 누르면 버퍼에 저장된 문자들이 프로그램으로 전달된다. 보통 입출력에 버퍼를 사용하는 것은 다중 사용자 환경에서 효율적으로 사용하기 위해서다. _getch()는 getchar()와 동일하지만 버퍼를 사용하지 않는다.



#### _getch()와 _putch()

 <conio.h>에 포함되어, ANSI C표준 라이브러리 함수에 포함되지 않는다.

위 두함수는 에코를 하지 않는다. => 문자를 입력받으면서 화면에 출력하지 않는다.

```c
int ch;
while ((ch = getchar()) != 'q')	// ctrl도 하나의 문자로 입력되어 EOF를 사용할 수 없다.
    putchar(ch);
```



#### 문자열 입출력 라이브러리

### get_s()와 puts()을 이용한 문자열 입출력
```c
char buf[100];
gets_s(buf, 100);   // 최대 입력 개수는 100이다. 배열의 이름이 배열의 주소이므로 &buf와 같이 하지 않는다
puts(buf);
```
get_s()는 표준 입력으로부터 줄바꿈 문자 '\n' 가 나올 때까지 한 줄의 라인을 문자열로 입력받는다.
문자열에 '\n'은 포함되지 않으며 대신에 자동으로 NULL문자 '\0'을 추가한다.
입력받은 문자열은 buf가 가리키는 주소에 저장된다.
만약 성공적으로 입력받았으면 인수 buf가 그대로 반환되고, 실패하면 NULL값이 반환된다.

puts()는 str가 가리키는 문자열을 받아서 화면에 출력하는 함수
이때 문자열에 끝에 있는 NULL문자 '\0'는  줄바꿈 문자 '\n'로 변경된다.
출력 작업이 성공적이었으면 음수가 아닌 값이 반환된다. 만약 실패하면 EOF를 반환한다.



### 문자 처리 라이브러리
`ctype.h`를 포함하며, is...()의 형태의 함수다. 검사 결과가 참이면 0이 아닌 값이 반환되고 거짓이면 0이 반환된다.



### 문자열 처리 라이브러리

`string.h`를 포함하며, 함수 이름은 str로 시작한다. 

```c
/// 문자열 길이 strlen() 
int size = strlen("abcdef");

/// 문자열 복사 strcpy()
char a[6];
char b[6] = "hello";
strcpy(a, b);	// b를 a에 복사

// 복사되는 문자의 개수 제한하기
strcpy(a, b, 3);	// hel만 복사

/// 문자열 연결 strcat()
char a[12] = "Hello";
char b[6] = "World";
strcat(a, b);	// b를 a뒤에 붙이고 끝에 Null 문자로 종료

// 복사되는 문자의 개수 제한하기
strcat(a, b, 3);	// a가 hellowor된다

/// 문자 검색 strchr()
char *p = strchr("dog", 'g');	// g문자의 주소를 반환한다, 찾지 못하면 Null이 반환

/// 문자열 검색 strchr()
char *p = strchr("dog", "og");	// og문자의 위치의 주소를 반환한다, 찾지 못하면 Null이 반환
```



#### 문자열 비교 strcmp()

```c
/// 같으면 1이아닌 0이 반환된다
int result = strcmp("a", "a");	// 0이 반환된다
```

strcmp(s1, s2)는 문자열을 구성하는 문자들의 아스키 코드 값을 차례대로 비교한다. 만약 두 문자의 코드값이 같다면 계속하여서 다음 문자들을 비교한다. 

- 반환값 <0 : s1이 s2 보다 앞에 있다.
- 반환값 0 : s1 == s2
- 반환값 >0 : s1이 s2보다 뒤에 있다.



#### 문자열 토큰 분리 strtok()

**토큰**이란 문법적으로 더 이상 나눌 수 없는 기본적인 언어 요소를 말한다. 예를 들어 문장에서 공백문자로 분리된 단어들을 토큰이라고 할 수 있다.

```c
char s[] = "I am ironman";
char delimit[] = " ";
char *p = strtok(s, delimit);	// 문자열을 스페이스 문자를 사용해 단어들로 분리

// strtok()는 첫 번째 토큰에 대한 포인터를 반환한다. 만약 계속하여서 다음 토큰을 읽으려면 s대신에 Null을 넣으면 된다. 즉 나머지 토큰들을 strtok(NULL, " ")호출에 의하여 추출된다.
```

strtok.c

```c
#include <stdio.h>
#include <string.h>

char s[] = "I love U three thousand";
char seps[] = " ,\t\n";	// 분리자는 스페이스 문자와, 쉼표, 탭, 줄바꿈 문자이다.
char *token;

int main(void)
{
    token = strtok(s, seps);	// 문자열에서 첫번째 토큰을 얻는다.
    
    while(token != NULL) {	// 문자열 s에 토큰이 있는 동안 반복한다.
        printf( "토큰: %s\n", token);
        token = strtok( NULL, seps );	// 다음 토큰을 얻으려면 NULL을 인수로 준다.
    }
    return 0;
}
```



### 문자열 수치 변환

sscanf(s, ...) : 문자열 s로부터 지정된 형식으로 수치를 읽어서 변수에 저장한다.

sprintf(s, ...) : 변수의 값을 형식 지정자에 따라 문자열 형태로 문자 배열 s에 저장한다.

```c
char s[] = 100;
int value;

sscanf(s, "%d", &value);	// a문자열에서 %d 형식으로 읽어서 value에 저장한다. 문자열 -> 수치
```



#### 문자 포인터 배열을 사용하는 방법

2차원 문자 배열을 문자열들로 초기화 하면 2차원 배열의 각가의 행이 주어진 문자열로 초기화된다.

만약 문자열의 길이가 서로 다르면 길이가 짧은 문자열이 저장된 행은 낭비되는 공간이 많아진다.

포인터의 배열을 이용하면 **메모리 공간을 정확하게 문자열의 크기가 맞추**어 사용할 수 있다.

```c
char *s[3] = {
	"init",
    "open",		// s[1]로 출력하면 open 출력
    "close"
}
```

각 포인터는 메모리에 저장된 문자열 상수의 주소를 가지고 있다. 문자열 상수는 문자열의 크기만큼만 자리를 차지한다. 따라서 공간을 절약할 수 있으나, **한번 문자열이 결정되면 문자열의 내용을 변경할 수 없다.**


문자열 예제

[encrypt.c](<https://github.com/heuristicwave/TIL-CS/blob/master/C%20lang/encrypt.c> )

[hangman.c](<https://github.com/heuristicwave/TIL-CS/blob/master/C%20lang/hangman.c>)