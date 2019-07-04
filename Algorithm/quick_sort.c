#include <stdio.h>
#include <stdlib.h>
#define swap(type, x, y) do { type t = x; x = y; y = t; } while(0)

void quick (int a[], int left, int right)
{
	int left_cursor = left;
	int right_cursor = right;
	int pivot = a[(left_cursor + right_cursor) / 2];	// Select center pivot
	
	// line 12 ~ 16 Print split process
	int i;
	printf("a[%d] ~ a[%d] : {", left, right);
	for (i = left; i <right; i++)
		printf("%d ", a[i]);
	printf("%d}\n", a[right]);

	// Divide array a by pivot
	do {
		while(a[left_cursor] < pivot) left_cursor++;	// Move one space to the right after comparing with pivot
		while(a[right_cursor] > pivot) right_cursor--;  // Move one space to the left after comparing with pivot
		if(left_cursor <= right_cursor) {
			swap(int, a[left_cursor], a[right_cursor]);
			left_cursor++;
			right_cursor--;
		}
	} while(left_cursor <= right_cursor);	// After crossing cursors, complete
	
	// Recursive calls to repartition left and right groups
	if (left < right_cursor) quick(a, left, right_cursor);
	if (left_cursor < right) quick(a, left_cursor, right);	
}

int main(void){
	int i, nx;
	int *x;		// Pointer to array first element
	
	puts("Quick Sort");
	printf("요소 개수 : ");
	scanf("%d", &nx);
	
	x = calloc(nx, sizeof(int));
	
	for(i = 0; i < nx; i++) {
		printf("x[%d] : ", i);
		scanf("%d", &x[i]);
	}
	
	quick(x, 0, nx - 1);
	puts("오름차순 정렬");
	for (i = 0; i < nx; i++)
		printf("x[%d] = %d\n", i, x[i]);
	
	free(x);
	
	return 0;	
}