#include<iostream>
#pragma warning(disable:4996)
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
void reattach(int a, int b, int c, Ptr *Rear)
{
	Ptr M, temp;
	M = (Ptr)malloc(sizeof(struct LNode));
	M->ad = a;
	M->num = b;
	M->na = c;
	M->Next = *Rear;
	temp = M;
	M = *Rear;
	*Rear = temp;
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
//题目：Reversing Linked List；
//问题：本题测试点仅剩一个当N取最大时，超时未通过。
//除输入输出外共使用三个函数，第二个函数对链表前n项翻转，第三个函数更新翻转后的下一跳地址，
//没有错误且都消耗线性时间，所以只能对这个函数进行修改，希望老师可以给出这个对函数或者整个题的建议
Ptr ReLink(Ptr a, int nexta)
{//函数通过对给出的初始下一跳地址不断查找并更新，来将所有结点按逻辑地址排序
	Ptr rear, t, front, temp;
	t = a;//原始链指针t
	rear = (Ptr)malloc(sizeof(struct LNode));
	front = rear;//申请空节点，将front和rear都指向它
	while (t)//如果t指向非空
	{
		if (t->ad == nexta)//如果当前的地址ad和给出的最初下一跳地址nexta相等
		{
			nexta = t->na;//将nexta更新为当前结点的下一跳地址
			attach(t->ad, t->num, t->na, &rear);//接在rear后面
			t = a;//指针t归位
			continue;//从头开始查找
		}
		t = t->Next;
	}
	rear->Next = NULL;//封结点尾
	temp = front;
	front = front->Next;
	free(temp);//去结点头
	return front;
}
Ptr Reverse(Ptr b, int o)
{
	Ptr front, Rear, a, temp;
	int K = o;
	a = b;
	Rear = (Ptr)malloc(sizeof(struct LNode));
	Rear->Next = NULL;
	front = Rear;
	while (K--)
	{
		reattach(a->ad, a->num, a->na, &Rear);
		a = a->Next;
	}//至此完成到k位的倒序插入
	//此时rear在头，front在尾，且front为空
	temp = front;
	front = Rear;
	free(temp);
	K = o;
	while (--K)
		Rear = Rear->Next;
	Rear->Next = NULL;
	a = b;
	K = o;
	while (K)
	{
		a = a->Next;//指针右移k次
		K--;
		if (a==NULL)//如果为空
		{
			Rear->Next = NULL;
			return front;//封尾去头，指向链表头
		}
	}
	attach(a->ad, a->num, a->na, &Rear);
	a = a->Next;
	while (a)
	{
		attach(a->ad, a->num, a->na, &Rear);
		a = a->Next;
	}
	Rear->Next = NULL;
	return front;
}

void OutPut(Ptr a)
{
	Ptr b = a;
	while (b)
	{
		if (b->ad >= 0)
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
		printf("%d %d ", b->ad, b->num);
		if (b->na >= 0)
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
		printf("%d\n", b->na);
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
	a->na = -1;
	return front;
}
int main()
{
	Ptr P, P1, P2, P3;
	int nexta, N, K;
	scanf("%d%d%d", &nexta, &N, &K);
	P = ReadInput(N);//读入数据，线性
	P1 = ReLink(P, nexta);//将数据按地址逻辑排列好，平方
	P2 = Reverse(P1, K);//翻转前k个，线性
	P3 = Link(P2);//将下一跳地址修改，线性
	OutPut(P3);//按序列格式化输出，线性
}
