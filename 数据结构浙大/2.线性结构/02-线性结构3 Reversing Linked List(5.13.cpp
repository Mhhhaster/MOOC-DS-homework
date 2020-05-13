/*Sample Input:
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218
Sample Output:
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1*/
#include<iostream>
using namespace std;
struct Node {
	int data;
	int next=-2;
}Link[100000];//00000到99999
int rankbyadd[100000];//指示各结点实际的排序顺序，排序从0开始
int Rank(int firstadd, int N)
{
	int add = firstadd;
	for (int i = 0;i<N; i++)
	{
		rankbyadd[i] = add;
		add = Link[add].next;
		if (add == -1)
			return i + 1;
	}
}
void Reverse(int start, int end)
{
	while (start < end)
	{
		swap(rankbyadd[start], rankbyadd[end]);
		start++;
		end--;
	}
	return;
}
void Getreverse(int N, int K)//对排序顺序进行翻转
{
	int start = 0;
	int end = K-1;
	while (end <= N - 1)
	{
		Reverse(start, end);
		start += K;
		end += K;
	}
	return;
}
void Print(int N)
{
	for (int i = 0; i < N-1; i++)
		printf("%05d %d %05d\n", rankbyadd[i], Link[rankbyadd[i]].data, rankbyadd[i + 1]);
	printf("%05d %d -1", rankbyadd[N - 1], Link[rankbyadd[N - 1]].data);
}
int main()
{
	int Firstadd, N, K;
	scanf("%d%d%d", &Firstadd, &N, &K);
	int add, data, nextadd;
	for(int i=0;i<N;i++)
	{
		scanf("%d%d%d", &add, &data, &nextadd);
		Link[add].data = data;
		Link[add].next = nextadd;
	}
	int Reallength=Rank(Firstadd, N);//这里还要判断是否有多余节点在链表少，需要返回一个真实链表长度，方便翻转
	Getreverse(Reallength,K);
	Print(Reallength);
	return 0;
}