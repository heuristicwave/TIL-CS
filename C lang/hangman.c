#include <stdio.h>
#include <string.h>

int check(char s[], char a[], char ch);

int main(void)
{
	char solution[100] = "I am inevitable";
	char answer[100] = "_ __ __________";
	char ch;
	
	while (1) {
		printf("���ڿ��� �Է��Ͻÿ�: %s \n", answer);
		printf("���ڸ� �����Ͻÿ�: ");
		ch = getchar();
		if (check(solution, answer, ch) == 1)
			break;
		getchar();
	}

	return 0;
}

int check(char s[], char a[], char ch) {
	int i;

	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] == ch)
			a[i] = ch;
	}
	if (strcmp(s, a) == 0) return 1;
	else return 0;
}