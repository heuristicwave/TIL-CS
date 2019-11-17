## Chap15. 전처리 및 비트 필드



### 자주 사용되는 매크로

```c
#define EOF		    (-1)		    // 파일의 끝 표시
#define DIGITS		"0123456789"	// 문자 상수 정의
#define getchar()	getc(stdin)		// stdio.h에 정의
#define putchar()	putc(stdout)	// stdio.h에 정의
```

<br>

### 함수 매크로

```c
#define AVERAGE(x, y, z)	( ((x) + (y) + (z)) / 3)
#define MAX 		        ( (x) > (y) ) ? (x) : (y)
```

> **매크로를 사용할 때 주의할 점**
>
> 함수 매크로에서는 매개 변수의 자료형을 써주지 않는다. 따라서 어떠한 자료형에 대해서도 적용이 가능하다.
>
> 함수 매크로에서는 매개 변수가 기계적으로 대치되기 때문에 반드시 매크로의 매개 변수들을 괄호로 묶어주어야 한다.
>
> ```c
> #define SQUARE(X) x*x	// x*x 보다는 ((x) * (x))
> ```
>
> - 매크로를 정의할 떄 매개 변수는 모두 사용되어야 한다.
> - 매크로 이름과 괄호 사이에 공백이 있으면 안 된다.
> - 매크로를 한 줄 이상으로 만들떄는 줄의 맨 끝에 \을 적어주면 한줄이 연장된다.

<br>

#### #연산자

#은 `문자열 변환 연산자(Stringizing Operator)`라고 불린다. 변수 앞에 #가 위치하면 매크로 호출에 의하여 전달되는 실제 인수는 큰따옴표로 감싸지고 문자열로 변환된다.



#### ##연산자

##은 `토큰 병합 연산자(token-pasting operator)`라고 불린다. 2개의 토큰을 따로 따로 치환한 후에 2개의 토큰을 합하는 역할을 한다.



#### 내장 매크로

```
__DATE__ : 소스가 컴파일된 날짜(월 일 년)로 치환된다.
__TIME__ : 소스가 컴파일된 시간(시:분:초)으로 치환된다.
__LINE__ : 소스 파일에서의 현재의 라인 번호로 치환된다.
__FILE__ : 소스 파일 이름으로 치환된다.
```



#### 비트 관련 매크로

```c
#define GET_BIT(w, k)	(((w) >> (k)) & 0x01)	// 변수의 w의 k번째 비트 값 반환
#define SET_BIT_ON(w, k)	((w) |= (0x01 << (k)))	// 변수의 w의 k번째 비트 값을 1로 설정
```



### #ifdef, #endif

#ifdef은 조건부 컴파일을 지시하는 전처리 지시자

조건부 컴파일? 어떤 조건이 만족되는 겨웅에만 지정된 소스 코드 블록을 컴파일

#ifdef는 #ifdef 다음에 있는 매크로를 검사하여 매크로가 정의되어 있으면 #if와 #endif 사이에 있는 모든 문장들을 컴파일

```c
#include <stdio.h>
#define DELUXE	// 정의되어 있을 떄만 컴파일된다.

int main(void)
{
#ifdef DELUXE
    printf("디럭스 버전");
#endif
    return 0;
}
```



#### undef

#undef는 매크로의 정의를 취소한다.

```
#define SIZE 100
#undef SIZE	//SIZE의 정의를 취소
#define SIZE 200
```



### 비트 필드 구조체

비트 필드 구조체는 구조체의 일종으로서 멤버들의 크기가 비트 단위로 나누어져 있는 구조체를 의미한다. 즉 비트들의 멤버로 가지는 구조체이다. 비트 필드를 사용하면 꼭 필요한 만큼의 비트만을 사용할 수 있어서 메모리를 효율적으로 사용하는 것이 가능하다.

```c
struct product {
	unsigned style : 3;	// unsigned가 3개가 아니라, unsingned 중에서 3개의 비트만을 사용
	unsigned size : 2;
	unsigned color : 1;	
}
```

style 멤버는 3비트로 정의되었으므로 0에서 7까지의 값을 가질 수 있다.

비트필드는 선언된 순서대로 unsigned 자료형 안에 하위 비트부터 순차적으로 저장된다.



bit_field.c

```c
#include <stdio.h>

struct product {
	unsigned style : 3;	// unsigned가 3개가 아니라, unsingned 중에서 3개의 비트만을 사용
	unsigned size : 2;
	unsigned color : 1;	
};

int main(void)
{
    struct product p1;
    
    p1.style = 5;
    p1.size = 3;
    p1.color = 1;
    
    printf("sizeof(p1) = %d\n", sizeof(p1));	// 4 <- 전체 unsigned int 형의 크기가 반환됨
    
    return 0;
}
```

