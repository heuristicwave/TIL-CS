#include <stdio.h>
#include <stdlib.h>
#include "../Member.h"
#include "ArrayLinkedList.h"

// Get the index of the record to insert and return
static Index GetIndex(List* list)
{
	if (list->deleted == Null)	// If there are no records to delete
		return ++(list->max);
	else {
		Index rec = list->deleted;
		list->deleted = list->n[rec].Dnext;
		return rec;
	}
}

// 