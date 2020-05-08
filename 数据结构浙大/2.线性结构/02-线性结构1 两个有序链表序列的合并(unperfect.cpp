#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */
List Merge(List L1, List L2)
{
	PtrToNode front,rear;
	rear = (PtrToNode)malloc(sizeof(struct Node));
	front = rear;
	L1 = L1->Next;
	L2 = L2->Next;
	while (L1&&L2)
	{
		if (L1->Data > L2->Data)
		{
			rear->Next = L2;
			rear = rear->Next;
			L2=L2->Next;
		}
		else
		{
			rear->Next = L1;
			rear = rear->Next;
			L1 = L1->Next;
		}
	}
	if (L2)rear->Next = L2;
	if (L1)rear->Next = L1;
	L2->Next = NULL;
	L1->Next = NULL;
	return front;
}
//本程序错在将L1,L2视为指针