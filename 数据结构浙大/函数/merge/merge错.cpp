#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* ϸ���ڴ˲��� */
void Print(List L); /* ϸ���ڴ˲������������NULL */
List Merge(List L1, List L2)
{
	PtrToNode front,linshi;
	if (L1->Data > L2->Data)
	{
		linshi = L1;
		L1 = L2;
		L2 = linshi;
	}//ʹL1ΪС��
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