#include<iostream>
#include<stdio.h>
#include<stack>
using namespace std;
typedef struct TreeNode* Tree;
int tag = 0;
struct TreeNode {
	int data;
	Tree Left;
	Tree Right;
};
int FindMin(int* a, int b, int c,int *m,int p)//返回序列最小元素的位置;
{
	for (int i = b; i <= c; i++)
		if (m[p] == a[i])
			return i;
}
Tree BuildTree(int* a, int b, int c,int *m, int p,int q)
{
	int i = FindMin(a, b, c,m,p);//在a数组中找到m数组中的第一个元素
	Tree Root = (Tree)malloc(sizeof(struct TreeNode));
	Root->data = a[i];
	int num = i - b;
	if (i - 1 >= b)
		Root->Left = BuildTree(a, b, i - 1,m,p+1,p+num);
	else
		Root->Left = NULL;
	if (c >= i + 1)
		Root->Right = BuildTree(a, i + 1, c,m,p+num+1,q);
	else
		Root->Right = NULL;
	return Root;
}
void Posttraversal(Tree Root)
{
	if (Root->Left)
		Posttraversal(Root->Left);
	if (Root->Right)
		Posttraversal(Root->Right);
	if (tag!=0)
		printf(" %d", Root->data);
	else
	{
		printf("%d", Root->data); tag++;
	}


}
void PostOrder2(Tree Root)//后序遍历非递归实现
{
	stack<Tree>S;
	Tree p =Root;
	Tree r = NULL;
	while (p || !S.empty())
	{
		if (p)
		{
			S.push(p);
			p = p->Left;
		}
		else
		{
			p =S.top();//先不出栈，满足条件再出栈访问
			if (p->Right && p->Right != r)
				p = p->Right;
			else//满足该结点没有右子树 或者 右儿子刚出栈，则出栈访问
			{
				p = S.top();
				S.pop();
				if (tag!=0)
                printf(" %d", p->data);
                else
                {
                    printf("%d", p->data); tag++;
                }
				r = p;//记录最近出栈的结点
				p = NULL;//该结点的左右子树都已出栈，所以要继续出栈，访问其父结点
			}
		}
	}
}
int main()//对于没有左子树的情况不能正确输出
{
	int N;
	int a[31];
	int c[31];
	scanf("%d", &N);
	int j = 1;
	int m = 1;
	stack<int> S;
	while (j <= N)
	{
		string b;
		cin >> b;
		if (b[1] == 'o')//Pop,则POP出栈顶元素并赋给a
		{
			a[j++] = S.top();
			S.pop();
		}
		else
		{
			int num;
			scanf("%d", &num);
			c[m++] = num;
			S.push( num);
		}
	}//得到先序遍历的数组c，中序遍历的数组a，从1到N；
	Tree Root = BuildTree(a, 1, N,c,1,N);//建树
	//Posttraversal(Root);//后序遍历
	PostOrder2(Root);
	return 0;
}
conclude：复习了栈函数的使用，没什么难点，与完全搜索二叉树类似的解法，同样也是减而治之，需要注意的是，先序遍历并不是从1~N。
改进：是否可以减少函数参数来降低运行成本呢，对于先序遍历的数组，只需要开始位置的结点序号即可。