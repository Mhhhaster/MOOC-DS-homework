#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct TreeNode* Tree;
struct TreeNode {
	int data;
	Tree Left, Right;
};
Tree NewTree(int i)//����һ������Ϊi�Ľڵ�
{
	Tree T = (Tree)malloc(sizeof(TreeNode));
	T->data = i;
	T->Left = NULL;
	T->Right = NULL;
	return T;
}
Tree Insert(Tree t, int i)//�������²���һ���ڵ�
{
	if (!t) t = NewTree(i);
	else {
		if (i > t->data)
			t->Right = Insert(t->Right, i);
		else
			t->Left = Insert(t->Left, i);
		//ʡȥelse�������������Ѵ��ڵ����
	}
	return t;
}
Tree MakeTree(int N)//���������N����һ��N������
{
	int a;
	scanf("%d", &a);
	Tree T = NewTree(a);
	for (int i = 1; i < N; i++)
	{
		scanf("%d", &a);
		T = Insert(T, a);
	}
	return T;
}
int IsSame(Tree T1, Tree T2)//�Ƚ��������Ƿ���ͬ
{//�ȱȽϸ��ڵ��Ƿ���ȣ�����У��Ƚ��������ǲ�����ͬ���Ƚ��������ǲ�����ͬ�������������yes��
	if (T1 == NULL && T2 == NULL)
		return 1;
	if (T1->data == T2->data)
	{//���Ҷ�Ϊ��return1
		//1���2�󲻿�
		//1�ҿ�2�Ҳ���return 0
		//1���2��գ�return ����1�ҿ�2�ҿ�return ���ң�
		//�����գ�return ��������
		if (T1->Left == NULL && T1->Right == NULL && T2->Left == NULL && T2->Right == NULL)
			return 1;
		if (T1->Left == NULL && T2->Left != NULL)
			return 0;
		if (T1->Right == NULL && T2->Right != NULL)
			return 0;
		if (T1->Left == NULL && T2->Left == NULL)
			return IsSame(T1->Right, T2->Right);
		if (T1->Right == NULL && T2->Right == NULL)
			return IsSame(T1->Left, T2->Left);
		if (T1->Left != NULL && T1->Right != NULL && T2->Left != NULL && T2->Right != NULL)
			return (IsSame(T1->Left, T2->Left) + IsSame(T1->Right, T2->Right)) / 2;
	}
	return 0;
}
void FreeTree(Tree T)//�ͷ�һ����
{
	if (T->Left) FreeTree(T->Left);
	if (T->Right)FreeTree(T->Right);
	free(T);
}
int main()
{
	int N, L;
	scanf("%d%d", &N, &L);
	while (N)//�����Ѷ���N��L���ȶ���N��������һ������{�ٶ���N�������Ƚ������Ƿ�ͬ��,�ͷ�}*L�Σ�
	{

		Tree T1 = MakeTree(N);//����ǰN��������һ�űȽ���
		for (int i = 0; i < L; i++)
		{
			Tree tempTree = MakeTree(N);
			if (IsSame(T1, tempTree))
				printf("Yes\n");
			else
				printf("No\n");
			free(tempTree);
		}
		free(T1);
		scanf("%d", &N);
		if (N)
			scanf("%d", &L);
	}
	return 0;
}