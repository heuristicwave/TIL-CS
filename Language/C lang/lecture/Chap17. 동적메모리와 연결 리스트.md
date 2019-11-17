## Chap17. 동적 메모리와 연결 리스트

### malloc()

바이트 단위로 메모리를 할당한다. malloc()은 <stdlib.h>에 원형이 정의되어 있다.

size는 할당받고 싶은 바이트의 수이다. size_t는 unsigned int로 정의되어 있다.

malloc()는 효율성을 위하여 동적 메모리를 초기화하지 않는다. 따라서 쓰레기 값이 들어 있다고 생각하여야 한다.

```c
void *malloc(size_t size);	// 형식
int *p;
p = (int *)malloc(500);	// int 포인터로 변환

if (p == NULL) {
    .... // 오류처리, 메모리가 부족하면 null을 반환하기 때문에 널인지 체크한다.
}

free(p);	// 동적 메모리는 반드시 사용 후에 반납되어야 한다.
```

malloc()이 반환하는 반환형은 void *이다. void 포인터를 반환하는 이유는 malloc()함수 입장에서는 프로그래머가 할당받은 메모리 블록을 어떤 자료형으로 사용하는지 알 수 없기 때문이다. 프로그래머는 void 포인터를 자신이 원하는 포인터 타입으로 바꾸어서 사용하면 된다.

<br>



#### 동적메모리 사용

포인터가 반환되므로 포인터를 이용하여서 동적 메모리를 사용해야 한다.

```c
// *사용하기
*p = 100;
*(p+1) = 200;
...
    
    
// 동적메모리를 배열과 같이 취급하여 []연산자 사용하기*p = 100;
p[0] = 100;
p[1] = 200;
...
```

<br>



구조체 동적 배열 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int number;
    char title[50];
};

int main(void)
{
	struct Book *p;
    
    p = (struct Book *)malloc(2 * sizeof(struct Book));

	if (p == NULL) {
		printf("메모리 할당 오류 \n");
		exit(1);
	}

	p[0].number = 1;
    strcpy(p[0].title, "C programming");
    p[1].number = 2;
    strcpy(p[1].title, "Data Structure");
    
    free(p);
	return 0;
}
```



### calloc()

calloc()은 0으로 초기화된 동적 메모리를 할당한다. 또 바이트 단위가 아닌 항목 단위로 메모리를 할당한다.

```c
void *calloc(size_t n, size_t size);	// param1: 항목의 개수 param2: 항목의 크기

int *p;
p = (int *p)calloc(5, sizeof(int));	// 0으로 초기화된 동적 메모리를 n*size 만큼 할당한다.
```



### realloc()

realloc()은 할당 하였던 메모리 블록의 크기를 변경한다.

```c
void *realloc(void *p, size_t size);	// param1: 기존의 동적 메모리 param2: 새로운 크기

int *p;
p = (int *p)malloc(5*sizeof(int));
realloc(p, 7*sizeof(int));
```

<br>



### 연결리스트

연결리스트의 노드는 데이터 필드와 링크 필드로 이루어진다.

데이터 필드 : 저장하고 싶은 데이터가 들어감

링크 필드 : 다른 노드를 가리키는 포인터가 저장됨.



연결리스트에서는 연결 리스트의 첫 번째 노드를 알아야 전체의 노드에 접근 할 수 있다. 따라서 연결리스트 마다 첫 번째 노드를 가리키고 있는 변수가 **헤드 포인터**라고 한다. 연결 리스트의 이름은 이 헤드 포인터의 이름과 같다. 



#### 자기 참조 구조체

구성 멤버 중에 같은 타입의 구조체를 가리키는 포인터가 존재하는 구조체

```c
struct NODE {
    int data;
    struct NODE *link;	// 현재 구조체를 가리킬 수 있는 포인터
};
```

link는 바로 지금 정의하고 있는 구조체의 NODE를 가리키는 포인터로 정의되고 있다.

일반적으로 항목의 개수를 미리 예측할 수 없는 경우에 자체 참조 구조체를 정의해 놓고 동적으로 기억 장소를 할당 받아서 이들을 포인터로 연결하여 자료 구조를 구성한다. 자기 참조 구조체를 포인터로 연결하여 자료를 저장하게 되면 중간에 새로운 자료를 삽입하기가 용이해진다.



보통 자기 참조 구조체는 typedef을 이용하여 새로운 타입으로 정의하는 것이 보통이다. typedef을 이용하게 되면 매번 struct 키워드를 써주지 않아도 된다.

```C
// typedef으로 자기 참조 구조체를 새로운 자료형 NODE로 정의한다.
typedef struct NODE {
    int data;
    struct NODE *link;
} NODE;
```



#### 연결 리스트 생성의 예

노드의 구조는 구조체를 이용하여 앞에서와 같의 정의

포인터 변수 p1을 만들고 malloc()함수를 이용하여 노드의 크기 만큼의 동적 메모리를 할당 받는다. 이 동적 메모리가 노드가 된다

```c
NODE *p1;
p1 = (NODE *)malloc(sizeof(NODE));
```



새로 만들어진 노드에 데이터를 저장하고 링크 필드를 NULL로 설정한다.

```c
p1->data = 10;
p1->link = NULL;
```



같은 방식으로 동적으로 두번째 노드를 생성하고 첫 번째 노드의 링크 필드가 두 번째 노드를 가리키도록 한다.

```c
NODE *p2;
p2 = (NODE *)malloc(sizeof(NODE));
p2->data = 20;
p2->link = NULL;
p2->link = p2;
```

사용이 끝나면 free(p1); free(p2);로 메모리를 해제 한다.



#### 리스트의 데이터 값 출력

```c
void print_list(NODE *plist)
{
    NODE *p;
    
    p = plist;
    printf("( ");
    
    while( p )	// (p!=NULL) 과 같다
    {
        printf("%d ", p->data);
        p = p->link;	// p를 연결 리스트를 따라서 앞으로 한 노드 전진
    }
    printf(")\n");
}
```



#### 노드의 개수 세기

```c
int get_length(NODE *plist)
{
    NODE *p;
    int length = 0;
    
    p = plist;
    
    while( p )	// (p!=NULL) 과 같다
    {
        length++;
        p = p->link;	// p를 연결 리스트를 따라서 앞으로 한 노드 전진
        
        // sum += p->data; p = p->link;를 하면 순회를 하며 합을 구할 수 있음
    }
    
    return length;
}
```

