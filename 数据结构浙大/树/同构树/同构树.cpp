#define MAXSIZE 10
#define Tree int
#include<iostream>
#pragma warning(disable:4996)
#define Null -1
#define ElementType char
#include <stdio.h>
using namespace std;
struct TreeNode {
	ElementType name;
	Tree left;
	Tree right;
}T1[MAXSIZE], T2[MAXSIZE];
Tree BuildTree(struct TreeNode T[])//ע������Ĳ������ͣ�ҪΪT1��T1����Ϊstruct treenode�����������������޷��ֱ�T1,T2
{
	int  Root=Null, N;
	char l, r;
	scanf("%d", &N); int tag[MAXSIZE] = { 0 };
	if (N)
	{

		for (int i = 0; i < N; i++)
		{
			cin>> T[i].name>> l>> r;
			if (l != '-')
			{
				T[i].left = l - '0'; tag[l - '0'] = 1;
			}
			else
				T[i].left = Null;
			if (r != '-')
			{
				T[i].right = r - '0'; tag[r - '0'] = 1;
			}
			else
				T[i].right = Null;
		}
	}
	for (int i = 0; i < N; i++)
	{
		if (tag[i] == 0)
			Root = i;
	}
	return Root;
}
//int Isomorphic(struct TreeNode T1[R1],struct TreeNode T2[R2])
int Isomorphic(Tree R1, Tree R2)//��ΪT1,T2Ϊȫ�ֱ��������Բ��ô��룬�ں����ڲ�ֱ���þ���
{
	if (R1 == Null && R2 == Null) return 1;                                     //case 1 ������
	if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null)) return 0;   //case 2 ��1��
	if ((R1 != Null && R2 != Null) && (T1[R1].name != T2[R2].name)) return 0;    //case 3 �������գ�rootֵname�����
	if ((R1 != Null && R2 != Null) && (T1[R1].name == T2[R2].name))//case 4 rootֵ���{������Ҳ���ȣ�����һ�Σ����name��=����=�ң�return isomorphic��Tree T1[R1].left��Tree T2[R2].left)+isomorphic��Tree T1[R1].right��Tree T2[R2].right)else return 0��
	{
		if ((T1[R1].left == Null) && (T2[R2].left == Null) && (T2[R2].right == Null) && (T1[R1].right == Null))
			return 1;
		if ((T1[R1].left == Null) && (T2[R2].left == Null) && (T2[R2].right != Null) && (T1[R1].right != Null))//T1T2��
			return Isomorphic(T1[R1].right, T2[R2].right);
		if ((T1[R1].left == Null) && (T2[R2].left != Null) && (T1[R1].right != Null) && (T2[R2].right == Null))//T1��T2��
			return Isomorphic(T1[R1].right, T2[R2].left);
		if ((T1[R1].left != Null) && (T2[R2].left != Null) && (T1[R1].right == Null) && (T2[R2].right == Null))//T1��T2��
			return Isomorphic(T1[R1].left, T2[R2].left);
		if ((T1[R1].left != Null) && (T2[R2].left == Null) && (T1[R1].right == Null) && (T2[R2].right != Null))//T1��T2��
			return Isomorphic(T1[R1].left, T2[R2].right);
		if ((T1[R1].left != Null) && (T2[R2].left != Null) && (T2[R2].right != Null) && (T1[R1].right != Null))//T1,T2��Ϊ��
		{//����������name��ͬ���Һ��ҽ��name��ͬ��return iso/2���������ҽ��name��ͬ��return iso/2
			if (T1[T1[R1].left].name == T2[T2[R2].left].name&& T1[T1[R1].right].name == T2[T2[R2].right].name)
				return (Isomorphic(T1[R1].left, T2[R2].left) + Isomorphic(T1[R1].right, T2[R2].right)) / 2;
			if (T1[T1[R1].left].name == T2[T2[R2].right].name&& T1[T1[R1].right].name == T2[T2[R2].left].name)
				return(Isomorphic(T1[R1].left, T2[R2].right) + Isomorphic(T1[R1].right, T2[R2].left)) / 2;
			else return 0;
		}
	}
}
int main()
{
	Tree R1, R2;
	R1 = BuildTree(T1);//����ΪT1[]
	R2 = BuildTree(T2);
	if (Isomorphic(R1, R2)) printf("Yes\n");
	else printf("No\n");
	return 0;
}