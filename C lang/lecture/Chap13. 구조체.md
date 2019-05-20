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

p571

```c

```



### 구조체의 배열

#### 구조체 배열의 선언과 초기화



```c

```



### 구조체와 포인터

#### 구조체를 가리키는 포인터



```c

```



#### 포인터를 멤버로 가지는 구조체



#### 문자 배열과 문자 포인터의 차이점



### 구조체와 함수

