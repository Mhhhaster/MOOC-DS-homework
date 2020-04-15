#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
#define NotFound 0
typedef struct LNode *List;//ListΪLNode����ָ��
struct LNode {
	int Data[MAXSIZE];
	int Last; /* �������Ա������һ��Ԫ�ص�λ�� */
};//LNode�ṹ�Ľ�����������Ϣ��һ��Data���飬һ��Last��

List ReadInput(); /* ����ʵ�֣�ϸ�ڲ���Ԫ�ش��±�1��ʼ�洢 */
int BinarySearch(List L, int X)//������X
{
	int head = 1;
	int tail = L->Last;
	while(head<tail)
	{
		int mid =(tail + head) / 2;
		if (L->Data[head]==X)
			return 	head;
		if (L->Data[mid]==X)
			return mid;
		if (L->Data[tail]==X)
			return tail;
		if (X > mid&&X < tail)//�������
		{
				head = mid + 1;
				continue;
		 }
		
		if (X > head&&X < mid)
		{
				tail = mid;
				continue;
		}
	}
	return NotFound;
}
int BinarySearch(List L, int X)//�������
{
	int head = 1;
	int tail = L->Last;
	while (head <= tail)
	{
		int mid = (head + tail) / 2;
		if (L->Data[mid] == X)
			return mid;
		if (L->Data[mid] > X)
			tail = mid - 1;
		else
			head = mid + 1;
	}
	return NotFound;
}
int main()
{
	List L;
	int X;
	int P;
	L = ReadInput();
	scanf("%d", &X);
	P = BinarySearch(L, X);
	printf("%d\n", P);
	return 0;
}