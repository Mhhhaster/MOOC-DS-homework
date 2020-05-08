#include<queue>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
#define null 0
#define MAXSIZE 2002
using namespace std;
struct TreeNode {
	int Left;
	int Right;
}T1[MAXSIZE];
int BuildTree(int a[], int i, int j)
{
	int num = j - i + 1;//指示元素个数
	if (num == 1)//只传进来一个元素就返回它
		return a[i];
	int height;//指示多少行
	for (height = 0; pow(2, height) - 1 < num; height++);//num=3，height=2；num=4，height=3
	int lastnum = num - pow(2, height - 1) + 1;//记录最底下一排的个数,num=4,height=3,lastnum=1;
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
	if (mid - 1 >= i)
		T1[a[mid]].Left = BuildTree(a, i, mid - 1);
	else T1[a[mid]].Left = null;
	if (j >= mid + 1)
		T1[a[mid]].Right = BuildTree(a, mid + 1, j);
	else  T1[a[mid]].Right= null;
	return a[mid];
}
void LevelTraversals(int Root)
{
	queue<int> Q;
	int T;
	Q.push(Root);
	int tag = 0;
	while (!Q.empty())
	{
		T = Q.front();
		Q.pop();
		if (tag == 0)
		{
			printf("%d", T); tag++;
		}
		else
			printf(" %d", T);
		if(T1[T].Left!=null)Q.push(T1[T].Left);
		if(T1[T].Right!=null)Q.push(T1[T].Right);
	}
}
int main()
{
	int N;
	scanf("%d", &N);
	int* a = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 1; i <= N; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + N + 1);
	int Root = BuildTree(a, 1, N);
	LevelTraversals(Root);
	return 0;
}
