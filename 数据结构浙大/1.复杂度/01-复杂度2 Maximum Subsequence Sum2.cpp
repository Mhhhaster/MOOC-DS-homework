#include<iostream>
#include<stdio.h>
#define K 120000
using namespace std;
int main()
{
	int N;
	scanf("%d/n", &N);
	int a[K] = { 0 };
	for (int j = 0; j < N; j++)
		scanf("%d", &a[j]);//���˲���Ϊ������ȫ������ֵ
	int M = 0; int S = 0; int b = 0; int s = 0;
	for (int i = 0; i < N; i++)
	{
		S += a[i];
		if (S > M)
		{
			M = S;//renew the biggest number
			b = i;//���µ�ǰ���
		}
		if (S < 0)
			S = 0;//abandon current sum
	}
	if (M == 0)
	{
		for (int i = 0; i < N; i++)
			if (a[i] == 0)
			{
				printf("0 %d %d", a[i], a[i]);
				return 0;//�������һ����Ϊ0���������������
			}
		printf("0 %d %d", a[0], a[N - 1]);//���û��0����ô�������
	}
	else
		for (int m = b; m >= 0; m--)
		{
			s += a[m];
			if (s == M)
				printf("%d %d %d", M, a[m], a[b]);

		}///a[b]Ϊ������е����һ�����Ӵ˿�ʼ��ǰ�ӣ�����=������кͼ�ֹͣ��ֹͣ������ż�Ϊ��ʼ

}