/* 이진 검색 */
#include <stdio.h>
#include <stdlib.h>

// 요소의 개수가 n인 배열 a에서 key와 일치하는 요소를 이진검색
int bin_search(const int a[], int n, int key)
{
	int pl = 0;	// 검색 범위 맨 앞의 인덱스
	int pr = n - 1;	// 검색 범위 맨 끝의 인덱스
	int pc;

	do {
		pc = (pl + pr) / 2;
		if (a[pc] == key)	// 검색 성공
			return pc;
		else if (a[pc] < key)
			pl = pc + 1;
		else
			pr = pc - 1;
	} while (pl <= pr);
	return -1;
}

int main(void)
{
	int i, nx, ky, idx;
	int *x; 	// 배열의 첫 번쨰 요소에 대한 포인터
	puts("이진 검색");
	printf("요소 개수 : ");
	scanf_s("%d", &nx);

	x = calloc(nx, sizeof(int));	// 요소의 개수가 nx인 int형 배열을 생성

	printf("오름차순으로 입력하세요.\n");
	printf("x[0] : ");
	scanf_s("%d", &x[0]);
	for (i = 1; i < nx; i++) {
		do {
			printf("x[%d] : ", i);
			scanf_s("%d", &x[i]);
		} while (x[i] < x[i - 1]);	// 바로 앞의 값도다 작으면 다시 입력
	}
	printf("검색값 : ");
	scanf_s("%d", &ky);
	idx = bin_search(x, nx, ky);	// 배열 x에서 값이 ky인 요소를 이진 검색
	if (idx == -1)
		puts("검색에 실패했습니다.");
	else
		printf("%d는 x[%d]에 있습니다.\n", ky, idx);
	free(x);	// 배열 해제

	return 0;
}

/*
 검색을 반복할 때마다 검색 범위가 절반이 되므로 검색에 필요한 비교 횟수의 평균값은 log(n-1)회
 검색에 실패할 경우는 log(n+1)회, 성공한 경우는 log(n-1)회
*/