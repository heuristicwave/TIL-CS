## Chap13. 구조체



### 구조체란?

C에서의 자료형

- 기초자료형 : int, char, double ...
- 파생자료형 : 배열, 포인터, 구조체, 공용체
- 사용자정의 자료형 : typedef, enum



구조체는 서로 다른 자료형들을 하나로 묶는 것이다.

```c
// 구조체 선언
struct student {	// struct라는 키워드로 정의, student는 구조체 테그 라고 한다.
    int number;		// 구조체의 멤버
    char name[10];
    double grade;
};	// 세미콜론 필수
```

구조체를 정의하는 것은 만드는 틀을 정의하는 것과 같다.



#### 구조체 변수 생성

```c
int main(void){
	struct student s1;	// s1이 차지하는 메모리 공간의 크기는 각 멤버들의 크기를 합치면 알 수 있다.
    // 4+10+8=22바이트
}
```

> 구조체 정의와 구조체 변수 선언 동시에 하기
>
> ```c
> struct student {	
>     int number;		
>     char name[10];
>     double grade;
> } s1;
> ```



#### 구조체의 초기화

```c
struct student {	
    int number;		
    char name[10];
    double grade;
};

struct student s1 = { 24, "kim", 4.3 };
```



#### 구조체의 멤버 참조

```c
s1.grade = 3.8;	// grade에 3.8대입
strcpy(s1.name, "kim");	// 멤버가 문자배열 이라면 strcpy()를 사용하여 문자열을 저장
```



#### 이름없는 구조체

구조체를 정의할 때 태그 이름은 생략하여도 무방하다. 그러나 이 경우 구조체의 변수를 더 이상 생성할 수 없다. 따라서 필요한 모든 구조체 변수를 정의와 함께 선언해야 한다.

```c
struct student {	
    int number;		
    char name[10];
    double grade;
} s1, s2, s3;
```



### 구조체의 활용

#### 구조체를 멤버로 가지는 구조체

```c
struct date {	
    int year;
    int month;
    int day;
};

struct student {	
    int number;		
    char name[10];
  	struct date dob;	// 구조체 안에 구조체 포함
    double grade;
};
struct student s1;
// 멤버변수 접근
s1.dob.year = 1983;
```



#### 구조체 변수의 대입과 비교

```c
/// 요소 대입 아래 2가지 방법 모두 동일한 효과
p2 = p1;

p2.x = p1.x;
p2.y = p1.y;
////////////////////////////////////////////
p1 == p1	// 컴파일 오류

(p2.x = p1.x) && (p2.y = p1.y);	// 올바른 방법
```



### 구조체의 배열

#### 구조체 배열의 선언과 초기화

```c
/// 구조체 배열의 선언
struct student list[100];	// 구조체의 배열로서 구조체 100개를 저장할 수 있다.

/// 요소 접근
list[2].number = 24;
strcpy(list[2].name, "alice");

/// 구조체 배열의 조기화
struct student list[3] = {
    {1, "Park", 3.42},
    {2, "Kim", 3.1},
    {3, "Lee", 4.2}	// 맨 마지막 원소에는 콤마를 붙이지 않는다.
};

/// 원소의 개수 계산

sizeof(list)/sizeof(list[0]);
sizeof(list)/sizeof(struct student);
```



### 구조체와 포인터

#### 구조체를 가리키는 포인터

```c
struct student s = { 24, "Kim", 4.3 };
struct student *p;	// 구조체 student를 가리키는 포인터 선언

p = &s;
// 포인터를 통한 구조체 정보 접근 (*p)가 구조체가 됨
printf("학번 = %d 이름 = %s 학점 = %f \n", (*p).number, (*p).name, (*p).grade);
```



**간접 멤버 연산자** : `->`

구조체 포인터를 이용하여 멤버에 접근하기 위하여 사용

```c
// 포인터 p가 가리키는 구조체의 멤버 number
printf("학번 = %d 이름 = %s 학점 = %f \n", p->number, p->name, p->grade);
```

> 혼동하기 쉬운 구조체 변수와 구조체 포인터
>
> *p.number
>
> *(p.number)과 같다. 구조체 p의 멤버 number가 가리키는 것이라는 의미
>
> 만약 number가 포인터가 아니면 오류
>
> 
>
> *p->number
>
> *(p->number)와 같다. p가 가리키는 구조체의 멤버 number가 가리키는 내용을 의미
>
> 만약 number가 포인터가 아니면 오류



#### 포인터를 멤버로 가지는 구조체

구조체는 멤버로 포인터를 가질 수 있다.



#### 문자 배열과 문자 포인터의 차이점

```c
// 1. 문자 배열 선언
struct A {
    int number;
    char name[10];
}

// 2. 문자 포인터 선언
struct B {
    int number;
    char *p;
}

// 변수를 생성하고 초기화 하는 것은 1, 2의 방법에 있어 오류는 없다.
struct A s1 = { 20190523, "aaa" };
struct B s2 = { 20190523, "bbb" };
```

그러나, 문자열 구조체 내부의 배열에 aaa가 저장되는 것은 10 바이트의 공간이 구조체 내부에 할당되는 것이다

때문에 아래와 같은 코드가 가능하다.

```c
scanf("%s", s1.name);
```

반면 구조체 s2의 경우, 구조체 내부에는 포인터 p를 위한 4바이트의 공간만 할당된다. 즉, 문자열을 위한 공간은 구조체 s2에 없다. 그렇기 때문에 아래와 같이 문자열을 받아서 저장할 수 없다. 그러나 텍스트 세그먼트에 ccc를 저장하는 것은 가능하다.

```c
scanf("%s", s2.name);	// ERROR

s2.p = "ccc";	// 가능
```



### 구조체와 함수

구조체는 함수의 인수로도 사용이 가능하고 함수에서 반환값으로 반환될 수 있다. 구조체가 **인수나 반환값**으로 사용될 때는 **값에 의한 호출**의 원칙이 적용된다. 단점으로 만약 구조체의 크기가 클 경우에는 상당한 시간이 소요된다. 때문에 구조체를 직접 전달하거나 반환하는 것보다는 **포인터를 사용**하는 것이 바람직하다.



#### 구조체를 함수의 인수로 넘기는 방법

구조체의 복사본 넘기기

```c
int equal(struct student s1, struct student s2)
{
	if ( s1.number == s2.number ) return 1;
    else return 0;
}

int main(void)
{
	struct student a = { 1, "aaa", 3.8 };
	struct student b = { 2, "bbb", 4.1 };
    if( equal(a, b) == 1){
		printf("같은 학생 \n");
    }
    else {
		printf("다른 학생 \n");
    }
}
```



구조체의 포인터를 보내기

```c
// int equal(struct student const *p1, struct student const *p2)	// 원본 변경 금지
int equal(struct student *p1, struct student *p2)
{
	if ( p1->number == p2->number ) return 1;
    else return 0;
}

int main(void)
{
	struct student a = { 1, "aaa", 3.8 };
	struct student b = { 2, "bbb", 4.1 };
    if( equal(&a, &b) == 1){
		printf("같은 학생 \n");
    }
    else {
		printf("다른 학생 \n");
    }
}
```



### 공용체

C에서는 같은 메모리 영역을 여러 개의 변수들이 공유할 수 있게 하는 기능이다. 같은 메모리 영역을 여러 개의 변수가 공유하도록 하여 메모리를 절약할 수 있다. 공용체를 선언하고 사용하는 방법은 구조체와 아주 비슷하다. 다만 공용체는 멤버들이 같은 공간을 공유하기 때문에 동시에 모든 멤버 변수들의 값을 저장할 수는 없으며 어떤 순간에는 하나의 멤버만 존재할 수 있다.

[구조체와 공용체 차이](<https://yoon90.tistory.com/22>)



### 열거형

변수가 가질 수 있는 값을은 나열한 자료형, 열거형을 사용하면 특정한 숫자 대신에 기호를 사용함으로서 프로그램의 이해도를 향상 시킬 수 잇고, 변수가 열거된 값 이외의 값을 취하는 것을 막아 오류를 줄여준다.

```c
enum days { SUN=1, MON, TUE, WED, THU };	// 1부터 시작하기
// 식별자들의 값을 지정할수도 있고 (SUN=7) 작성하지 않으면 자동으로 0부터 시작한다
```



### typedef

#### typedef의 개념

새로운 자료형(type)을 정의(define)하는 것이다. 이 키워드는 C의 기본 자료형을 확장시키는 역할을 한다.

```C
typedef unsinged char BYTE;

BYTE index;				// unsinged char index; 와 같은기능
```

기존의 자료형 unsigned char를 BYTE로 새롭게 정의하는 것이다



#### 구조체로 새로운 자료형 만들기

```c
struct point {
	int x;
	int y;
};

typedef struct point POINT;	// 새로운 POINT 자료형으로 생성

POINT a, b;

/// 구조체의 선언과 typedef을 같이 사용할 수도 있다.
typedef struct point {
	int x;
	int y;
} POINT;
```



#### typedef의 장점

1. 이식성을 높여준다

   컴퓨터 시스템에 따라 int형은 2byte, 4byte이기도 하다. 컴퓨터의 시스템이 달라지면 typedef 정의만 변경하면 된다. C 컴파일러가 size_t나 time_t와 같은 자료형을 만들어서 사용하는 이유도 이러하다. 상기 자료형은 연산자가 반환하는 값의 타입인데, 컴퓨터 시스템에 따라 달라질 수 잇어 자료형을 고정시키지 않고 헤더 파일에서 정의한 size_t를 사용하는 것이다.

2. #define과의 차이점

   typedef는 컴파일러가 직접 처리하며 VECTOR와 같은 자료형의 정의는 #define에서는 불가하다.

3. 문서화의 역할

   주석을 붙이는 효과가 있어 구조체가 무엇을 표현하는지 확실하게 알 수 있다.

