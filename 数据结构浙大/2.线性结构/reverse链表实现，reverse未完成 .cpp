#include<iostream>
#pragma warning(disable:4996)
using namespace std;
typedef struct LNode *Ptr;
struct LNode {
	int ad;//������ָ���ȡ
	int num;
	int na;
	Ptr Next;
};
void attach(int a, int b, int c, Ptr *Rear)//����һ���սڵ�ָ��P����ֵ�����ӵ���󣬽�ָ��ָ��������ָ���޸�ΪP
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
//��Ŀ��Reversing Linked List��
//���⣺������Ե��ʣһ����Nȡ���ʱ����ʱδͨ����
//����������⹲ʹ�������������ڶ�������������ǰn�ת���������������·�ת�����һ����ַ��
//û�д����Ҷ���������ʱ�䣬����ֻ�ܶ�������������޸ģ�ϣ����ʦ���Ը�������Ժ�������������Ľ���
Ptr ReLink(Ptr a, int nexta)
{//����ͨ���Ը����ĳ�ʼ��һ����ַ���ϲ��Ҳ����£��������н�㰴�߼���ַ����
	Ptr rear, t, front, temp;
	t = a;//ԭʼ��ָ��t
	rear = (Ptr)malloc(sizeof(struct LNode));
	front = rear;//����սڵ㣬��front��rear��ָ����
	while (t)//���tָ��ǿ�
	{
		if (t->ad == nexta)//�����ǰ�ĵ�ַad�͸����������һ����ַnexta���
		{
			nexta = t->na;//��nexta����Ϊ��ǰ������һ����ַ
			attach(t->ad, t->num, t->na, &rear);//����rear����
			t = a;//ָ��t��λ
			continue;//��ͷ��ʼ����
		}
		t = t->Next;
	}
	rear->Next = NULL;//����β
	temp = front;
	front = front->Next;
	free(temp);//ȥ���ͷ
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
	}//������ɵ�kλ�ĵ������
	//��ʱrear��ͷ��front��β����frontΪ��
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
		a = a->Next;//ָ������k��
		K--;
		if (a==NULL)//���Ϊ��
		{
			Rear->Next = NULL;
			return front;//��βȥͷ��ָ������ͷ
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
	P = ReadInput(N);//�������ݣ�����
	P1 = ReLink(P, nexta);//�����ݰ���ַ�߼����кã�ƽ��
	P2 = Reverse(P1, K);//��תǰk��������
	P3 = Link(P2);//����һ����ַ�޸ģ�����
	OutPut(P3);//�����и�ʽ�����������
}
