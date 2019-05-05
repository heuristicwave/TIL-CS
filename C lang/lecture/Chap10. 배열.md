## Chap10. 배열

### 인덱스의 범위

배열의 인덱스의 범위는 0부터 시작한다.

메모리주소가 0부터 시작하기 때문(포인터와 밀접한 연관)

[Why does the indexing of Array start with Zero in C?](<https://developerinsider.co/why-does-the-indexing-of-array-start-with-zero-in-c/> )

> 배열의 이름은 본질적으로 포인터이며, 메모리 위치에 대한 참조이므로,  array [n]은 시작 요소로부터 n-elements 떨어진 메모리 위치를 참조한다. 즉, 인덱스가 오프셋으로 사용된다. 배열의 첫 번째 요소는 배열이 참조하는 메모리 위치에 정확하게 포함되므로 (0 요소 거리) array [0]으로 표시해야 한다. 대부분의 프로그래밍 언어는 이런 식으로 설계되었으므로 0부터 인덱싱하는 것이 언어에 내재되어 있다.



### 배열의 초기화

```c
int grade[5] = { 0 };	// 모든 원소가 0으로 초기화 된다.
int grade[5] = { 10, 20, 30 };	// 남은 2개의 원소는 0으로 초기화 된다.
```



### 배열 요소의 개수를 계산하는 방법

```c
배열의 크기 = sizeof(배열) / sizeof(배열 원소)
    
ex) int형의 크기가 10인 배열에서, sizeof(배열)은 40이 나오니 sizeof(int) 요소의 크기로 나눠야함.
```



#### 배열과 함수

배열의 경우에는 단순한 "값에 의한 호출"이 아니다. 배열이 인수인 경우에는 배열의 원본이 매개 변수를 통하여 전달된다.

> `const` 지정자를 배열 매개 변수 앞에 붙이면 그 배열 원소는 변경이 불가능 하다.

배열을 함수로 전달하는 예제(연습문제 2번에 활용 가능)

```c
#include <stdio.h>
#define STUDENT 5

int get_average(int scores[], int size);	// 배열은 받는 매개 변수는 크기를 적어주지 않아도 됨.

int main(void)
{
    int scores[STUDENTS] = { 1, 2, 3, 4, 5};
    int avg;
    
    avg = get_average(scores, STUDENTS);
    printf("평균은 %d입니다.\n", avg);
    
    return 0;
}

int get_average(int scores[], int size)
{
	int i;
    int sum = 0;
    
    for(i=0; i<size; i++)
        sum += scores[i];
    
    return sum / size;
}
```



#### 원본 배열의 변경

배열은 매개 변수를 통하여 원본을 참조하는 것이기 때문에 항상 조심 해야 한다. 만약 함수 안에서 매개 변수를 통.하여 배열 요소를 변경한다면 이것은 원본 배열을 변경시키는 결과를 가져온다.

> [배열의 메모리 주소가 전달됨](<https://dojang.io/mod/page/view.php?id=562> )
>
> [배열을 함수의 매개변수로 사용하기](<https://goandroidtips.com/blog/%EB%B0%B0%EC%97%B4%EC%9D%84-%ED%95%A8%EC%88%98%EC%9D%98-%EB%A7%A4%EA%B0%9C%EB%B3%80%EC%88%98%EB%A1%9C-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0/> )



modify.c

```c
#include <stdio.h>
#define SIZE 7

void modify_array(int a[], int size);
void print_array(int a[], int size);

int main(void)
{
	int list[SIZE] = { 1, 2, 3, 4, 5, 6, 7 };

	print_array(list, SIZE);
	modify_array(list, SIZE);
	print_array(list, SIZE);

	return 0;
}

void modify_array(int a[], int size)
{
	int i;

	for (i = 0; i < SIZE; i++)
		++a[i];
}

void print_array(int a[], int size)
{
	int i;

	for (i = 0; i < SIZE; i++)
		printf("%3d ", a[i]);
	printf("\n");
}

////////////////// 실행결과 //////////////////
1	2	3	4	5	6	7
2	3	4	5	6	7	8
```



#### 원본 배열의 변경을 금지하는 방법

const 지정자를 배열 매개 변수 앞에 붙이면 그 배열 요소는 변경이 불가능 해진다. 단순히 배열 요소를 출력하는 함수는 배열을 변경할 필요가 없으므로 const를 사용하는것이 안전하다.

```c
void print_array(const int a[], int size)
{
	int i;

	for (i = 0; i < SIZE; i++)
		printf("%3d ", a[i]);
	printf("\n");
}
```



### 2차원 배열

two_dim_array.c

```c
#define ROWS 3
#define COLS 5

void main()
{
    int s[ROWS][COLS];	// 2차원 배열 행(row), 열(column) 순서로 선언
    int i, j;		// 2개의 인덱스 변수
    
    for (i=0; i<ROWS; i++)
        for (j=0; j<COLS; j++)
            s[i][j] = rand % 100;
    
    for (i=0; i<ROWS; i++)
    {
        for (j=0; j<COLS; j++)
            printf("%02d ", s[i][j]);
        printf("\n");
    }
}
```



#### hands-on

p430 dice.c
```c
#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

int main(void)
{
    int freq[SIZE] = {0};
    int i;
    
    for(i=0; i<10000; i++)
        ++freq[ rand() % 6];    //freq[0] ~ freq[5] 으로 나오면 ++횟수 카운트
        
    printf("================\n");
    printf("면 빈도\n");
    printf("================\n");
    
    for(i=0; i<SIZE; i++)
        printf("%3d %3d \n", i+1, freq[i]); // 카운트된 횟수 출력
        
    return 0;
}
```

p432 theater.c
```c
#include <stdio.h>
#define SIZE 10

int main(void)
{
	char ans1;
	int ans2, i;
	int seats[SIZE] = { 0 };  // 1차원 배열을 선언하고 0으로 초기화

	while (1)
	{
		printf("좌석을 예약하시겠습니까?(y 또는 n) ");
		scanf(" %c", &ans1);    // 공백 문자는 제외하고 일반 문자만을 입력받는다.

		if (ans1 == 'n')
			break;
		printf("-----------------------\n");
		printf("1 2 3 4 5 6 7 8 9 10\n");
		printf("-----------------------\n");

		for (i = 0; i < SIZE; i++)
			printf(" %d", seats[i]);
		printf("\n");

		printf("몇번째 좌석을 예약하시겠습니까");
		scanf("%d", &ans2);
		if (seats[ans2-1] == 0) {
			seats[ans2-1] = 1;
			printf("예약되었습니다.\n");
		}
		else
			printf("이미 예약된 자리입니다.\n");
	}

	return 0;
}
```

p442 순차탐색



## 심화

selection_sort.c

```c
#include <stdio.h>
#define SIZE 10

int main(void)
{
    int list[SIZE] = { 3, 2, 9, 7, 1, 4, 8, 0, 6, 5};
    
    int i, j, temp, least;
    
    for (i=0; i <SIZE-1; i++)
    {
		least = i;
        for(j=i+1; j < SIZE; j++)
            if(list[j] < list[least])
                least = j;
        temp = list[i];
        list[i] = list[least];
        list[least] = temp;
    }
    for(i=0; i<SIZE; i++)
        printf("%d", list[i]);
    printf("\n");
    
    return 0;
}
```

p455 tic_tac_toe.c