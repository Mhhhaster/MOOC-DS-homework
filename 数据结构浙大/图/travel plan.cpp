#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#define MAX 500
#define Infinity 65535 
#define ERROR -1
using namespace std;
typedef struct GNode* PtrToGNode;
struct GNode
{
	int Nv;
	int dis[MAX][MAX];
	int pri[MAX][MAX];
};
typedef PtrToGNode Graph;
Graph CreatGraph(int N)
{//全部初始化为0
	Graph G = (Graph)malloc(sizeof(GNode));
	G->Nv = N;
	for (int i = 0; i < G->Nv; i++)
		for (int j = 0; j < G->Nv; j++)
		{
			if (i != j)
			{
				G->dis[i][j] = Infinity;
				G->pri[i][j] = Infinity;
			}
			else
			{
				G->dis[i][j] = 0;
				G->pri[i][j] = 0;
			}
		}
	return G;
}
Graph BuildGraph(int N, int M)
{
	Graph G = CreatGraph(N);
	int a, b, distance, price;
	while (M--)
	{
		scanf("%d%d%d%d", &a, &b, &distance, &price);
		G->dis[a][b] = distance;
		G->dis[b][a] = distance;
		G->pri[a][b] = price;
		G->pri[b][a] = price;
	}
	return G;
}
int dist[MAX], price[MAX];
int collect[MAX] = { false };
int Min(Graph G)
{
	int min, ser;
	min = Infinity;
	for (int i = 0; i < G->Nv; i++)
	{
		if (min > dist[i] && collect[i] == false)//找到未被收录且dist最小的
		{
			min = dist[i];
			ser = i;
		}
	}
	if (min == Infinity)
		return ERROR;
	collect[ser] = true;
	return ser;
}
void FindMin(Graph G, int S, int D)//根据图G和传入的S和D，dijkstra找出S到D的最短距离和价格，需要三个大小为N的数组，dist，collect，price
{
	collect[S] = true;
	//收录起始点,将邻接点初始化
	for (int i = 0; i < G->Nv; i++)
	{
		dist[i] = G->dis[S][i];
		price[i] = G->pri[S][i];
	}
	//循环：找到未被收录的顶点中距离最短者，收录，检验邻接点是否可以更新。（找不到时break）,先建立最小堆
	while (1)
	{
		int V = Min(G);//找到起始顶点
		if (V == ERROR)
			break;
		for (int i = 0; i < G->Nv; i++)//对于所有顶点
		{
			if (collect[i] == false && G->dis[V][i] < Infinity)//对于未收录的邻接点
				if ((dist[V] + G->dis[V][i] < dist[i]) || (dist[V] + G->dis[V][i] == dist[i] && price[V] + G->pri[V][i] < price[i]))//如果可以更新:要么距离更小，要么距离相等但价格更小
				{
					dist[i] = dist[V] + G->dis[V][i];
					price[i] = price[V] + G->pri[V][i];
				}
		}
	}
	printf("%d %d", dist[D], price[D]);

}
int main()
{
	int N, M, S, D;
	scanf("%d%d%d%d", &N, &M, &S, &D);
	Graph G = BuildGraph(N, M);
	FindMin(G, S, D);
	return 0;
}