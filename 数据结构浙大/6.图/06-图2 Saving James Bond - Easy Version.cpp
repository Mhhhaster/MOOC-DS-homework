#include<stdio.h>
#include<stdlib.h>
using namespace std;
typedef struct Crocodile* Ptr;
#define YES 1
struct Crocodile
{
	int x;
	int y;
}Cro[100];
bool Visited[100] = { false };
bool Ispath(int i,int j,int D)
{
	int _x = Cro[i].x - Cro[j].x;
	int _y = Cro[i].y - Cro[j].y;
	return _x * _x + _y * _y <= D * D;
}
bool FirstStep(int i,int D)
{
	return Cro[i].x * Cro[i].x + Cro[i].y * Cro[i].y < D * D + 15 * D + 56;
}
bool IsSafe(int i,int D)
{
	if (Cro[i].x >= 50 - D || Cro[i].x < D - 50 || Cro[i].y>50 - D || Cro[i].y<D - 50)
		return true;
	else return false;
}
int DFS(int i,int D,int N)
{
	Visited[i] = true;
	if (IsSafe(i, D))
		return YES;
	for (int j = 0; j < N; j++)
	{
		if(!Visited[j]&&Ispath(i,j,D))
			return DFS(j,D,N);
	}
	return -1;
}
void Save007(int N,int D)
{
	int answer;
	for (int i = 0; i < N; i++)
		if (!Visited[i] && FirstStep(i, D))
		{//对每一个可以第一脚踩上去的鳄鱼
			answer = DFS(i,D,N);
			if (answer == 1)
			{
				printf("Yes");
				return;
			}
		}
	printf("No");
	return;
}
int main()
{
	int N, D;
	scanf("%d%d", &N, &D);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &Cro[i].x, &Cro[i].y);
	Save007(N,D);
	return 0;
}