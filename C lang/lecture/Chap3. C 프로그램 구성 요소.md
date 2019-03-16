## Chap3. C 프로그램 구성 요소

### 3.2 주석(comment)

  주석은 가독성을 높이고, 프로그램이 하는 일을 설명함.

<br>



### 3.3 전처리기

```c
#include <stdio.h>
```

헤더파일 `stdio.h`를 소스 코드 안에 포함시켜줘~

<br>



### 3.4 함수

사용자 정의 함수 : 우리가 직접 정의하는 함수

라이브러리 함수 : 외부에서 가져와서 사용하는 함수 ex) printf()

<br>



### 3.5 변수

variable 프로그램이 사용하는 데이터를 일시적으로 저장할 목적으로 사용되는 메모리 공간



변수선언

```c
int x;
```

"컴파일러야 나는 x라는 이름의 변수를 사용할건데, 이건 자료형이 int야!"

<br>



### 3.6 수식과 연산

대입연산

```c
x = 100;	// 변수 x에 100을 대입한다.
```

"컴파일러야 나는 아까만든 변수x는 100이라고 너한테 알려준다!"

<br>



### 3.7  printf()

변수값 출력

```c
printf("두수의 합: %d", sum);	// %d(decimal)는 출력형식
```

"컴파일러야 나는 변수 sum의 값을 10진수 정수 형태로 출력하길 원해~"

<br>



### 3.9  scanf()

```c
scanf("%d", &x);	// %d : 형식 지정자, &x : 값을 저장할 변수
```

변수 이름 앞에 **&(앰퍼샌드)**라는 주소 연산자가 있다. [출처](https://m.blog.naver.com/PostView.nhn?blogId=zzffgg&logNo=220663594667&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F)

![주소 연산자](http://mblogthumb4.phinf.naver.net/20160324_191/zzffgg_1458745246100vFQi7_PNG/3.png?type=w800)
