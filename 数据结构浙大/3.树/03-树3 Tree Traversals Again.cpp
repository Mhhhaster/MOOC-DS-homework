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
int FindMin(int* a, int b, int c,int *m,int p)//����������СԪ�ص�λ��;
{
	for (int i = b; i <= c; i++)
		if (m[p] == a[i])
			return i;
}
Tree BuildTree(int* a, int b, int c,int *m, int p,int q)
{
	int i = FindMin(a, b, c,m,p);//��a�������ҵ�m�����еĵ�һ��Ԫ��
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
void PostOrder2(Tree Root)//��������ǵݹ�ʵ��
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
			p =S.top();//�Ȳ���ջ�����������ٳ�ջ����
			if (p->Right && p->Right != r)
				p = p->Right;
			else//����ý��û�������� ���� �Ҷ��Ӹճ�ջ�����ջ����
			{
				p = S.top();
				S.pop();
				if (tag!=0)
                printf(" %d", p->data);
                else
                {
                    printf("%d", p->data); tag++;
                }
				r = p;//��¼�����ջ�Ľ��
				p = NULL;//�ý��������������ѳ�ջ������Ҫ������ջ�������丸���
			}
		}
	}
}
int main()//����û�������������������ȷ���
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
		if (b[1] == 'o')//Pop,��POP��ջ��Ԫ�ز�����a
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
	}//�õ��������������c���������������a����1��N��
	Tree Root = BuildTree(a, 1, N,c,1,N);//����
	//Posttraversal(Root);//�������
	PostOrder2(Root);
	return 0;
}
conclude����ϰ��ջ������ʹ�ã�ûʲô�ѵ㣬����ȫ�������������ƵĽⷨ��ͬ��Ҳ�Ǽ�����֮����Ҫע����ǣ�������������Ǵ�1~N��
�Ľ����Ƿ���Լ��ٺ����������������гɱ��أ�����������������飬ֻ��Ҫ��ʼλ�õĽ����ż��ɡ�