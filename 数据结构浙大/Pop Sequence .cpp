
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define ERROR -1
typedef struct SNode *Stack;
struct SNode {
	ElementType *Data;
	int Top;
	int Maxsize;
};
Stack CreatStack(int M)//数组实现，好处：方便实现对于栈满的把握
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType*)malloc(M * sizeof(ElementType));//给数组申请合适的空间
	S->Top = -1;
	S->Maxsize = M;
	return S;//必须要有返回值
}
bool IsFull(Stack S)
{
	return(S->Top == S->Maxsize - 1);
}
bool IsEmpty(Stack S)
{
	return (S->Top == -1);
}
bool Push(Stack S, int n)
{
	if (IsFull(S))
		return false;
	else {
		(S->Top)++;
		S->Data[S->Top] = n;
		return true;
	}
}
int Pop(Stack S)
{
	if (IsEmpty(S))
		return ERROR;
	else
	{
		return S->Data[(S->Top)--];
	}
}//这上面都是栈的基本函数，千篇一律
int IsAccessible(int M, int N);
int main()
{
	int M, N, K;
	scanf_s("%d%d%d", &M, &N, &K);
	int b[1000] = { 0 };
	for (int i = 1; i <= K; i++)
		b[i] = IsAccessible(M, N);
	for (int i = 1; i <= K; i++)
	{
		if (b[i] == 1)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
int IsAccessible(int M, int N)
{
	Stack S = CreatStack(M);//创建一个M大小的栈
	Stack Q = CreatStack(N);
	for (int i = N; i >= 1; i--)
		Push(Q, i);//从上往下1至N
	int a[1000];
	for (int i = 0; i < N; i++)//输入N个数
		scanf_s("%d", &a[i]);
	int temp;
	for (int i = 0; i < N; i++)//进行N次比较
	{
		if (IsEmpty(S))
		{
			do {
				temp = Pop(Q);
				if (bool(IsFull(S)))
				{
					return 0;
				}
				Push(S, temp);
			} while (temp != a[i]);//如果为空，Q中元素转入S
			Pop(S);
		}
		else
		{
			if (a[i] == S->Data[S->Top])
				Pop(S);
			else
			{
				if (a[i] < S->Data[S->Top])
				{
					return 0;
				}
				else//输出大于S->Top
				{
					do {
						temp = Pop(Q);
						if (bool(IsFull(S)))
						{
							return 0;
						}
						Push(S, temp);
					} while (temp != a[i]);
					Pop(S);
				}
			}
		}
	}
	return 1;
}


