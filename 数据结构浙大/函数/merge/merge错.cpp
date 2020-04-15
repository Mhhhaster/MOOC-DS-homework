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
	PtrToNode front,linshi;
	if (L1->Data > L2->Data)
	{
		linshi = L1;
		L1 = L2;
		L2 = linshi;
	}//使L1为小列
	front = L1;
	while (L1->Next)
	{
		if ((L1->Data < L2->Data && (L1->Next)->Data < L2->Data) || !L2)
		{
			L1 = L1->Next; continue;
		}
		PtrToNode temp;
		temp = L2;
		temp = temp->Next;
		L2->Next = L1->Next;
		L1->Next = L2;
		L2 = temp;
		L1 = L1->Next;
	}
	L1 = L1->Next;
	return front;
}