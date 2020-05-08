#include<iostream>
#include<stdio.h>
using namespace std;
int position = 1;
int Insertionsort(int ins[])//进行一次选择排序
{
	int j;
	int temp = ins[position];//找到这次该插入的元素
	for (j = position; j >= 1 && ins[j - 1] > temp; j--)//也可令j=position-1
		ins[j] = ins[j - 1];
	ins[j] = temp;
	position++;
	if (j == position - 1)
		return 0;
	else
		return 1;
}
int heapsize;
void percdown(int hea[], int i)//对下标为i的下滤
{
	int temp = hea[i];
	int parent;
	int child;
	for (parent = i; parent * 2 + 1 <= heapsize - 1; parent = child)
	{
		child = 2 * parent + 1;//Δ放在第一句话
		if (child != heapsize - 1 && hea[child] < hea[child + 1])
			child++;//child指向更大的孩子
		if (hea[child] > temp)//如果孩子比顶部元素要大（Δ注意，不是比父亲大）
			hea[parent] = hea[child];//把孩子提上来
		else
			break;
	}
	//出来则说明孩子更小，parent就是要待的位置
	hea[parent] = temp;
}

void Heapsort(int hea[], int N)//执行一次调换，调堆
{
	swap(hea[0], hea[heapsize - 1]);
	heapsize--;
	percdown(hea, 0);
}
int main()
{
	int N;
	cin >> N;
	int* ini = (int*)malloc(N * sizeof(int));
	int* fin = (int*)malloc(N * sizeof(int));
	int* ins = (int*)malloc(N * sizeof(int));
	int* hea = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &ini[i]);
	for (int i = 0; i < N; i++)
		scanf("%d", &fin[i]);
	int times = N;
	heapsize = N;
	for (int i = 0; i < N; i++)
	{
		ins[i] = ini[i];
		hea[i] = ini[i];
	}//初始化两个排序结果的数组
	for (int i = N / 2 - 1; i >= 0; i--)//BuildHeap;
		percdown(hea, i);//从下标为i的地方开始调堆
	while (--times)//排序最多进行N-1次
	{//如果，ins数组或者mer数组与fin数组完全相同，那么输出xxx，break;
		int j = 0;
		int k = 0;
		for (int i = 0; i < N; i++)
		{
			if (fin[i] == ins[i])
				j++;
			if (fin[i] == hea[i])
				k++;
		}//j记录ins和ini有多少个元素相等，k为mer和ini
		if (j == N)//说明ins,fin完全相同
		{
			while (1) {
				if (Insertionsort(ins) == 1)
					break;//只要后续的交换不与之前相等就break
			}
			printf("Insertion Sort\n");
			printf("%d", ins[0]);
			for (int i = 1; i < N; i++)
				printf(" %d", ins[i]);
			return 0;
		}
		if (k == N)
		{
			printf("Heap Sort\n");
			Heapsort(hea, N);
			printf("%d", hea[0]);
			for (int i = 1; i < N; i++)
				printf(" %d", hea[i]);
			return 0;
		}
		Heapsort(hea, N);
		Insertionsort(ins);
	}
}