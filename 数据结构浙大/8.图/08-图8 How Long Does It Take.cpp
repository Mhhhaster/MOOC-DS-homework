#include<iostream>
#define Uplimit 65535
#define End -1
#define ERROR -1
#include<queue>
using namespace std;
int G[1000][1000];
int Getmax(int ECtime[], int N)
{
	int max = 0;
	for (int i = 0; i < N; i++)
		if (ECtime[i] > max)
			max = ECtime[i];
	return max;
}
int Get_earliest_completion_time(int N)
{
	queue<int>Q;
	int Indegree[1000] = { 0 };
	int ECtime[1000] = { 0 };
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (G[i][j] != Uplimit && i != j)//注意不能统计自身到自身不能算入度
				Indegree[j]++;//初始化入度
	for (int i = 0; i < N; i++)
		if (Indegree[i] == 0)
			Q.push(i);//把入读为零的点加入队列
	int times = 0;
	while (!Q.empty())
	{
		int V = Q.front();
		Q.pop();
		times++;
		for (int W = 0; W < N; W++)
		{
			if (G[V][W] != Uplimit && V != W)//V到W有边,注意，V和W不能相同
			{
				if (G[V][W] + ECtime[V] > ECtime[W])
					ECtime[W] = ECtime[V] + G[V][W];
				Indegree[W]--;
				if (Indegree[W] == 0)
					Q.push(W);
			}
		}
	}//队列为空跳出循环，判断是否已全部收录
	if (times != N)
		return ERROR;
	else
		return Getmax(ECtime, N);
}
int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (i == j)
				G[i][j] = 0;
			else
				G[i][j] = Uplimit;
		}
	int t1, t2, weight;
	while (M--)
	{
		scanf("%d%d%d", &t1, &t2, &weight);
		G[t1][t2] = weight;
	}
	int ECT = Get_earliest_completion_time(N);
	if (ECT == ERROR)
		printf("Impossible");
	else
		printf("%d", ECT);
	return 0;
}
/*9 12
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
5 4 0
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4*/