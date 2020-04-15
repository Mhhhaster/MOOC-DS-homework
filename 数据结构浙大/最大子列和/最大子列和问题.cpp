#include<iostream>
#include<stdio.h>
#define K 120000
using namespace std;
int main()
{
	int N; int Max = 0; int S = 0; int L = 0; int b; int c=0;
	scanf_s("%d/n", &N);
	int a[K] = { 0 };
	for (int j = 0; j < N; j++)
		scanf_s("%d", &a[j]);
	for (int i = 0; i < N; i++)
	{
         S += a[i];
		if (a[i] >= 0)
		{
			Max = S; 
			if (Max >= L)
			{
				L = Max; b = i;
			}
		}
		if (S <= 0)
		{
			S = 0; Max = 0;
		}
	}
	for (int m = b;; b--)
	{
		c += a[m];
		if (c == L)
			break;
	}
	printf("%d%d%d", L,c,b);
}