#include <stdio.h>
void encrypt(char cipher[], int shift);

int main(void)
{
	char cipher[50];
	int shift = 3;

	printf("문자열을 입력하시오: ");
	gets(cipher, 50);
	encrypt(cipher, shift);

	return 0;
}

void encrypt(char cipher[], int shift) {
	int i = 0;

	while (cipher[i] != '\0') {
		if (cipher[i] >= 'A' && cipher[i] <= 'z') {
			cipher[i] += shift;
			if (cipher[i] > 'z')
				cipher[i] -= 26;
		}
		i++;
	}
	printf("암호화된 문자열: %s \n", cipher);
}