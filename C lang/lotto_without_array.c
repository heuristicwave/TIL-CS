#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 45

int lotto();

int main(void)
{
	lotto();

	return 0;
}

int lotto()
{
	int i;
	int set;
	int a1, a2, a3, a4, a5, a6;

	srand((unsigned)time(NULL));

	for (set = 0; set < 10; set++) {
		printf("%d번째 ", set + 1);

		a1 = 1 + rand() % MAX;
		a2 = 1 + rand() % MAX;
		a3 = 1 + rand() % MAX;
		a4 = 1 + rand() % MAX;
		a5 = 1 + rand() % MAX;
		a6 = 1 + rand() % MAX;

		while (a1 == a2) {
			a2 = 1 + rand() % MAX;
			printf("case1 발생\n");	// 중복발생 확인용
		}

		while (a1 == a3 || a2 == a3) {
			a3 = 1 + rand() % MAX;
			printf("case2 발생\n");	// 중복발생 확인용
		}

		while (a1 == a4 || a2 == a4 || a3 == a4) {
			a4 = 1 + rand() % MAX;
			printf("case3 발생\n");	// 중복발생 확인용
		}

		while (a1 == a5 || a2 == a5 || a3 == a5 || a4 == a5) {
			a5 = 1 + rand() % MAX;
			printf("case4 발생\n");	// 중복발생 확인용
		}

		while (a1 == a6 || a2 == a6 || a3 == a6 || a4 == a6 || a5 == a6) {
			a6 = 1 + rand() % MAX;
			printf("case5 발생\n");	// 중복발생 확인용
		}

		printf("%d %d %d %d %d %d", a1, a2, a3, a4, a5, a6);
		printf("\n");
	}

	return 0;
}