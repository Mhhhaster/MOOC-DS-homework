#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#define Maxsize 100
#define Infinity 65535
using namespace std;
typedef int Vertex;
typedef int Weight;
typedef struct GNode* Graph;
int D[100][100];
struct GNode
{
	int Nv;
	int Ne;
	Weight G[Maxsize][Maxsize];
};
Graph CreatGraph(int N)
{//ȫ����ʼ��Ϊ0
	Graph G = (Graph)malloc(sizeof(GNode));
	G->Nv = N;
	G->Ne = 0;
	for (int i = 0; i < G->Nv; i++)
		for (int j = 0; j < G->Nv; j++)
		{
			if (i != j)
				G->G[i][j] = Infinity;
			else
				G->G[i][j] = 0;
		}
	return G;
}
Graph BuildGraph(int N, int M)
{
	Graph G = CreatGraph(N);
	int a,b,weight;
	while (M--)
	{
		scanf("%d%d%d", &a, &b, &weight);
		G->G[--a][--b] = weight;
		G->G[b][a] = weight;
	}
	return G;
}
void Floyd(Graph G)
{
	for (int i = 0; i < G->Nv; i++)
		for (int j = 0; j < G->Nv; j++)
			D[i][j] = G->G[i][j];//��ʼ��
	for (int k = 0; k < G->Nv; k++)
		for (int i = 0; i < G->Nv; i++)
			for (int j = 0; j < G->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j])
					D[i][j] = D[i][k] + D[k][j];
}
void FindAnimal(Graph G)
{
	int Min = Infinity;
	int max;
	int tag;
	for (int i = 0; i < G->Nv; i++)//����ÿһ������Сֵ
	{
		max = 0;
		for (int j = 0; j < G->Nv; j++)//����ÿһ�������ֵ
		{
			
			if (D[i][j] > max)
				max = D[i][j];
			if (D[i][j] == Infinity)
			{
				printf("0");
				return;
			}
		}
		if (max < Min)
		{
			tag = i+1;
			Min = max;
		}
	}
	printf("%d %d",tag,Min);
}
int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	Graph G=BuildGraph(N, M);//����ͼ
	Floyd(G);//������D��Ϊfloyd����
	FindAnimal(G);
	return 0;
}