
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
Stack CreatStack(int M)//����ʵ�֣��ô�������ʵ�ֶ���ջ���İ���
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType*)malloc(M * sizeof(ElementType));//������������ʵĿռ�
	S->Top = -1;
	S->Maxsize = M;
	return S;//����Ҫ�з���ֵ
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
}//�����涼��ջ�Ļ���������ǧƪһ��
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
	Stack S = CreatStack(M);//����һ��M��С��ջ
	Stack Q = CreatStack(N);
	for (int i = N; i >= 1; i--)
		Push(Q, i);//��������1��N
	int a[1000];
	for (int i = 0; i < N; i++)//����N����
		scanf_s("%d", &a[i]);
	int temp;
	for (int i = 0; i < N; i++)//����N�αȽ�
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
			} while (temp != a[i]);//���Ϊ�գ�Q��Ԫ��ת��S
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
				else//�������S->Top
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


