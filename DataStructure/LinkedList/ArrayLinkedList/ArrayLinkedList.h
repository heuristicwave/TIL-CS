#ifndef ___ArrayLinkedList
#define ___ArrayLinkedList

#include "../Member.h"

#define Null -1

typedef int Index;	// typeof index

/// Node
typedef struct {
	Member data;
	Index next;
	Index Dnext;	// Next node in the Free List
} Node;

typedef struct {
	Node* n;	// list body(array)
	Index head;	// head node
	Index max;	// Using tail record
	Index deleted; // head node of free list
	Index crnt;	// selected node
} List;

// init linked_list
void Initialize(List* list, int size);

// find a node like x with function compare
Index search(List* list, const Member* x, int compare(const Member* x, const Member* y));

// insert node in head
void InsertFront(List* list, const Member* x);

// insert node in tail
void InsertRear(List* list, const Member* x);

// remove node in head
void RemoveFront(List* list);

// remove node in tail
void RemoveRear(List* list);

// remove node in selected
void RemoveRear(List* list);

// remove all node
void Clear(List* list);

// print selected node data
void PrintCurrent(const List* list);

// print selected node data with newline
void PrintLnCurrent(const List* list);

// print all node data
void Print(const List* list);

// terminate linked_list
void Terminate(List* list);
#endif
