#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "LinkedList.h"

// 노드를 동적으로 생성, NODE형 객체를 만들고 만든 객체의 포인터 반환
static Node* AllocNode(void)
{
	return calloc(1, sizeof(Node));
}

/*--- n이 가리키는 노드의 각 멤버에 값을 설정 ----*/
static void SetNode(Node* n, const Member* x, const Node* next)
{
	n->data = *x;		/* 데이터 */
	n->next = next;		/* 뒤쪽 포인터 */
}

void Initialize(List* list) //연결리스트 사용전 초기화 
{
	list->head = NULL;	// 텅빈 연결리스트
	list->crnt = NULL;
}

/*--- 함수 compare를 사용해 x를 검색합니다. ---*/
Node* search(List* list, const Member* x, int compare(const Member* x, const Member* y))
{
	Node* ptr = list->head;
	while (ptr != NULL) {
		if (compare(&ptr->data, x) == 0) {	/* 키값이 같은 경우 */
			list->crnt = ptr;
			return ptr;			/* 검색 성공 */
		}
		ptr = ptr->next;			/* 다음 노드를 선택 */
	}
	return NULL;					/* 검색 실패 */
}

void InsertFront(List* list, const Member* x) // 머리에 노드를 삽입
{
	Node* ptr = list->head;	// 삽인 전, 머리 노드에 대한 포인터를 ptr에 대입
	list->head = list->crnt = AllocNode();	// 삽입 할 노드 g를 allocNode 함수로 만들고 만든 노드G를 가리키도록 업데이트
	SetNode(list->head, x, ptr); // setnode를 호출해 값 설정. 이 때 삽입한 다음 머리 노드의 다음을 가리키는 포인터 값을 ptr(삽입전 머리노드)로 업데이트
}

/*--- 꼬리에 노드를 삽입하는 함수 ---*/
void InsertRear(List* list, const Member* x)
{
	if (list->head == NULL)		/* 비어있는 경우 */
		InsertFront(list, x);	/* Insert to Head */
	else {
		Node* ptr = list->head;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = list->crnt = AllocNode();
		SetNode(ptr->next, x, NULL);
	}
}

/*--- 머리노드를 삭제하는 함수 ---*/
void RemoveFront(List* list)
{
	if (list->head != NULL) {
		Node* ptr = list->head->next;		/* 두 번째 노드에 대한 포인터 */
		free(list->head);					/* 머리 노드를 해제 */
		list->head = list->crnt = ptr;		/* 새로운 머리 노드 */
	}
}

/*--- 꼬리 노드를 삭제하는 함수 ---*/
void RemoveRear(List* list)
{
	if (list->head != NULL) {
		if ((list->head)->next == NULL)	/* 노드가 하나만 있는 경우 */
			RemoveFront(list);			/* 머리 노드를 삭제 */
		else {
			Node* ptr = list->head;
			Node* pre = NULL;
			while (ptr->next != NULL) {
				pre = ptr;
				ptr = ptr->next;
			}

			pre->next = NULL;	/* pre는 꼬리 노드부터 두 번째 노드 */
			free(ptr);			/* ptr은 꼬리 노드 */
			list->crnt = pre;
		}
	}
}

/*--- 선택한 노드를 삭제하는 함수 ---*/
void RemoveCurrent(List* list)
{
	if (list->head != NULL) {
		if (list->crnt == list->head)	/* 머리 노드를 선택한 상태라면 */
			RemoveFront(list);			/* 머리 노드를 삭제 */
		else {
			Node* ptr = list->head;
			while (ptr->next != list->crnt)
				ptr = ptr->next;
			ptr->next = list->crnt->next;
			free(list->crnt);
			list->crnt = ptr;
		}
	}
}

/*--- 모든 노드를 삭제 ---*/
void Clear(List* list)
{
	while (list->head != NULL)		/* 텅 빌 때까지 */
		RemoveFront(list);			/* 머리 노드를 삭제 */
	list->crnt = NULL;
}

/*--- 선택한 노드의 데이터를 출력 ---*/
void PrintCurrent(const List* list)
{
	if (list->crnt == NULL)
		printf("선택한 노드가 없습니다.");
	else
		PrintMember(&list->crnt->data);
}
/*--- 선택한 노드의 데이터를 출력(줄바꿈 문자 포함) ---*/
void PrintLnCurrent(const List* list)
{
	PrintCurrent(list);
	putchar('\n');
}

/*--- 모든 노드의 데이터를 순서대로 출력하는 함수 ---*/
void Print(const List* list)
{
	if (list->head == NULL)
		puts("노드가 없습니다.");
	else {
		Node* ptr = list->head;
		puts("【 모두 보기 】");
		while (ptr != NULL) {
			PrintLnMember(&ptr->data);
			ptr = ptr->next;		/* 뒤쪽 노드 선택 */
		}
	}
}
/*--- 선형 리스트를 종료하는 함수 ---*/
void Terminate(List* list)
{
	Clear(list);		/* 모든 노드를 삭제 */
}