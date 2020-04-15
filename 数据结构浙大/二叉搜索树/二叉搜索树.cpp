#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct TreeNode* Tree;
struct TreeNode {
	int data;
	Tree Left, Right;
};
Tree NewTree(int i)//建立一个数据为i的节点
{
	Tree T = (Tree)malloc(sizeof(TreeNode));
	T->data = i;
	T->Left = NULL;
	T->Right = NULL;
	return T;
}
Tree Insert(Tree t, int i)//在树中新插入一个节点
{
	if (!t) t = NewTree(i);
	else {
		if (i > t->data)
			t->Right = Insert(t->Right, i);
		else
			t->Left = Insert(t->Left, i);
		//省去else，即插入数据已存在的情况
	}
	return t;
}
Tree MakeTree(int N)//根据输入的N，造一颗N结点的数
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
int IsSame(Tree T1, Tree T2)//比较两颗树是否相同
{//先比较根节点是否相等；如果有，比较左子树是不是相同，比较右子树是不是相同，都满足则输出yes；
	if (T1 == NULL && T2 == NULL)
		return 1;
	if (T1->data == T2->data)
	{//左右都为空return1
		//1左空2左不空
		//1右空2右不空return 0
		//1左空2左空，return 左左，1右空2右空return 右右；
		//都不空，return 左左右右
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
void FreeTree(Tree T)//释放一棵树
{
	if (T->Left) FreeTree(T->Left);
	if (T->Right)FreeTree(T->Right);
	free(T);
}
int main()
{
	int N, L;
	scanf("%d%d", &N, &L);
	while (N)//现在已读入N和L；先读入N个数建立一棵树，{再读入N个数，比较两者是否同构,释放}*L次；
	{

		Tree T1 = MakeTree(N);//读入前N个数建立一颗比较树
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