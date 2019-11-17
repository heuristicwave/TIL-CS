#include <stdio.h>

int main(void)
{
	int a[3][2] = { 2,4,6,8,10,12 };

	printf("a[0]의 크기는 : %d \n", sizeof(a[0]));		// 8
	
	printf("a[0] : %d \n", *a[0]);					// 2
	printf("a[0][0] : %d \n", a[0][0]);				// 2
	printf("a[0][0] : %d \n", *(*a));				// 2
	printf("a[0][1] : %d \n", *(*a+1));				// 4
	printf("a[1][0] : %d \n", *(*a+2));				// 6
	printf("%d \n", *(*a+3));	// a[1][1]			// 8
	printf("%d \n", *(*a + 5));						// 12
	printf("================================\n");
	printf("a[0][0] : %d \n", *(*(a)));				// 2
	printf("a[1][0] : %d \n", *(*(a+1)));			// 6
	printf("a[2][0] : %d \n", *(*(a+2)));			// 10
	printf("a[2][1] : %d \n", *(*(a + 2)+1));		// 12
	
	return 0;
}