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
		scanf("%d", &a[j]);//到此部分为对数组全部赋上值
	int M = 0; int S = 0; int b = 0; int s = 0;
	for (int i = 0; i < N; i++)
	{
		S += a[i];
		if (S > M)
		{
			M = S;//renew the biggest number
			b = i;//记下当前序号
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
				return 0;//如果存在一个数为0，输出并跳出程序；
			}
		printf("0 %d %d", a[0], a[N - 1]);//如果没有0，那么输出这条
	}
	else
		for (int m = b; m >= 0; m--)
		{
			s += a[m];
			if (s == M)
				printf("%d %d %d", M, a[m], a[b]);

		}///a[b]为最大子列的最后一个，从此开始往前加，至和=最大子列和即停止，停止到的序号即为开始

}