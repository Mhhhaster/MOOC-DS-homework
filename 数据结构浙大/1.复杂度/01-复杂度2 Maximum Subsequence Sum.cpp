#include<iostream>

#include<stdio.h>

#define K 120000

using namespace std;

int main()

{

	int N;

	scanf_s("%d/n", &N);

	int a[K] = { -1 };

	for (int j = 0; j < N; j++)

		scanf_s("%d", &a[j]);//���˲���Ϊ������ȫ������ֵ

	int M = 0; int S = 0; int b = 0; int s = 0; int tag;

	for (int i = N-1; i >=0; i--)

	{

		S += a[i];

		if (S >=M)

		{

			M = S;//renew the biggest number

			b = i;//���µ�ǰ��ţ�������������ͷ�ͽ�β

		}

		if (S < 0)

			S = 0;//abandon current sum

	}

	if (M == 0)//��ȫΪ�����ͺ�������������

	{

		for (int i = 0; i < N; i++)

			if (a[i] == 0)

			{

				printf("0 %d %d", a[i], a[i]);

				return 0;

			}//�������һ����Ϊ0���������������

		printf("0 %d %d", a[0], a[N - 1]);//���û��0����ô�������

	}

	else//���ں������������
		///b��Ϊ�ʼ������0Ҳ�п��ܣ�
	{
		for (int m = b; m <= N - 1; m++)

		{

			s += a[m];


			if (s == M)//�����ȣ���ʼ��s�����´�ʱ�����tag
			{
				s = 0;
				tag = m;
			}
		}//�õ����һ��ʹs=M���±�ֵtag
		printf("%d %d %d", M, a[b], a[tag]);
	}
}