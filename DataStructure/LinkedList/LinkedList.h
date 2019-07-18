// 포인터로 만든 연결리스트 헤더
#ifndef __LinkedList
#define __LinkedList

#include "Member.h"

/*--- 노드 ---*/
typedef struct __node {
	Member data;			// 데이터
	struct __node* next;	// 다음 노드에 대한 포인터
} Node;

/*--- 연결 리스트 ---*/
typedef struct {
	Node* head;		// 머리 노드에 대한 포인터
	Node* crnt;		// 선택한 노드에 대한 포인터
} List;

void Initialize(List* list)	// 연결리스트 초기화

// 함수 compare로 x와 같은 노드 검색
Node* search(List* list, const Member* x, int compare(const Member* x, const Member* y))

void InsertFront(List* list, const Member* x) // 머리에 노드를 삽입
void InsertRear(List* list, const Member* x)	// 꼬리에 노드를 삽입
void RemoveFront(List* list)	// 머리 노드를 삭제
void RemoveRear(List* list)	// 꼬리 노드를 삭제
void RemoveCurrent(List* list)	// 선택한 노드를 삭제
void Clear(List* list)		// 모든 노드를 삭제
void PrintCurrent(const List* list)	// 선택한 노드를 출력
void PrintLnCurrent(const List* list)	// 선택한 노드의 데이터를 출력
void Print(const List* list)		// 모든 노드의 데이터를 리스트 순서대로 출력
void Terminate(List* list)
#endif



