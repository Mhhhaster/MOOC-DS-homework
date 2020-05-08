#include<iostream>
#define Uplimit 65535
#define End -1
using namespace std;
int G[1000][1000];
int Getnext(int N,int dist[])//��ȡ��������С�Ľڵ�
{
	int min=Uplimit;
	int minposition;
	for (int i = 0; i < N; i++)
	{
		if (dist[i] < min && dist[i]>0)//�ҵ�û�б���¼����С�ڵ�
		{
			min = dist[i];
			minposition = i;
		}
	}
	if (min == Uplimit)//ȫ����¼���߲���ͨ
		return End;
	else
		return minposition;
}
void Prim(int N)
{
	//��ʼ��
	int dist[1000];
	dist[0] = 0;
	int price = 0;
	int flag = 0;
	for (int i = 0; i < N; i++)
		dist[i] = G[0][i];
	while (1)
	{
		int nextvertex = Getnext(N,dist);
		flag++;
		if (nextvertex == End)
			break;
		price += dist[nextvertex];
		dist[nextvertex] = 0;
		for (int i = 0; i < N; i++)
		{
			if (dist[i] != 0 && dist[i] > G[nextvertex][i])//û�б���¼���ҿ����ҵ�����·��
				dist[i] = G[nextvertex][i];
		}
 	}
	if (flag == N)
	{
		printf("%d", price);
		return;
	}
	else
	{
		printf("-1");
		return;
	}
}
int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	for(int i=0;i<N;i++)
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
		G[t1 - 1][t2 - 1] = weight;
		G[t2 - 1][t1 - 1] = weight;
	}
	/*Prim�㷨��Kruskal�㷨û�д洢�ߵ���Ϣ������ʹ��*/
	Prim( N);
	return 0;
}