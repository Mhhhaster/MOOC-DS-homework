#include<iostream>
using namespace std;
int main()
{
	int N;
	scanf("%d", &N);
	int* a = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &a[i]);
	int sum = 0;
	int max = 0;
	for (int i = 0; i < N; i++)
	{
		sum += a[i];
		if (sum < 0)
		{
			sum = 0;
			continue;
		}
		if (sum > max)
			max = sum;
	}
	printf("%d", max);
	return 0;
}