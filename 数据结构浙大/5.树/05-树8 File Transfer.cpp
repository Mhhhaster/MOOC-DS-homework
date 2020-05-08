#include<iostream>
#include<stdio.h>
using namespace std;
int Find(int* a, int b)//返回的是根节点的数据
{
	if (a[b] < 0)
		return b;
	else
		return a[b] = Find(a, a[b]);//路径压缩
}
void Check(int* a)
{
	int i, k;
	scanf("%d%d", &i, &k);
	if (Find(a, i) == Find(a, k))
		printf("yes\n");
	else
		printf("no\n");
}
void Link(int* a)
{
	int i, k;
	scanf("%d%d", &i, &k);
	if (Find(a, i) !=Find(a, k))
		a[Find(a, k)] = Find(a, i);
}
//43ms,按秩归并如下
void link(int* a)
{
	int i, k;
	scanf("%d%d", &i, &k);
	if (Find(a, i) > Find(a, k))//i的根节点秩更小,i加入k
	{
		a[Find(a, k)] += a[Find(a, i)];//将i根节点的值加入到k根节点
		a[Find(a, i)] = Find(a, k);//k根节点的下标赋给a[i根节点的下标]
	}
	else {
		a[Find(a, i)] += a[Find(a, k)];
		a[Find(a, k)] = Find(a, i);
	}
}
//40ms
int main()
{
	int N;
	scanf("%d", &N);
	int* a = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 1; i <= N; i++)//不能用a={-1}，只能第一个元素置-1，后续都为0
		a[i] = -1;
	char op;
	cin>>op;
	while (op != 'S')
	{
		if (op == 'C')//查询两节点是否相接
			Check(a);
		else//合并两集合
			link(a);
		cin >> op;
	}
	int k=0;
	for (int i = 1; i <= N; i++)
	{
		if (a[i] < 0)//遍历数组，看看有多少个根节点
			k++;
	}
	if (k == 1)
		printf("The network is connected.");
	else
		printf("There are %d components.", k);
	return 0;
}