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
	int num = j - i + 1;//指示元素个数
	if (num == 1)//只传进来一个元素就返回它
	{
		Root->data = a[i];
		Root->Left = NULL;
		Root->Right = NULL;
		return Root;
	}
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
	queue<Tree> Q;//注意Q类型为指针
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
	sort(a + 1, a + N + 1);//对下标1到N排序,接下来将一个有序数组插入到完全二叉树里
	Tree Root = BuildTree(a, 1, N);
	levertraversals(Root);
	return 0;
}
conclude：本题使用一次sort函数，以及pow函数，复习了队列的用法，事实证明抽象数据类型在队列等结构体里的使用与int等类型相同。核心函数采用的方法为减而治之。真正巧妙之处其实在于数学方法的使用。
启示：对于完全二叉树，可以采用数组方法存储，可以继续改进，从而简化队列结构。
此外，本题不方便使用insert操作，完全搜索二叉树和堆都是唯一的。霍夫曼树不是。