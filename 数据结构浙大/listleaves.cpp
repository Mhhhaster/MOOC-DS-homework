#include<iostream>
#define MAXSIZE 10
#include<stdio.h>
#pragma warning(disable:4996)
#define Tree int
#define Null -1
using namespace std;
struct TNode {
	Tree Left;
	Tree Right;
}T1[MAXSIZE];//T1ȫ�ֱ���

typedef struct Node *PtrToNode;
struct Node {
	int Data;
	PtrToNode Next;
}typedef PtrToNode Position;
struct QNode {
	Position Front, Rear;
}typedef struct QNode *Queue;//�����ṹ�弰ָ��

bool IsEmpty(Queue Q)//����λ��ָ��Q
{
	return (Q->Front == NULL);//��ͷָ���Ƿ��ָ�������ָ��˵����deleteɾ���ˣ����⣬���ܶ�û��ɾ�ӹ�Ԫ�ص�ʹ��
}
void AddQ(Queue Q, int X)//�ڶ�β���һ�ڵ�
{//����һ��ָ�룬��ָ��ָ��սڵ㣬���սڵ㸳ֵ�����ڶ�β����βָ�����
	PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));
	TmpCell->Data = X;
	TmpCell->Next = NULL;
	Q->Rear->Next = TmpCell;
	Q->Rear = Q->Rear->Next;
}
int DeleteQ(Queue Q)//ɾ����ͷ����������Ԫ��
{
	Position FrontCell;
	int FrontElem;
	FrontCell = Q->Front;
	if (Q->Front == Q->Rear)
		Q->Front = Q->Rear = NULL;//��ӦIsEmpty
	else
		Q->Front = Q->Front->Next;
	FrontElem = FrontCell->Data;
	free(FrontCell);
	return FrontElem;
}
Queue CreatQueue()//�����ն���,��ͷָ��Ͷ�βָ��ָ��սڵ�
{
	Queue Q = malloc(sizeof(struct QNode));//��ʽ��ָ��=�ṹ������
	PtrToNode temp = malloc(sizeof(struct Node));
	temp->Next = NULL;
	Q->Rear = Q->Front = temp;
	return Q;
}
Tree BuildTree(struct TNode T[])
{
	int N, Root = Null;
	int tag[MAXSIZE] = { 0 };
	char cl, cr;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		cin >> cl >> cr;
		if (cl != '-')
		{
			T[i].Left = cl - '0'; tag[cl - '0'] = 1;
		}
		else
			T[i].Left = Null;
		if (cr != '-')
		{
			T[i].Right = cr - '0'; tag[cr - '0'] = 1;
		}
		else
			T[i].Right = Null;
	}
	for (int i = 0; i < N; i++)
	{
		if (tag[i] == 0)
			Root = i;
	}
	return Root;
}
void PreorderTraveral(Tree R)
{
	//ȡ��Root����ȡֵ���ж�
	if (R != Null)
	{
		printf("%d ", R);
		ListleavesTraversal(T1[R].Left);
		ListleavesTraversal(T1[R].Right);
	}
}
void ListleavesTraversal(Tree R)
{//���б����R�����ڵ�ֵ���Ƿ�ΪNull,���򷵻����޷���ֵ
	//AddQ R���б�����Ƿ�Ϊ�գ��ǿ�ȡ��һ��Ԫ�أ��б�ǰR�����������Ƿ�ΪNull;
	Queue Q = CreatQueue();
	int t;
	if (R == Null)return;
	AddQ(Q, R);
	while (!IsEmpty(Q))
	{
		t = DeleteQ(Q);
		printf("%d", t);
		if (T1[t].Left != Null) AddQ(Q, T1[t].Left);//����������ǿգ�����������
		if (T1[t].Right != Null) AddQ(Q, T1[t].Right);//����������ǿգ��������������ձ�־ΪNull,��-1��
	}
}
int main()
{
	Tree R1;
	R1 = BuildTree(T1);//��R1=BuildTree(T1[]);
	ListleavesTraversal(R1);
	return 0;
}