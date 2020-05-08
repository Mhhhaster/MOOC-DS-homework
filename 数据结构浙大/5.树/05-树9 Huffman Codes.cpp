#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<string>
#include<iostream>
using namespace std;
typedef struct TreeNode* huffman;
struct TreeNode {
	int weight;
	huffman left;
	huffman right;
};
struct cmp {
	bool operator()(huffman x, huffman y)
	{
		return x->weight > y->weight;//>代表升序
	}
};
int fr[64];
char ch[64];
int WPL(huffman T,int depth)
{
	if (!T->left && !T->right)//左右皆空
		return T->weight * depth;
	else if (T->left)
	{
		if (T->right)
			return WPL(T->left, depth + 1) + WPL(T->right, depth + 1);
		else
			return WPL(T->left, depth + 1);
	}
	else
		return  WPL(T->right, depth + 1);
}
int GetMINWPL(int a[], int N)//根据输入的出现次数生成huffman树并求出最短编码
{
	priority_queue<huffman, vector<huffman>, cmp > c;//c是小顶堆
	for (int i = 0; i < N; i++)
	{
		huffman T = (huffman)malloc(sizeof(struct TreeNode));
		T->weight = a[i];
		T->left = NULL;
		T->right = NULL;
		c.push(T);
	}
	huffman T;
	for (int i = 0; i < N - 1; i++)
	{
		huffman T = (huffman)malloc(sizeof(struct TreeNode));
		T->left = c.top();
		c.pop();
		T->right = c.top();
		c.pop();
		T->weight = T->left->weight + T->right->weight;
		c.push(T);
	}
	T = c.top();
	return WPL(T, 0);
}
huffman CreatTreeNode()
{
	huffman T = (huffman)malloc(sizeof(struct TreeNode));
	T->left = NULL;
	T->right = NULL;
	T->weight = 0;//weight 0代表不是叶子节点，1代表叶子节点
	return T;
}
void Judge(int wpl,int N)
{
	int flag = 1;  //1代表Yes，0代表NO
	char name;
	int weight;
	string str;
	huffman T = CreatTreeNode();
	huffman Root = CreatTreeNode();
	for (int i = 0; i < N; i++) {//n条输入
		scanf(" %c", &name);
		cin >> str;//string类型只能用cin
		if (str.length() > N - 1)  flag=0;
		weight = fr[i];
		T = Root;//每次建树前先将指针移动到根节点上
		for (int j = 0; j<str.length(); j++) //每条输入有length个字符
		{
			if (str[j] == '0') {
				if (!T->left)  T->left = CreatTreeNode();
				T = T->left;
			}
			if (str[j] == '1') {
				if (!T->right)  T->right = CreatTreeNode();
				T = T->right;
			}
			if (T->weight)  flag = 0;  // 判断叶结点之前的结点权值是否为0，若不为0，则为非前缀码 
			if (j ==str.length()-1) {  //倒数第一个码值 说明此时应该到达叶结点位置 
				if (T->left || T->right)  flag = 0;  //不是叶节点则为前缀码
				T->weight = weight;
			}
		}
	}
	if (flag == 1 && wpl == WPL(Root, 0)) //判断带权路径长度是否相等
		printf("Yes\n"); 
	else
		printf("No\n");
}
int main()
{
	int N; int M;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf(" %c", &ch[i]);
		scanf("%d", &fr[i]);
	}
	int wpl = GetMINWPL(fr, N);//根据fr计算出最小wpl
	scanf("%d", &M);
	while (M--)//若给出的wpl大于最小wpl，那么no；且任何一个字符的编码都不能是另一个字符的编码的前缀
		Judge(wpl,N);
	return 0;
}