## Chap10. 배열



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

<br>

#### 배열과 함수

배열의 경우에는 단순한 "값에 의한 호출"이 아니다. 배열이 인수인 경우에는 배열의 원본이 매개 변수를 통하여 전달된다.

> `const` 지정자를 배열 매개 변수 앞에 붙이면 그 배열 원소는 변경이 불가능 하다.



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
정렬 및 2차원 배열 3판 교안보고 넣을만한것들 정리하기
