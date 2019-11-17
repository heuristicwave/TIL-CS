## Chap16. 스트림과 파일 입출력

스트림이란 모든 입력과 출력을 byte의 흐름으로 생각하는 것이다.

스트림의 최대 장점은 **장치 독립성**이다.

스트림은 buffer를 사용한다.

> cpu의 속도가 입출력 장치보다 훨씬 빠르기 때문에 CPU가 입출력 장치 중간에 버퍼를 설치한다. 입력 장치는 버퍼에 데이터들을 저장하고, 버퍼에 어느 정도 데이터가 쌓이면 CPU가 한 번에 데이터를 가져간다.



![입출력함수의분류](https://image3.slideserve.com/7094046/slide5-n.jpg)



```c
#define EOF		    (-1)		    // 파일의 끝 표시
#define DIGITS		"0123456789"	// 문자 상수 정의
#define getchar()	getc(stdin)		// stdio.h에 정의
#define putchar()	putc(stdout)	// stdio.h에 정의
```

<br>

### Hands On



학점관리 DB

```c
#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

struct student {
    int number;
    char name[20];
    double gpa;
};

int main(void)
{
	struct student table[SIZE] = {
        {1, "Kim", 3.99},
        {1, "Min", 2.68},
        {1, "Lee", 4.01}
    };
    struct student s;
    FILE *fp = NULL;
    int i;
    
    // 이진 파일을 쓰기 모드로 연다.
    // wb - write binary
    // 반환값이 NULL이면 파일생성과정에서 오류 발생, stderr에 출력
    if ( (fp = fopen("stydent.dat", "wb")) == NULL)
    {
        fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
        exit(1);	// exit는 프로그램을 종료시키는데 사욧ㅇ되는 라이브러리, 오류 있을때 1반환
    }
    
    // 배열을 파일에 저장한다.
    fwrite(table, sizeof(struct student), SIZE, fp);
    fclose(fp);
    
    if  ( (fp = fopen("stydent.dat", "rb")) == NULL)
    {
        fprintf(stderr, "입력을 위한 파일을 열 수 없습니다.\n");
        exit(1);	// exit는 프로그램을 종료시키는데 사욧ㅇ되는 라이브러리, 오류 있을때 1반환
    }
    
    for(i=0; i < SIZE; i++)
    {
        // fread()를 이용하여 한번에 하나의 레코드를 읽는다.
        fread(&s, sizeof(struct student), 1, fp);
        pritnf("학번 = %d, 이름 = %s, 평점 = %f\n", s.number, s.name, s.gpa);
    }
    fclose(fp);
    
    return 0;
}
```

<br>



이미지 파일 복사하기

```c
#include <stdio.h>

int main(void)
{
	FILE *src_file, *dst_file;
	char filename[100];
	char buffer[1024];
	int r_count;

	printf("이미지 파일 이름 : ");
	scanf("%s", filename);

	src_file = fopen(filename, "rb");
	dst_file = fopen("copy.jpg", "wb");

	if (src_file == NULL || dst_file == NULL) {
		fprintf(stderr, "file open error \n");
		return 1;
	}

	// 파일의 끝에 도달할때까지 데이터를 읽는다.
	while ((r_count = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
		int w_count = fwrite(buffer, 1, r_count, dst_file);

		if (w_count < 0) {
			fprintf(stderr, "file write error \n");
			return 1;
		}
		
		if (w_count < r_count) {
			fprintf(stderr, "media write error \n");
			return 1;
		}
	}

	printf("image file cope complete \n");
	fclose(src_file);
	fclose(dst_file);

	return 0;
}
```



#### 특정 위치를 입력받아 그 위치로 파일 포인터를 이동하여 정수 읽는 프로그램

```c
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000
void init_table(int table[], int size);

int main(void)
{
	int table[SIZE];
	int n, data;
	long pos;
	FILE *fp = NULL;

	init_table(table, SIZE);

	if ( (fp = fopen("sample.dat", "wb")) == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다. \n");
		exit(1);
	}

	fwrite(table, sizeof(int), SIZE, fp);
	fclose(fp);

	// 이진 파일을 읽기모드로 연다.
	if ((fp = fopen("sample.dat", "rb")) == NULL)
	{
		fprintf(stderr, "입력을 위한 파일을 열 수 없습니다. \n");
		exit(1);
	}

	// 사용자가 선택한 위치의 정수를 파일로부터 읽는다.
	while (1)
	{
		printf("파일에서의 위치를 입력하십시오(0에서 %d, 종료 -1): ", SIZE - 1);
		scanf("%d", &n);

		if (n == -1)
			break;

		pos = (long)n * sizeof(int);
		fseek(fp, pos, SEEK_SET);
		fread(&data, sizeof(int), 1, fp);
		printf("%d 위치의 값은 %d 입니다. \n", n, data);
	}
	fclose(fp);

	return 0;
}

// 배열을 인덱스의 제곱으로 채운다.
void init_table(int table[], int size)
{
	int i;

	for (i = 0; i < size; i++)
		table[i] = i * i;
}
```

