#include<iostream>
using namespace std;
typedef struct LNode *PtrToLNode;
struct LNode {
	int coef;//必须由指针读取
	int expon;//ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;//Postion和List都是这种类型的指针

/* 查找 *///线性表4p 4:50
#define ERROR NULL
Position Find(List L, int a, int b)
{
	Position p = L; /* p指向L的第1个结点 *///L是指针，将指针地址给到p
	while (p && (p->coef != a || p->expon != b))
		p = p->Next;
	/* 下列语句可以用 return p; 替换 */
	return p;//if (p)		return p;	else		return ERROR;
}

/* 带头结点的插入 */
/*注意:在插入位置参数P上与课程视频有所不同，课程视频中i是序列位序（从1开始），这里P是链表结点指针，在P之前插入新结点 */
bool Insert(List L, int a, int b, Position P)
{ /* 这里默认L有头结点 */
	Position tmp, pre;//pre和tmp类型为位置指针

	/* 查找P的前一个结点 */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);//pre从头开始扫描直到指向P或者为NULL
	if (pre == NULL) { /* P所指的结点不在L中 */
		printf("插入位置参数错误\n");
		return false;
	}
	else { /* 找到了P的前一个结点pre */
		/* 在P前插入新结点 *///此时pre指向P
		tmp = (Position)malloc(sizeof(struct LNode)); /* 申请、填装结点 */
		tmp->coef = a;
		tmp->expon = b;//给节点填充内容
		tmp->Next = P;//tmp指向P
		pre->Next = tmp;//pre指向tmp，pre和P中间插入tmp
		return true;
	}
}

/* 带头结点的删除 */
/*注意:在删除位置参数P上与课程视频有所不同，课程视频中i是序列位序（从1开始），这里P是拟删除结点指针 */
bool Delete(List L, Position P)
{ /* 这里默认L有头结点 */
	Position  pre;

	/* 查找P的前一个结点 */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);
	if (pre == NULL || P == NULL) { /* P所指的结点不在L中 */
		printf("删除位置参数错误\n");
		return false;
	}
	else { /* 找到了P的前一个结点pre */
		/* 将P位置的结点删除 */
		pre->Next = P->Next;//将pre的指向p的下一个，跳过p
		free(P);//释放p
		return true;
	}
}
int Compare(int a, int b)
{
	if (a > b)
		return 1;
	if (a < b)
		return -1;
	if (a == b)
		return 0;
}
//指针需要变化，所以加上&取地址
void Attach(int a, int b, PtrToLNode *pRear)//建立一个空节点指针P，赋值，连接到最后，将指针指向它，将指针修改为P
{//作用，如果把a，b内容作为结点接在指针最后(Rear),指针移位
	PtrToLNode P;
	P = (PtrToLNode)malloc(sizeof(struct LNode));
	P->coef = a;
	P->expon = b;
	P->Next = NULL;
	(*pRear)->Next = P;
	*pRear = P;
}
/*加法*/
PtrToLNode  Add(PtrToLNode P1, PtrToLNode P2)//P1,P2位于两个链头
{//两条链都从左至右，不断比较，谁大就入新链
	PtrToLNode front, rear, temp;//临时定义三个指针
	int sum;
	rear = (PtrToLNode)malloc(sizeof(struct LNode));
	front = rear;//front与rear同指
	while (P1&&P2)//两个指针都有所指
		switch (Compare(P1->expon, P2->expon))
		{
		case 1://P1所指大于P2
			Attach(P1->coef, P1->expon, &rear);//函数作用将内容接在rear指针后面 
			P1 = P1->Next;//P1后移
			break;
		case -1:
			Attach(P2->coef, P2->expon, &rear);
			P2 = P2->Next;
			break;
		case 0://两者相等，系数相加
			sum = P1->coef + P2->coef;
			if (sum)Attach(sum, P1->expon, &rear);//如果等于零就略过attach
			P1 = P1->Next;
			P2 = P2->Next;
			break;
		}//循环退出条件为一个指针到头
	for (; P1; P1 = P1->Next)Attach(P1->coef, P1->expon, &rear);
	for (; P2; P2 = P2->Next)Attach(P2->coef, P2->expon, &rear);
	rear->Next = NULL;//，此时rear在表的最末尾，将rear指向空
	temp = front;//临时储存用指针
	front = front->Next;//front指针后移
	free(temp);//释放空间
	return front;//回到表头
}

/*乘法*/
PtrToLNode  Multiple(PtrToLNode P1, PtrToLNode P2)
{//先得到P1第一项乘P2的链，P1指针后移，新得到的链不断与第一条链相加
	PtrToLNode front, rear, temp;//临时定义指针
	rear = (PtrToLNode)malloc(sizeof(struct LNode));
	front = rear;
	PtrToLNode t1 = P1;
	PtrToLNode t2 = P2;
	if (t1)
	{
		while (t2)
		{
			Attach(t1->coef*t2->coef, t1->expon + t2->expon, &rear);
			t2 = t2->Next;//至此，形成一个front为头rear为尾的链,结果是一项乘多项
		}
		temp = front;
		front = front->Next;
		free(temp);//将front指针后移
		t2 = P2;//将第二项多项式的指针归位；
	//得到一个front为头，rear为结果的初项和，下一步目标是将t1指针后移，重复相加
	}
	t1 = t1->Next;
	while (t1)
	{
		PtrToLNode Lrear, Lfront, Ltemp;//每次循环新建一个序列
		Lrear = (PtrToLNode)malloc(sizeof(struct LNode));
		Lfront = Lrear;
		while (t2)
		{
			Attach(t1->coef*t2->coef, t1->expon + t2->expon, &Lrear);
			t2 = t2->Next;
		}//至此，形成一个Lfront为头Lrear为尾的链
		Ltemp = Lfront;
		Lfront = Lfront->Next;
		free(Ltemp);//将Lfront指针后移
		t2 = P2;//将第二项多项式的指针归位；
		front = Add(front, Lfront); //将第一次得到的多项式与这次得到的多项式相加,
		free(Lfront); free(Lrear);//释放掉临时多项式
		t1 = t1->Next;//第一个多项式从第二个结点开始
	}
	return front;//返回最终结果链的头结点
}

//读入多项式
PtrToLNode Read()
{
	int a, b, N;
	PtrToLNode P, Rear, t;
	scanf("%d", &N);//
	P = (PtrToLNode)malloc(sizeof(struct LNode));
	P->Next = NULL;
	Rear = P;//P和Rear指向一个无所指的结点，这个结点接在rear后
	while (N--)
	{
		scanf("%d %d", &a, &b);
		Attach(a, b, &Rear);
	}//包含数据的结点一个个接在Rear指针后面
	t = P; P = P->Next; free(t);//t指向空节点，p后移，删除t
	return P;
}
//输出多项式
void Print(PtrToLNode P)
{
	int tag = 0;
	if (!P)
		printf("0 0");
	while (P != 0)
	{
		if (!tag)
		{
			tag = 1;
			printf("%d %d", P->coef, P->expon);
		}
		else
			printf(" %d %d", P->coef, P->expon);
		P = P->Next;
	}

}
int main()
{
	PtrToLNode P1;
	PtrToLNode P2;
	PtrToLNode A;
	PtrToLNode M;
	P1 = Read();//ReadInput(P1);
	P2 = Read();// ReadInput(P2);
	if (P1&&P2)
	{
		M = Multiple(P1, P2);
		Print(M);
	}
	else
		printf("0 0"); printf("\n");//换行
	A = Add(P1, P2);
	Print(A);
}