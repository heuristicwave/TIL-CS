#include <stdio.h>
void encrypt(char cipher[], int shift);

int main(void)
{
	char cipher[50];
	int shift = 3;

	printf("���ڿ��� �Է��Ͻÿ�: ");
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
	printf("��ȣȭ�� ���ڿ�: %s \n", cipher);
}