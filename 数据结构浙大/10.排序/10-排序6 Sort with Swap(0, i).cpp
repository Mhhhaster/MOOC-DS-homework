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
	}//��ʼ��Ϊtrue
	int times = 0;
	int start, temp;
	for (int i = 0; i < N; i++)
	{
		if (a[i] != i && b[i] == true)//a[i]��ֵ������b[i]��û�б���¼
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