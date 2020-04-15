#include<iostream>
#include<stdio.h>
using namespace std;
int Find(int* a, int b)//���ص��Ǹ��ڵ������
{
	if (a[b] < 0)
		return b;
	else
		return a[b] = Find(a, a[b]);//·��ѹ��
}
void Check(int* a)
{
	int i, k;
	scanf("%d%d", &i, &k);
	if (Find(a, i) == Find(a, k))
		printf("yes\n");
	else
		printf("no\n");
}
void Link(int* a)
{
	int i, k;
	scanf("%d%d", &i, &k);
	if (Find(a, i) !=Find(a, k))
		a[Find(a, k)] = Find(a, i);
}
//43ms,���ȹ鲢����
void link(int* a)
{
	int i, k;
	scanf("%d%d", &i, &k);
	if (Find(a, i) > Find(a, k))//i�ĸ��ڵ��ȸ�С,i����k
	{
		a[Find(a, k)] += a[Find(a, i)];//��i���ڵ��ֵ���뵽k���ڵ�
		a[Find(a, i)] = Find(a, k);//k���ڵ���±긳��a[i���ڵ���±�]
	}
	else {
		a[Find(a, i)] += a[Find(a, k)];
		a[Find(a, k)] = Find(a, i);
	}
}
//40ms
int main()
{
	int N;
	scanf("%d", &N);
	int* a = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 1; i <= N; i++)//������a={-1}��ֻ�ܵ�һ��Ԫ����-1��������Ϊ0
		a[i] = -1;
	char op;
	cin>>op;
	while (op != 'S')
	{
		if (op == 'C')//��ѯ���ڵ��Ƿ����
			Check(a);
		else//�ϲ�������
			link(a);
		cin >> op;
	}
	int k=0;
	for (int i = 1; i <= N; i++)
	{
		if (a[i] < 0)//�������飬�����ж��ٸ����ڵ�
			k++;
	}
	if (k == 1)
		printf("The network is connected.");
	else
		printf("There are %d components.", k);
	return 0;
}