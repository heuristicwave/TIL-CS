## Chap14. 포인터 활용



### 이중 포인터란?

포인터의 포인터, 이중 포인터도 주소가 저장되므로 다른 포인터와 마찬가지로 4바이트의 메모리 공간이 필요함.

```c
int i = 100;
int *p = &i;
int **q = &p;	// q는 포인터 p를 가리키는 이중 포인터

*p = 200;		// p를 통하여 i에 200을 저장 => i = 200;
**q = 300;		// q를 통하여 i에 300을 저장 => i = 300;

/// *q = 300; 포인터 *q는 p와 같은데 포인터 p에 주소 300을 대입하는 것은 의미가 없다, 논리적 오류
```



이중 포인터가 많이 사용되는 상황은 외부에서 정의된 포인터 값을 함수의 인수로 받아 변경하려고 하는 경우다.

```c
void set_pointer(char **q);
char *proverb="This is proverb";

int main(void)
{
	char *p = "zzz";
    set_pointer(&p);
    printf("%s \n", p);
    
    return 0;    
}
// 매개변수로 이중포인터 q를 통하여 외부의 포인터 p를 변경함.
void set_pointer(char **q)
{
    *q = proverb;
}
```



구교재 p568 이후