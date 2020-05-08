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
		return x->weight > y->weight;//>��������
	}
};
int fr[64];
char ch[64];
int WPL(huffman T,int depth)
{
	if (!T->left && !T->right)//���ҽԿ�
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
int GetMINWPL(int a[], int N)//��������ĳ��ִ�������huffman���������̱���
{
	priority_queue<huffman, vector<huffman>, cmp > c;//c��С����
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
	T->weight = 0;//weight 0������Ҷ�ӽڵ㣬1����Ҷ�ӽڵ�
	return T;
}
void Judge(int wpl,int N)
{
	int flag = 1;  //1����Yes��0����NO
	char name;
	int weight;
	string str;
	huffman T = CreatTreeNode();
	huffman Root = CreatTreeNode();
	for (int i = 0; i < N; i++) {//n������
		scanf(" %c", &name);
		cin >> str;//string����ֻ����cin
		if (str.length() > N - 1)  flag=0;
		weight = fr[i];
		T = Root;//ÿ�ν���ǰ�Ƚ�ָ���ƶ������ڵ���
		for (int j = 0; j<str.length(); j++) //ÿ��������length���ַ�
		{
			if (str[j] == '0') {
				if (!T->left)  T->left = CreatTreeNode();
				T = T->left;
			}
			if (str[j] == '1') {
				if (!T->right)  T->right = CreatTreeNode();
				T = T->right;
			}
			if (T->weight)  flag = 0;  // �ж�Ҷ���֮ǰ�Ľ��Ȩֵ�Ƿ�Ϊ0������Ϊ0����Ϊ��ǰ׺�� 
			if (j ==str.length()-1) {  //������һ����ֵ ˵����ʱӦ�õ���Ҷ���λ�� 
				if (T->left || T->right)  flag = 0;  //����Ҷ�ڵ���Ϊǰ׺��
				T->weight = weight;
			}
		}
	}
	if (flag == 1 && wpl == WPL(Root, 0)) //�жϴ�Ȩ·�������Ƿ����
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
	int wpl = GetMINWPL(fr, N);//����fr�������Сwpl
	scanf("%d", &M);
	while (M--)//��������wpl������Сwpl����ôno�����κ�һ���ַ��ı��붼��������һ���ַ��ı����ǰ׺
		Judge(wpl,N);
	return 0;
}