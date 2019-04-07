## Chap6. 조건문

#### 조건문과 조건 연산자

```c
(scor >= 60) ? true : false;
```



<br>



### Hands-On

p240 charclass.c  

p241 calc1.c

p254 proper_tri.c

<br>



## Chap7. 반복문

#### 반복(iteration)

<br>



### 7.3 반복 루프에서 보초값 사용하기

데이터의 끝을 알리는데 사용되는 데이터 값을 `센티널(sentinel)` 또는 `보초값` 이라고 한다. 센티널을 일반적인 데이터값에서는 절대 등장 할 수 없는 값으로 선택하는 것이 좋다.

```c
#include <stdio.h>

int main(void)
{
	int grade, n;
	float sum, average;

	// 필요한 변수들을 초기화한다.
	n = 0;
	sum = 0;
	grade = 0;

	printf("성적 입력을 종료하려면 음수를 입력하시오\n");

	// 성적을 입력받아서 합계를 구하고 학생 수를 센다.
	while (grade >= 0)
	{
		printf("성적을 입력하시오: ");
		scanf_s("%d", &grade);

		sum += grade;
		n++;
	}

	sum = sum - grade; 	// 마지막 데이터를 제거한다. 
	n--;			// 마지막 데이터를 제거한다. 
	// 평균을 계산하고 화면에 출력한다.
	average = sum / n;
	printf("성적의 평균은 %f입니다.\n", average);

	return 0;
}
```

위의 코드로 보초값을 제거하지 않고 5, 15 , -1을 차례로 입력하면 6.3333이 나온다.

<br>



### Hands-On

p267 gugu.c  

p277 gcd.c

p310 [파이구하기](https://cloud.google.com/blog/products/compute/calculating-31-4-trillion-digits-of-archimedes-constant-on-google-cloud)