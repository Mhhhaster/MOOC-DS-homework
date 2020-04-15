#include<iostream>
using namespace std;
typedef struct LNode *Ptr;
struct LNode {
	int ad;//必须由指针读取
	int num;
	int na;
	Ptr Next;
};
void attach(int a, int b, int c, Ptr *Rear)//建立一个空节点指针P，赋值，连接到最后，将指针指向它，将指针修改为P
{
	Ptr M;
	M = (Ptr)malloc(sizeof(struct LNode));
	M->ad = a;
	M->num = b;
	M->na = c;
	M->Next = NULL;
	(*Rear)->Next = M;
	*Rear = M;
}
void reattach(int a,int b,int c,Ptr *Rear)
{
	Ptr M,temp;
	M=(Ptr)malloc(sizeof(struct LNode));
	M->ad = a;
	M->num = b;
	M->na = c;
	M->Next=*Rear;
	temp=M;
	M=*Rear;
	*Rear=temp;
}
Ptr ReadInput(int N)
{
	int  n, a, number;
	Ptr front, rear, temp;
	rear = (Ptr)malloc(sizeof(struct LNode));
	front = rear;
	while (N--)
	{
		scanf("%d%d%d", &a, &number, &n);
		attach(a, number, n, &rear);
	}
	temp = front;
	front = front->Next;
	free(temp);
	return front;
}

Ptr ReLink(Ptr a,int nexta)
{
	Ptr P,t,front,temp;
	t = a;
	P = (Ptr)malloc(sizeof(struct LNode));
	front = P;
	while (t)
	{
		if (t->ad == nexta)
		{
			nexta = t->na;
			attach(t->ad, t->num, t->na, &P);
			t = a;
			continue;
		}
		t = t->Next;
	}
	P->Next = NULL;
	temp = front;
	front = front->Next;
	free(temp);
	return front;
}
Ptr Reverse(Ptr b,int o)
{
	Ptr front, Rear, a,temp;
	int K = o;
	a = b;
	int tag = 1;
	Rear = (Ptr)malloc(sizeof(struct LNode));
	Rear->Next=NULL;
	front = Rear;
	while (K--)
	{
		reattach(a->ad, a->num, a->na, &Rear);
		a=a->Next;
	}//至此完成到k位的倒序插入
	//此时Rear和front位置相反
	Ptr linshi=Rear;
	Rear=front;
	front=linshi;
    Rear->Next=NULL;
	K = o;
		while (K)
		{
			a = a->Next;//指针右移k次
			K--;
			if (!a)//如果为空
			{
				Rear->Next = NULL;
				temp = front;
				front = front->Next;
				free(temp);
				return front;//封尾去头，指向链表头
			}
		}
		attach(a->ad, a->num, a->na, &Rear);
		a = a->Next;
		while(a)
		{
			attach(a->ad, a->num, a->na, &Rear);
			a = a->Next;
	}
	Rear->Next = NULL;
	temp = front;
	front = front->Next;
	free(temp);
	return front;
}

void OutPut(Ptr a)
{
	Ptr b = a;
	while (b)
	{
		if (b->ad>=0)
		{
			if (b->ad < 10)
				printf("0");
			if (b->ad < 100)
			printf("0");
			if (b->ad < 1000)
				printf("0");
			if (b->ad < 10000)
			printf("0");
		}
		printf("%d %d ", b->ad,b->num);
		if (b->na>=0)
		{
			if (b->na < 10)
				printf("0");
			if (b->na < 100)
			printf("0");
			if (b->na < 1000)
				printf("0");
			if (b->na < 10000)
				printf("0");
		}
		printf("%d\n",b->na);
		b = b->Next;
	}
}
Ptr Link(Ptr a)
{
	Ptr front = a;
	while (a->Next)
	{
		a->na = (a->Next)->ad;
		a = a->Next;
	}
	return front;
}
int main()
{
	Ptr P, P1,P2,P3;
	int nexta, N, K;
	scanf("%d%d%d", &nexta, &N, &K);
	P = ReadInput(N);
	P1 = ReLink(P,nexta);
	P2 = Reverse(P1,K);
	P3 = Link(P2);
	OutPut(P3);
}
