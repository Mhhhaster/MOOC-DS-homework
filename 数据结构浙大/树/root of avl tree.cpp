#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct AVLTree* Tree;
struct AVLTree {
	int data;
	Tree Left;
	Tree Right;
	int Height;
};
int Max(int a, int b)
{
	return a > b ? a : b;
}
int GetHeight(Tree T)
{
	if (!T)return -1;
	else return T->Height;
}
Tree DoubleLeftrotation(Tree T)
{
	Tree B = T->Left;
	T->Left = B->Right;
	B->Right = T;
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), T->Height) + 1;
	return B;
}
Tree DoubleRightrotation(Tree T)
{
	Tree B = T->Right;
	T->Right = B->Left;
	B->Left = T;
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
	B->Height = Max(GetHeight(B->Right), T->Height) + 1;
	return B;
}
Tree LeftRightrotation(Tree T)//这里需要格外注意，左右旋=对左子树右旋后返回左旋值
{
	T->Left = DoubleRightrotation(T->Left);
	return DoubleLeftrotation(T);
}
Tree RightLeftrotation(Tree T)
{
	T->Right = DoubleLeftrotation(T->Right);
	return DoubleRightrotation(T);
}
Tree NewTree(int i)//finish
{
	Tree T = (Tree)malloc(sizeof(struct AVLTree));
	T->data = i;
	T->Left = NULL;
	T->Right = NULL;
	T->Height = 0;
	return T;
}
Tree Insert(Tree T, int i)
{
	if (!T) T = NewTree(i);
	else {
		if (i > T->data)
		{
			T->Right = Insert(T->Right, i);
			if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
				if (i > T->Right->data)
					T = DoubleRightrotation(T);
				else
					T = RightLeftrotation(T);
		}
		else if(i<T->data)
		{
			T->Left = Insert(T->Left, i);
			if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
				if (i > T->Left->data)
					T = LeftRightrotation(T);
				else
					T = DoubleLeftrotation(T);
		}
	}
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
	return T;
}
Tree BuildTree(int N)//finish
{
	int a;
	scanf("%d", &a);
	Tree T = NewTree(a);
	for (int i = 1; i < N; i++)
	{
		scanf("%d", &a);
		T = Insert(T,a);
	}
	return T;
}

int main()//finish
{
	int N;
	scanf("%d", &N);
	Tree T = BuildTree(N);
	printf("%d", T->data);
	return 0;
}