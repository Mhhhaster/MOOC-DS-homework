#include<queue>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
using namespace std;
typedef struct TreeNode* Tree;
struct TreeNode {
	int data;
	Tree Left;
	Tree Right;
};
Tree BuildTree(int a[], int i, int j)//j>=i
{
	Tree Root = (Tree)malloc(sizeof(struct TreeNode));
	int num = j - i + 1;//ָʾԪ�ظ���
	if (num == 1)//ֻ������һ��Ԫ�ؾͷ�����
	{
		Root->data = a[i];
		Root->Left = NULL;
		Root->Right = NULL;
		return Root;
	}
	int height;//ָʾ������
	for (height = 0; pow(2, height) - 1 < num; height++);//num=3��height=2��num=4��height=3
	int lastnum = num - pow(2, height - 1) + 1;//��¼�����һ�ŵĸ���,num=4,height=3,lastnum=1;
	int rightnum, leftnum;
	if (lastnum > pow(2, height - 2))
	{
		rightnum = lastnum - pow(2, height - 2);
		leftnum = lastnum - rightnum;
	}
	else {
		rightnum = 0;
		leftnum = lastnum;
	}
	int dif = leftnum - rightnum;
	int mid = (i + j + dif) / 2;
	Root->data = a[mid];
	if (mid - 1 >= i)
		Root->Left = BuildTree(a, i, mid - 1);
	else Root->Left = NULL;
	if (j >= mid + 1)
		Root->Right = BuildTree(a, mid + 1, j);
	else  Root->Right = NULL;
	return Root;
}
void levertraversals(Tree Root)
{
	if (!Root)return;
	Tree T;
	queue<Tree> Q;//ע��Q����Ϊָ��
	Q.push( Root);
	int tag = 0;
	while (!Q.empty())
	{
		T = Q.front();
		Q.pop();
		if (tag == 0) { printf("%d", T->data); tag++; }
		else printf(" %d", T->data);
		if (T->Left) Q.push( T->Left);
		if (T->Right)Q.push( T->Right);
	}
}
int main()
{
	int N;
	scanf("%d", &N);
	int* a = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 1; i <= N; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + N + 1);//���±�1��N����,��������һ������������뵽��ȫ��������
	Tree Root = BuildTree(a, 1, N);
	levertraversals(Root);
	return 0;
}
conclude������ʹ��һ��sort�������Լ�pow��������ϰ�˶��е��÷�����ʵ֤���������������ڶ��еȽṹ�����ʹ����int��������ͬ�����ĺ������õķ���Ϊ������֮����������֮����ʵ������ѧ������ʹ�á�
��ʾ��������ȫ�����������Բ������鷽���洢�����Լ����Ľ����Ӷ��򻯶��нṹ��
���⣬���ⲻ����ʹ��insert��������ȫ�����������ͶѶ���Ψһ�ġ������������ǡ�