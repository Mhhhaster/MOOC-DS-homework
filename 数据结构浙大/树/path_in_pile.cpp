#include<iostream>
#include<stdio.h>
#define MINDATA -10001
using namespace std;
//先建立小顶堆
typedef struct HeapNode *Heap;
struct HeapNode {
	int size;
	int* Data;
	int capacity;
};
Heap CreatHeap(int MAXSIZE)
{
	Heap H = (Heap)malloc(sizeof(struct HeapNode));
	H->Data = (int*)malloc((MAXSIZE+1) * sizeof(int));
	H->size = 0;
	H->capacity = MAXSIZE;
	H->Data[0] = MINDATA;
	return H;
}
void Insert(Heap H,int x)
{
	int i = ++H->size;
	while (x < H->Data[i / 2])
	{
		H->Data[i] = H->Data[i / 2];
		i /= 2;
	}
	H->Data[i] = x;
}
int main()
{
	int N, M;
	Heap H;
	scanf("%d%d", &N,&M);
	H = CreatHeap(N);
	for (int i = 1; i <= N; i++)
	{
		int a;
		scanf("%d", &a);
		Insert(H, a);
	}
	while (M--)
	{
		int b;
		scanf("%d", &b);
		printf("%d", H->Data[b]);//输出序号b所在数据
		for (int i = b/2; i > 0; i = i / 2)
		{
			printf(" %d", H->Data[i]);
		}
		printf("\n");
	}
	return 0;
}