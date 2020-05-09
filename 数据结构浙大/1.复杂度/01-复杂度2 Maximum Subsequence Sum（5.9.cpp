#include<iostream>
using namespace std;
int main()
{
	int N;
	scanf("%d", &N);
	int* a = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &a[i]);
	int start = 0;
	int tempstart = 0;
	int end = 0;
	int sum = 0;
	int max = -1;
	for (int i = 0; i < N; i++)
	{
		sum += a[i];
		if (sum < 0)
		{
			sum = 0;
			tempstart = i + 1;
			continue;
		}
		if (sum > max)
		{
			max = sum;
			end = i;
			start = tempstart;
		}
	}
	if (max >= 0)
		printf("%d %d %d", max,a[start],a[end]);
	else
		printf("0 %d %d", a[0], a[N - 1]);
	return 0;
}