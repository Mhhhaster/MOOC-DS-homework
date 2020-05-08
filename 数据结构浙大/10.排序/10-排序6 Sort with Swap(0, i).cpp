#include<iostream>
using namespace std;
int main()
{
	int N;
	scanf("%d", &N);
	int* a = (int*)malloc(N * sizeof(int));
	bool* b = (bool*)malloc(N * sizeof(bool));
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
		b[i] = true;
	}//初始化为true
	int times = 0;
	int start, temp;
	for (int i = 0; i < N; i++)
	{
		if (a[i] != i && b[i] == true)//a[i]的值不对且b[i]还没有被收录
		{
			int loopsize = 1;
			start = i;
			temp = a[i];
			b[i] = false;
			while (temp != start)
			{
				b[temp] = false;
				temp = a[temp];
				loopsize++;
			}
			if (start != 0)
				times += loopsize + 1;
			else
				times += loopsize -1;
		}
	}
	printf("%d", times);
}