#include <stdio.h>

double euler(int num);
double factorial(int x);

int main(void)
{
	int num;
	
	printf("어디까지 계산할까요: ");
	scanf("%d", &num);

	printf("오일러의 수는 %f입니다.\n", euler(num));

	return 0;
}

double euler(int num)
{
	int i;
	double j, k;
	k = 1;

	for (i = 1; i <= num; i++) {
		// printf("%d번째 %f\n", i, factorial(i));	// 디버깅용
		j = 1 / factorial(i);
		// printf("%d번째 까지는 %f\n", i, j);	// 디버깅용
		k = k + j;
	}

	return k;
}

double factorial(int x)
{
	// factorial(1) = 1 + 1/1;
	// factorial(2) = f(1) + 1/2;
	// factorial(3) = f(2) + 1/3*1/2;

	if (x > 0)
		return x * factorial(x - 1);
	else
		return 1;
}


