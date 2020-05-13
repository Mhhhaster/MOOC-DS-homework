#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
using namespace std;
int a[100000];
void Bubblesort(int N);//冒泡
void Insertionsort(int N);//简单插入
void Shellsort(int N);//希尔
void Selectionsort(int N);//简单选择
void Heapsort1(int N);//使用最小堆的堆排序
void Heapsort2(int N);//使用STL优先队列的堆排序
void Heapsort3(int N);//使用最大堆的堆排序
void Mergesort1(int N);//递归的归并排序
void Mergesort2(int N);//循环的归并排序
void Quicksort(int N);//快速排序
int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &a[i]);
	Mergesort2(N);//Quicksort(N);// Heapsort3(N);//Heapsort2(N);// Heapsort1(N);//Selectionsort(N);//Shellsort(N);//Insertionsort(N);//Bubblesort(N);
	printf("%d", a[0]);
	for (int i = 1; i < N; i++)
		printf(" %d", a[i]);
	return 0;
}
void Bubblesort(int N)
{
	int temp;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - i - 1; j++)
			if (a[j] > a[j + 1])
			{
				temp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = temp;
			}
	}
}//没什么好说的，两遍循环，第二遍循环的终止条件记得每次提前就行
void Insertionsort(int N)
{
	int j;
	for (int i = 1; i < N; i++)//这里从1开始
	{
		int tmp = a[i];
		for (j = i - 1; j >= 0 && a[j] > tmp; j--)//j从i开始，比较j-1个元素
			a[j + 1] = a[j];//上方不能交换位置
		a[j + 1] = tmp;
	}
}//从1开始，每次与前面的元素比较，移位，赋值。
int scanformin(int p, int q)
{
	int min = a[p];
	int tag = p;
	for (int i = p + 1; i <= q; i++)
	{
		if (a[i] < min)
		{
			min = a[i];
			tag = i;
		}
	}
	return tag;
}
void Selectionsort(int N)
{
	int min;
	for (int i = 0; i < N; i++)
	{
		min = scanformin(i, N - 1);
		swap(a[i], a[min]);//居然不需要取地址
	}
}//选择+交换
void Shellsort(int N)
{
	int i;
	int j;//代表插入排序
	int start;
	int step;
	int sedgewick[] = { 109,41,19,5,1,0 };//降序
	//初始增量不能比数组长
	for (start = 0; sedgewick[start] >= N; start++)
		;
	//此时的sedgewick[start]小于数组长度
	for (step = sedgewick[start]; start <= 4; step = sedgewick[++start])//三重for循环，分别对应增列个数和插入排序
		for (i = step; i < N; i++)//从第D个数开始向前插入
		{
			int temp = a[i];
			for (j = i; j >= step && a[j - step] > temp; j -= step)
				a[j] = a[j - step];//上方不能交换位置
			a[j] = temp;
		}
}//找到适宜的开头增量，循环递减；循环插入排序
void percdownmin(int i, int N)//对规模为N的堆，从下标i开始下滤调整
{
	int temp = a[i];
	int child;
	int j;
	for (j = i; j * 2 + 2 <= N; j = child)//j从节点i开始下滤,直到它没有孩子
	{
		child = j * 2 + 1;
		if (child != N - 1 && a[child + 1] < a[child])//如果有右孩子且它比左孩子小
			child++;//指向右孩子
		if (temp > a[child])//如果孩子更小，孩子提上来，进入下一层循环
			a[j] = a[child];
		else
			break;//此时的temp比child小，
	}
	//出循环为要么没孩子，要么找到位置
	a[j] = temp;
}
void BuildHeap(int N)//a[i]小于a[2*i+1]和a[2*i+2]
{
	for (int i = N / 2 - 1; i >= 0; i--)//八个元素，最后一个为a[7]，传入N=8，要从第三个元素开始，因为没有哨兵
		percdownmin(i, N);
}
int heapsize;//指示堆规模,size不明确
int deletemin()//取出队列顶端元素，并调整为最小堆
{
	int min = a[0];//先储存要返回元素
	heapsize--;
	a[0] = a[heapsize];
	percdownmin(0, heapsize);//从节点0开始下滤
	return min;
}
void Heapsort1(int N)//使用最小堆
{
	BuildHeap(N);//把数组a调整为最小堆；
	heapsize = N;
	int b[100000];//新建一个数组，用来储存排序结果；
	for (int i = 0; i < N; i++)
		b[i] = deletemin();//把堆顶元素赋给b,每操作一次规模减一
	for (int i = 0; i < N; i++)
		a[i] = b[i];
}//需要额外的空间存储排序结果最后再倒回去
void Heapsort2(int N)//使用优先队列
{
	priority_queue<int, vector<int>, greater<int>>Q;//记住这里的格式，greater代表递增，默认递减
	for (int i = 0; i < N; i++)
		Q.push(a[i]);
	for (int i = 0; i < N; i++)
	{
		a[i] = Q.top();
		Q.pop();
	}
}
void Percdownmax(int i, int N)
{
	int Parent, Child;
	int temp = a[i]; /* 取出根结点存放的值 */
	for (Parent = i; (Parent * 2 + 1) < N; Parent = Child) {
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (a[Child] < a[Child + 1]))
			Child++;  /* Child指向左右子结点的较大者 */
		if (temp >= a[Child]) break; /* 找到了合适位置 */
		else  /* 下滤X */
			a[Parent] = a[Child];
	}
	a[Parent] = temp;
}
void Heapsort3(int N)//使用最大堆
{
	for (int i = N / 2 - 1; i >= 0; i--)
		Percdownmax(i, N);
	for (int i = N - 1; i > 0; i--)//交换N-1次
	{
		swap(a[0], a[i]);//交换第一个和最后一个元素
		Percdownmax(0, i);
	}
}//建堆,循环N-1次{交换首尾，调堆}
void Merge(int b[], int start, int mid, int end)//归并，需要多一个参数指示两端分界点(实际上数组b仅在此使用,作为临时容器
{
	int left = start;
	int leftend = mid;
	int right = mid + 1;
	int rightend = end;
	int temp = left;
	int num = end - start + 1;//记录元素个数
	while (left <= leftend && right <= rightend)//简单的有序子列合并
	{
		if (a[left] > a[right])//左大于右，升序排列，所以右入
			b[temp++] = a[right++];
		else
			b[temp++] = a[left++];
	}
	while (left <= leftend)
		b[temp++] = a[left++];
	while (right <= rightend)
		b[temp++] = a[right++];
	//现在temp等指针都指在末尾，需要把b数组元素复制回a数组
	for (int i = end; i > end - num; i--)
	{
		a[i] = b[i];
	}
}//类似合并两个链表，最后记得倒回原始数组
void MSort(int b[], int start, int end)//递归，解决左右半边+归并
{
	int mid = (start + end) / 2;
	if (start < end)
	{
		MSort(b, start, mid);
		MSort(b, mid + 1, end);
		Merge(b, start, mid, end);
	}
}
void Mergesort1(int N)//申请额外数组空间，并传入，统一接口
{
	int* b = (int*)malloc(N * sizeof(int));
	MSort(b, 0, N - 1);
	free(b);
	return;
}

void Mergesort2(int N)
{
	int* TmpA= (int*)malloc(N * sizeof(int));
	int length = 1; /* 初始化子序列长度*/
	int i;
	while (length < N) {
	\
		for (i = 0; i <= N - 2 * length; i += 2 * length)
			Merge(TmpA, i, i + length-1, i + 2 * length - 1);//每次归并2*length长的子列
		if (i + length < N) /* 归并最后2个子列*/
			Merge(TmpA, i, i + length-1, N - 1);
		length *= 2;
	}
	free(TmpA);
}
int Median(int Left, int Right)//与例题类似，不过这里选择将中间值藏在左边的位置
{
	int mid = (Left + Right) / 2;
	if (a[Left] > a[Right])
		swap(a[Left], a[Right]);
	if (a[Left] > a[mid])
		swap(a[Left], a[mid]);
	if (a[mid] > a[Right])
		swap(a[mid], a[Right]);
	swap(a[mid], a[Left + 1]);
	return a[Left + 1];
}
void Qsort(int Left, int Right)
{
	if (Right - Left < 1)
		return;
	if (Right - Left == 1)
	{
		if (a[Right] < a[Left])
			swap(a[Right], a[Left]);
		return;
	}//只有两个元素以下时是快速排序的终止条件
	int left = Left + 1;
	int right = Right + 1;
	int Pivot = Median(Left, Right);
	while (1)
	{
		while (a[++left] < Pivot);
		while (a[--right] > Pivot);
		if (left < right)
			swap(a[left], a[right]);
		else
			break;
	}//要注意终止时的left和right位置，刚好差一个
	swap(a[Left + 1], a[right]);
	Qsort(Left, right - 1);
	Qsort(left, Right);
}
void Quicksort(int N)
{
	Qsort(0, N - 1);
}
