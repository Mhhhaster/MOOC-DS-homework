#include<iostream>
using namespace std;
typedef struct LNode *PtrToLNode;
struct LNode {
	int coef;//������ָ���ȡ
	int expon;//ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;//Postion��List�����������͵�ָ��

/* ���� *///���Ա�4p 4:50
#define ERROR NULL
Position Find(List L, int a, int b)
{
	Position p = L; /* pָ��L�ĵ�1����� *///L��ָ�룬��ָ���ַ����p
	while (p && (p->coef != a || p->expon != b))
		p = p->Next;
	/* ������������ return p; �滻 */
	return p;//if (p)		return p;	else		return ERROR;
}

/* ��ͷ���Ĳ��� */
/*ע��:�ڲ���λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P��������ָ�룬��P֮ǰ�����½�� */
bool Insert(List L, int a, int b, Position P)
{ /* ����Ĭ��L��ͷ��� */
	Position tmp, pre;//pre��tmp����Ϊλ��ָ��

	/* ����P��ǰһ����� */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);//pre��ͷ��ʼɨ��ֱ��ָ��P����ΪNULL
	if (pre == NULL) { /* P��ָ�Ľ�㲻��L�� */
		printf("����λ�ò�������\n");
		return false;
	}
	else { /* �ҵ���P��ǰһ�����pre */
		/* ��Pǰ�����½�� *///��ʱpreָ��P
		tmp = (Position)malloc(sizeof(struct LNode)); /* ���롢��װ��� */
		tmp->coef = a;
		tmp->expon = b;//���ڵ��������
		tmp->Next = P;//tmpָ��P
		pre->Next = tmp;//preָ��tmp��pre��P�м����tmp
		return true;
	}
}

/* ��ͷ����ɾ�� */
/*ע��:��ɾ��λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P����ɾ�����ָ�� */
bool Delete(List L, Position P)
{ /* ����Ĭ��L��ͷ��� */
	Position  pre;

	/* ����P��ǰһ����� */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);
	if (pre == NULL || P == NULL) { /* P��ָ�Ľ�㲻��L�� */
		printf("ɾ��λ�ò�������\n");
		return false;
	}
	else { /* �ҵ���P��ǰһ�����pre */
		/* ��Pλ�õĽ��ɾ�� */
		pre->Next = P->Next;//��pre��ָ��p����һ��������p
		free(P);//�ͷ�p
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
//ָ����Ҫ�仯�����Լ���&ȡ��ַ
void Attach(int a, int b, PtrToLNode *pRear)//����һ���սڵ�ָ��P����ֵ�����ӵ���󣬽�ָ��ָ��������ָ���޸�ΪP
{//���ã������a��b������Ϊ������ָ�����(Rear),ָ����λ
	PtrToLNode P;
	P = (PtrToLNode)malloc(sizeof(struct LNode));
	P->coef = a;
	P->expon = b;
	P->Next = NULL;
	(*pRear)->Next = P;
	*pRear = P;
}
/*�ӷ�*/
PtrToLNode  Add(PtrToLNode P1, PtrToLNode P2)//P1,P2λ��������ͷ
{//���������������ң����ϱȽϣ�˭���������
	PtrToLNode front, rear, temp;//��ʱ��������ָ��
	int sum;
	rear = (PtrToLNode)malloc(sizeof(struct LNode));
	front = rear;//front��rearָͬ
	while (P1&&P2)//����ָ�붼����ָ
		switch (Compare(P1->expon, P2->expon))
		{
		case 1://P1��ָ����P2
			Attach(P1->coef, P1->expon, &rear);//�������ý����ݽ���rearָ����� 
			P1 = P1->Next;//P1����
			break;
		case -1:
			Attach(P2->coef, P2->expon, &rear);
			P2 = P2->Next;
			break;
		case 0://������ȣ�ϵ�����
			sum = P1->coef + P2->coef;
			if (sum)Attach(sum, P1->expon, &rear);//�����������Թ�attach
			P1 = P1->Next;
			P2 = P2->Next;
			break;
		}//ѭ���˳�����Ϊһ��ָ�뵽ͷ
	for (; P1; P1 = P1->Next)Attach(P1->coef, P1->expon, &rear);
	for (; P2; P2 = P2->Next)Attach(P2->coef, P2->expon, &rear);
	rear->Next = NULL;//����ʱrear�ڱ����ĩβ����rearָ���
	temp = front;//��ʱ������ָ��
	front = front->Next;//frontָ�����
	free(temp);//�ͷſռ�
	return front;//�ص���ͷ
}

/*�˷�*/
PtrToLNode  Multiple(PtrToLNode P1, PtrToLNode P2)
{//�ȵõ�P1��һ���P2������P1ָ����ƣ��µõ������������һ�������
	PtrToLNode front, rear, temp;//��ʱ����ָ��
	rear = (PtrToLNode)malloc(sizeof(struct LNode));
	front = rear;
	PtrToLNode t1 = P1;
	PtrToLNode t2 = P2;
	if (t1)
	{
		while (t2)
		{
			Attach(t1->coef*t2->coef, t1->expon + t2->expon, &rear);
			t2 = t2->Next;//���ˣ��γ�һ��frontΪͷrearΪβ����,�����һ��˶���
		}
		temp = front;
		front = front->Next;
		free(temp);//��frontָ�����
		t2 = P2;//���ڶ������ʽ��ָ���λ��
	//�õ�һ��frontΪͷ��rearΪ����ĳ���ͣ���һ��Ŀ���ǽ�t1ָ����ƣ��ظ����
	}
	t1 = t1->Next;
	while (t1)
	{
		PtrToLNode Lrear, Lfront, Ltemp;//ÿ��ѭ���½�һ������
		Lrear = (PtrToLNode)malloc(sizeof(struct LNode));
		Lfront = Lrear;
		while (t2)
		{
			Attach(t1->coef*t2->coef, t1->expon + t2->expon, &Lrear);
			t2 = t2->Next;
		}//���ˣ��γ�һ��LfrontΪͷLrearΪβ����
		Ltemp = Lfront;
		Lfront = Lfront->Next;
		free(Ltemp);//��Lfrontָ�����
		t2 = P2;//���ڶ������ʽ��ָ���λ��
		front = Add(front, Lfront); //����һ�εõ��Ķ���ʽ����εõ��Ķ���ʽ���,
		free(Lfront); free(Lrear);//�ͷŵ���ʱ����ʽ
		t1 = t1->Next;//��һ������ʽ�ӵڶ�����㿪ʼ
	}
	return front;//�������ս������ͷ���
}

//�������ʽ
PtrToLNode Read()
{
	int a, b, N;
	PtrToLNode P, Rear, t;
	scanf("%d", &N);//
	P = (PtrToLNode)malloc(sizeof(struct LNode));
	P->Next = NULL;
	Rear = P;//P��Rearָ��һ������ָ�Ľ�㣬���������rear��
	while (N--)
	{
		scanf("%d %d", &a, &b);
		Attach(a, b, &Rear);
	}//�������ݵĽ��һ��������Rearָ�����
	t = P; P = P->Next; free(t);//tָ��սڵ㣬p���ƣ�ɾ��t
	return P;
}
//�������ʽ
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
		printf("0 0"); printf("\n");//����
	A = Add(P1, P2);
	Print(A);
}