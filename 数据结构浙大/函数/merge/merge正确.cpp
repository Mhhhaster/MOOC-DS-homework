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
	PtrToNode p = L1->Next;
	PtrToNode q = L2->Next;
	while (p&&q)
	{
		if (p->Data > q->Data)
		{
			rear->Next = q;
			rear = rear->Next;
			q=q->Next;
		}
		else
		{
			rear->Next = p;
			rear = rear->Next;
			p = p->Next;
		}
	}
	if (q)rear->Next = q;
	if (p)rear->Next = p;
	L2->Next = NULL;
	L1->Next = NULL;
	return front;
}