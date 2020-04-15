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
{//ȫ����ʼ��Ϊ0
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
		if (min > dist[i] && collect[i] == false)//�ҵ�δ����¼��dist��С��
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
void FindMin(Graph G, int S, int D)//����ͼG�ʹ����S��D��dijkstra�ҳ�S��D����̾���ͼ۸���Ҫ������СΪN�����飬dist��collect��price
{
	collect[S] = true;
	//��¼��ʼ��,���ڽӵ��ʼ��
	for (int i = 0; i < G->Nv; i++)
	{
		dist[i] = G->dis[S][i];
		price[i] = G->pri[S][i];
	}
	//ѭ�����ҵ�δ����¼�Ķ����о�������ߣ���¼�������ڽӵ��Ƿ���Ը��¡����Ҳ���ʱbreak��,�Ƚ�����С��
	while (1)
	{
		int V = Min(G);//�ҵ���ʼ����
		if (V == ERROR)
			break;
		for (int i = 0; i < G->Nv; i++)//�������ж���
		{
			if (collect[i] == false && G->dis[V][i] < Infinity)//����δ��¼���ڽӵ�
				if ((dist[V] + G->dis[V][i] < dist[i]) || (dist[V] + G->dis[V][i] == dist[i] && price[V] + G->pri[V][i] < price[i]))//������Ը���:Ҫô�����С��Ҫô������ȵ��۸��С
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