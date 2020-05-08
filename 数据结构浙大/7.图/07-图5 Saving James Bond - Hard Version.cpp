#include<iostream>
#define Maxsize 100
#define Max 65535
using namespace std;
struct CroNode
{
	int x;
	int y;
}Cro[Maxsize];
typedef struct GNode Graph;
int G[Maxsize][Maxsize];
bool Isinborder(int i)//判断是否在边界内
{
	return (Cro[i].x < 50 && Cro[i].x > -50) && (Cro[i].y < 50 && Cro[i].y > -50) && (Cro[i].x * Cro[i].x + Cro[i].y * Cro[i].y > 56.25);
}
bool Firststep(int i, int D)
{
	return (Cro[i].x * Cro[i].x + Cro[i].y * Cro[i].y <= D * D + 15 * D + 56.25) && Isinborder(i);
}
bool Issafe(int j, int D)
{
	return (Cro[j].x >= 50 - D || Cro[j].x <= D - 50 || Cro[j].y >= 50 - D || Cro[j].y <= D - 50) && Isinborder(j);
}
bool IsClose(int i, int j,int D)
{
	return (Cro[i].x - Cro[j].x) * (Cro[i].x - Cro[j].x) + (Cro[i].y - Cro[j].y) * (Cro[i].y - Cro[j].y) <= D * D;
}
int path[Maxsize][Maxsize];
void Floyd(int Gsize)
{
	for (int i = 0; i < Gsize; i++)
		for (int j = 0; j < Gsize; j++)
			path[i][j] = -1;
	for (int k = 0; k < Gsize; k++)
		for (int i = 0; i < Gsize; i++)
			for (int j = 0; j < Gsize; j++)
				if (G[i][j] > G[i][k] + G[k][j])
				{
					G[i][j] = G[i][k] + G[k][j];
					path[i][j] = k;//i到j的路径可分成i到k，k到j
				}
}
void Printpath(int i, int j)
{
	if (path[i][j] == -1)
		return;
	int k = path[i][j];
	Printpath(i, k);
	printf("%d %d\n", Cro[k].x, Cro[k].y);
	Printpath(k, j);
}
int main()
{
	int N, D;
	scanf("%d%d", &N, &D);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &Cro[i].x, &Cro[i].y);
	if (D > 42.5)
	{
		printf("1");
		return 0;
	}
	for(int i=0;i<N;i++)//制矩阵
		for (int j = 0; j < N; j++)
		{
			if (i == j)
				G[i][j] = 0;
			else {
				if (IsClose(i, j, D))
					G[i][j] = 1;
				else
					G[i][j] = Max;
			}
		}
	Floyd(N);
	int start, end;
	int minstep = 100;
	for (int i = 0; i < N; i++)//尝试以每一个鳄鱼作为初始点
	{
		if (!Firststep(i, D))//如果这条鳄鱼不能第一步走上去
			continue;
		else
		{
			for (int j = 0; j < N; j++)//以每一条鳄鱼作为终点
			{
				if (!Issafe(j,D))//鳄鱼不安全
					continue;
				else if (G[i][j] < minstep || (G[i][j] == minstep && Cro[start].x * Cro[start].x + Cro[start].y * Cro[start].y > Cro[i].x * Cro[i].x + Cro[i].y * Cro[i].y))
					{
						start = i;
						end = j;
						minstep = G[i][j];
					}
			}
		}
	}
	if (minstep == 100)
	{
		printf("0");
		return 0;
	}
	
	printf("%d\n", minstep + 2);
	printf("%d %d\n", Cro[start].x, Cro[start].y);
	Printpath(start, end);
	printf("%d %d\n", Cro[end].x, Cro[end].y);
	return 0;
}
