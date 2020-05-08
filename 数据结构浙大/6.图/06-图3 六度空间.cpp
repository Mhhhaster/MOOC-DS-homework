#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#define Maxsize 1001
#define Infinity 10000
typedef struct GNode *Graph;
struct GNode
{
	int Ne;
	int Nv;
	int G[Maxsize][Maxsize];
};
Graph BuildGraph(int N)
{
	Graph G = (Graph)malloc(sizeof(GNode));
	G->Nv = N;
	int M, v1, v2;
	scanf("%d", &M);
	G->Ne = M;
	for (int i = 0; i < G->Nv; i++)
		for (int j = 0; j < G->Nv; j++)
		{
			if (i == j)
				G->G[i][j] = 0;
			else
				G->G[i][j] = Infinity;//对角元为0，无边则为∞
		}
	while (M--)
	{
		scanf("%d%d", &v1, &v2);
		v1--; v2--;
		G->G[v1][v2] = 1;
		G->G[v2][v1] = 1;
	}
	return G;
}
int D[Maxsize][Maxsize];
void Floyd(Graph G)
{
	for (int i = 0; i < G->Nv; i++)
		for (int j = 0; j < G->Nv; j++)
			D[i][j] = G->G[i][j];//对角元为0，无边则为∞
	for (int k = 0; k < G->Nv; k++)
		for (int i = 0; i < G->Nv; i++)
			for (int j = 0; j < G->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j])
				{
					D[i][j] = D[i][k] + D[k][j];
				}
}
int main()
{
	int N;
	scanf("%d", &N);
	Graph G = BuildGraph(N);
	Floyd(G);
	int Count;
	for (int i = 0; i < G->Nv; i++)
	{
		Count = 0;
		for (int j = 0; j < G->Nv; j++)
			if (D[i][j] <= 6)
				Count++;
		float percentage = float(Count * 100) / float(G->Nv);
		printf("%d: %.2f%%\n", i + 1, percentage);
	}
}