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

		scanf_s("%d", &a[j]);//到此部分为对数组全部赋上值

	int M = 0; int S = 0; int b = 0; int s = 0; int tag;

	for (int i = N-1; i >=0; i--)

	{

		S += a[i];

		if (S >=M)

		{

			M = S;//renew the biggest number

			b = i;//记下当前序号，方便后续输出开头和结尾

		}

		if (S < 0)

			S = 0;//abandon current sum

	}

	if (M == 0)//对全为负数和含有零分情况讨论

	{

		for (int i = 0; i < N; i++)

			if (a[i] == 0)

			{

				printf("0 %d %d", a[i], a[i]);

				return 0;

			}//如果存在一个数为0，输出并跳出程序；

		printf("0 %d %d", a[0], a[N - 1]);//如果没有0，那么输出这条

	}

	else//对于含有正数的情况
		///b作为最开始的数（0也有可能）
	{
		for (int m = b; m <= N - 1; m++)

		{

			s += a[m];


			if (s == M)//如果相等，初始化s，记下此时的序号tag
			{
				s = 0;
				tag = m;
			}
		}//得到最后一次使s=M的下标值tag
		printf("%d %d %d", M, a[b], a[tag]);
	}
}