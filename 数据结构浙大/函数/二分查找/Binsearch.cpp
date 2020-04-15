#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
#define NotFound 0
typedef struct LNode *List;//List为LNode结点的指针
struct LNode {
	int Data[MAXSIZE];
	int Last; /* 保存线性表中最后一个元素的位置 */
};//LNode结构的结点包含两个信息：一个Data数组，一个Last；

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
int BinarySearch(List L, int X)//本程序X
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
		if (X > mid&&X < tail)//←这里错
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
int BinarySearch(List L, int X)//本程序√
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