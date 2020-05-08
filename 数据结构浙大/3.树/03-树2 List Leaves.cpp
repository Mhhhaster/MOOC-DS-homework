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
}T1[MAXSIZE];//T1全局变量

typedef struct Node *PtrToNode;
struct Node {
	int Data;
	PtrToNode Next;
}typedef PtrToNode Position;
struct QNode {
	Position Front, Rear;
}typedef struct QNode *Queue;//两个结构体及指针

bool IsEmpty(Queue Q)//传入位置指针Q
{
	return (Q->Front == NULL);//队头指针是否空指，如果空指，说明被delete删完了；另外，不能对没有删加过元素的使用
}
void AddQ(Queue Q, int X)//在队尾后加一节点
{//申请一个指针，给指针指向空节点，给空节点赋值，插在队尾，队尾指针后移
	PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));
	TmpCell->Data = X;
	TmpCell->Next = NULL;
	Q->Rear->Next = TmpCell;
	Q->Rear = Q->Rear->Next;
}
int DeleteQ(Queue Q)//删除队头，并返回其元素
{
	Position FrontCell;
	int FrontElem;
	FrontCell = Q->Front;
	if (Q->Front == Q->Rear)
		Q->Front = Q->Rear = NULL;//照应IsEmpty
	else
		Q->Front = Q->Front->Next;
	FrontElem = FrontCell->Data;
	free(FrontCell);
	return FrontElem;
}
Queue CreatQueue()//创建空队列,队头指针和队尾指针指向空节点
{
	Queue Q = malloc(sizeof(struct QNode));//格式：指针=结构体类型
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
	//取出Root，读取值并判断
	if (R != Null)
	{
		printf("%d ", R);
		ListleavesTraversal(T1[R].Left);
		ListleavesTraversal(T1[R].Right);
	}
}
void ListleavesTraversal(Tree R)
{//先判别传入的R（根节点值）是否为Null,是则返回且无返回值
	//AddQ R，判别队列是否为空，非空取出一个元素，判别当前R的左右子树是否为Null;
	Queue Q = CreatQueue();
	int t;
	if (R == Null)return;
	AddQ(Q, R);
	while (!IsEmpty(Q))
	{
		t = DeleteQ(Q);
		printf("%d", t);
		if (T1[t].Left != Null) AddQ(Q, T1[t].Left);//如果左子树非空，放入左子树
		if (T1[t].Right != Null) AddQ(Q, T1[t].Right);//如果右子树非空，放入右子树，空标志为Null,即-1；
	}
}
int main()
{
	Tree R1;
	R1 = BuildTree(T1);//非R1=BuildTree(T1[]);
	ListleavesTraversal(R1);
	return 0;
}