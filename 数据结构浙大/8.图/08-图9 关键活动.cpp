#include<iostream>
#define Uplimit 65535
#include<queue>
#include<stack>
using namespace std;
int G[100][100];

int Getmax(int ECtime[], int N)
{
	int max = 0;
	for (int i = 0; i < N; i++)
		if (ECtime[i] > max)
			max = ECtime[i];
	return max;
}	
int ECtime[100] = { 0 };
stack<int>S;
int Get_earliest_completion_time(int N)
{
	queue<int>Q;
	int Indegree[100] = { 0 };
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (G[i][j] != Uplimit&&i!=j)
				Indegree[j]++;//初始化入度
	for (int i = 0; i < N; i++)
		if (Indegree[i] == 0)
			Q.push(i);//把入读为零的点加入队列
	int times = 0;
	while (!Q.empty())
	{
		int V = Q.front();
		S.push(V);//方便得到LCT
		Q.pop();
		times++;
		for (int W = 0; W < N; W++)
		{
			if (G[V][W] != Uplimit&&V!=W)//V到W有边
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
		return 0;
	else
		return Getmax(ECtime, N);
}
int LCtime[1000];
void Get_latest_competition_time(int N,int ECT)
{
	for (int i = 0; i < N; i++)
		LCtime[i] = ECT;
	while (!S.empty())
	{
		int W = S.top();
		S.pop();
		for (int V = 0; V < N; V++)
			if(G[V][W]<Uplimit&&V!=W)
				if (LCtime[W] - G[V][W] < LCtime[V])
					LCtime[V] = LCtime[W] - G[V][W];
	}
}
int AdjustTime[100][100];
void GetAdjustTime(int N)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			AdjustTime[i][j] = LCtime[j] - ECtime[i] - G[i][j];
}
void PrintCrucialWay(int N)
{
	for (int i = 0; i < N; i++)
		for (int j = N - 1; j >= 0; j--)
			if (AdjustTime[i][j] == 0&&i!=j)
				printf("%d->%d\n", i + 1, j + 1);
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
	int t1, t2, time;
	while (M--)
	{
		scanf("%d%d%d", &t1, &t2, &time);
		G[t1-1][t2-1] = time;
	}
	int ECT = Get_earliest_completion_time(N);
	printf("%d\n", ECT);
	Get_latest_competition_time(N,ECT);
	GetAdjustTime(N);
	PrintCrucialWay(N);
	return 0;
}
/*7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2

输出样例:
17
1->2
2->4
4->6
6->7*/