#include <stdio.h>
#include "wbaes.h"

void printArr(char Arr[]) {
	for (int i = 0; i < 16; i++) {
		printf("%c ", Arr[i]);
	}
}

int main() {		
	unsigned char result_from_xor[16] = { 0, };
	unsigned char reverse_from_sbox[16] = { 0, };
	int row, column;

	printf("Using XOR operation with 0 : ");

	/* T-box 
	first param : round
	second param : hex number
	third param : XOR with zero
	*/
	for (int i = 0; i < 16; i++) {		
		result_from_xor[i] = tbox[0][i][0];
		printf("%2x ", result_from_xor[i]);
	}
	puts("\n");

	// Reverse from S-box, Convert hex to char
	for (int i = 0; i < 16; i++) {
		for (int row = 0; row < 16; row++) {
			for (int column = 0; column < 16; column++) {
				if (result_from_xor[i] == sbox[row][column]) {
					reverse_from_sbox[i] = row*16 + column;		// row X 16 + column X 1
				}
			}
		}
	}
		
	printf("Before : ");
	printArr(reverse_from_sbox);
	
	printf("\n=============== Inverse Metrix ================\n");
	// Mixcolums(In AES) can be computed vir four table look-ups and three XOR.
	// Thus, the initial value can be obtained by XORing the last table(reverse_from_sbox) 3 times. 
	sr(reverse_from_sbox); sr(reverse_from_sbox); sr(reverse_from_sbox);

	printf("Anser is : ");
	printArr(reverse_from_sbox);

	return 0;
}