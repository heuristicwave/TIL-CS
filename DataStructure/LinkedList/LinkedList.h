// �����ͷ� ���� ���Ḯ��Ʈ ���
#ifndef __LinkedList
#define __LinkedList

#include "Member.h"

/*--- ��� ---*/
typedef struct __node {
	Member data;			// ������
	struct __node* next;	// ���� ��忡 ���� ������
} Node;

/*--- ���� ����Ʈ ---*/
typedef struct {
	Node* head;		// �Ӹ� ��忡 ���� ������
	Node* crnt;		// ������ ��忡 ���� ������
} List;

void Initialize(List* list)	// ���Ḯ��Ʈ �ʱ�ȭ

// �Լ� compare�� x�� ���� ��� �˻�
Node* search(List* list, const Member* x, int compare(const Member* x, const Member* y))

void InsertFront(List* list, const Member* x) // �Ӹ��� ��带 ����
void InsertRear(List* list, const Member* x)	// ������ ��带 ����
void RemoveFront(List* list)	// �Ӹ� ��带 ����
void RemoveRear(List* list)	// ���� ��带 ����
void RemoveCurrent(List* list)	// ������ ��带 ����
void Clear(List* list)		// ��� ��带 ����
void PrintCurrent(const List* list)	// ������ ��带 ���
void PrintLnCurrent(const List* list)	// ������ ����� �����͸� ���
void Print(const List* list)		// ��� ����� �����͸� ����Ʈ ������� ���
void Terminate(List* list)
#endif



