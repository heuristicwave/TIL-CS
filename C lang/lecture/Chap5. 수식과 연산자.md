## Chap4. 변수와 자료형

### 5.2 대입 연산자

#### 복합 대입 연산자

```c
#include <stdio.h>

int main(void)
{
    int x = 10; y = 10; z = 33;
    
    x += 1;
    y *= 2;
    z %= 10 + 20;
    
    printf("x = %d	y = %d	z = %d \n", x, y, z);
    return 0;
}
```



<br>



### 5.3 관계 연산자

#### 복합 대입 연산자관계 연산자 사용시 주의점

```c
x = y;	// y의 값에 x에 대입한다. 수식의 값은 x의 값이다.
x == y;	// x와 y가 같으면 1, 다르면 0이 수식의 값이 된다.
```

<br>



### 5.4 논리 연산자

논리 연산자는 여러 개의 조건을 조합하여 참인지 거짓인지를 따진다.

```c
// 윤년 프로그램
#include <stdio.h>

int main(void)
{
    int year, result;
    
    printf("연도를 입력하시오: ");
    scanf("%d", &year);
    
    result = ((year % 4 == 0) && (year % 10 != 0)) || (year % 400 == 0);
    printf("result=%d \n", result);
    
    return 0;
}
```

<br>



### 5.6 콤마 연산자 (중요하진 않음)

콤마 연산자는 모든 연산자 중에서 우선순위가 가장 낮으며, 한정된 공간에 여러 개의 문장을 넣을 때 사용된다.

```
x = (2+3, 5-3);	// 앞이 먼저 수행
```

<br>



### 5.7 비트 연산자

정보처리기사 & 이산수학 (지금 읽고 넘어가면 좋음)

<br>



### 5.8 형변환

**형변환(type conversion)**이란 int형의 값이 double형의 값으로 변환되는 것과 같은, *데이터의 형이 변환되는 것을 의미*

- 자동적 형변환 : 컴파일러에 의하여 자동으로 수행

  하나의 수식에서 서로 다른 자료형이 사용되면 모든 자료형은 그 중에서 가장 높은 등급의 자료형으로 변환된다.

  ```c
  int > unsigned int > long > unsigned long > float > double > long double
  ```

  

- 명시적 형변환 : 프로그래머가 명시적으로 데이터의 형을 변환

  **형변환 연산자**를 상수나 변수 앞에 적어준다.

  ```c
  (int)1.23456	// int형으로 반환 => 1
  f = (double)i;	// 변수 i의 값이 double형으로 변환된다 => 1.0
  ```

<br>



### 5.9 연산자의 우선순위와 결합 규칙

```c
// F11로 한줄씩 디버깅 하며 확인해 보기

#include <stdio.h>

int main(void)
{
	double f_temp;
	double c_temp;

	printf("화씨온도를 입력하시오");
	scanf_s("%lf", &f_temp);
	c_temp = 5 / 9 * (f_temp - 32);
	printf("섭씨온도는 %f입니다", c_temp);
	
	return 0;
}	
```

