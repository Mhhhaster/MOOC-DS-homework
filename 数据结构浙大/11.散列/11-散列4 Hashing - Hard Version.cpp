#include<iostream>
using namespace std;
int G[1000][1000] = { 0 };
#include<queue>
int getposition(int n, int a[],int N)
{
	for (int i = 0; i < N; i++)
		if (a[i] == n)
			return i;
	return -1;
}
int main()
{
	int tablesize;
	priority_queue<int, vector<int>, greater<int>>H;
	scanf("%d", &tablesize);
	int a[1000];
	for (int i = 0; i < tablesize; i++)
		scanf("%d", &a[i]);
	int Indegree[1000];
	for (int i = 0; i < tablesize; i++)
	{
		if (a[i] < 0)
			continue;
		if (a[i] % tablesize == i)
		{
			Indegree[i] = 0;
			H.push(a[i]);
		}
		else
		{
			if (a[i] % tablesize < i)
			{
				Indegree[i] = i - a[i] % tablesize;
				for (int j = a[i] % tablesize; j < i; j++)
					G[j][i] = 1;
			}
			else
			{
				Indegree[i] = tablesize + i - a[i] % tablesize;
				for (int j = a[i] % tablesize; j < i + tablesize; j++)
					G[j % tablesize][i] = 1;
			}
		}
	}
	int V = getposition(H.top(),a,tablesize);
	printf("%d",H.top());
	H.pop();
	for(int i=0;i<tablesize;i++)
		if (G[V][i] != 0)
		{
			Indegree[i]--;
			if (Indegree[i] == 0)
				H.push(a[i]);
		}
	while (!H.empty())
	{
		V = getposition(H.top(),a,tablesize);
		printf(" %d", H.top());
		H.pop();
		for (int i = 0; i < tablesize; i++)
			if (G[V][i] != 0)
			{
				Indegree[i]--;
				if (Indegree[i] == 0)
					H.push(a[i]);
			}
	}
	return 0;
}