#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
using namespace std;
int a[100000];
void Bubblesort(int N);//ð��
void Insertionsort(int N);//�򵥲���
void Shellsort(int N);//ϣ��
void Selectionsort(int N);//��ѡ��
void Heapsort1(int N);//ʹ����С�ѵĶ�����
void Heapsort2(int N);//ʹ��STL���ȶ��еĶ�����
void Heapsort3(int N);//ʹ�����ѵĶ�����
void Mergesort1(int N);//�ݹ�Ĺ鲢����
void Mergesort2(int N);//ѭ���Ĺ鲢����
void Quicksort(int N);//��������
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
}//ûʲô��˵�ģ�����ѭ�����ڶ���ѭ������ֹ�����ǵ�ÿ����ǰ����
void Insertionsort(int N)
{
	int j;
	for (int i = 1; i < N; i++)//�����1��ʼ
	{
		int tmp = a[i];
		for (j = i - 1; j >= 0 && a[j] > tmp; j--)//j��i��ʼ���Ƚ�j-1��Ԫ��
			a[j + 1] = a[j];//�Ϸ����ܽ���λ��
		a[j + 1] = tmp;
	}
}//��1��ʼ��ÿ����ǰ���Ԫ�رȽϣ���λ����ֵ��
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
		swap(a[i], a[min]);//��Ȼ����Ҫȡ��ַ
	}
}//ѡ��+����
void Shellsort(int N)
{
	int i;
	int j;//�����������
	int start;
	int step;
	int sedgewick[] = { 109,41,19,5,1,0 };//����
	//��ʼ�������ܱ����鳤
	for (start = 0; sedgewick[start] >= N; start++)
		;
	//��ʱ��sedgewick[start]С�����鳤��
	for (step = sedgewick[start]; start <= 4; step = sedgewick[++start])//����forѭ�����ֱ��Ӧ���и����Ͳ�������
		for (i = step; i < N; i++)//�ӵ�D������ʼ��ǰ����
		{
			int temp = a[i];
			for (j = i; j >= step && a[j - step] > temp; j -= step)
				a[j] = a[j - step];//�Ϸ����ܽ���λ��
			a[j] = temp;
		}
}//�ҵ����˵Ŀ�ͷ������ѭ���ݼ���ѭ����������
void percdownmin(int i, int N)//�Թ�ģΪN�Ķѣ����±�i��ʼ���˵���
{
	int temp = a[i];
	int child;
	int j;
	for (j = i; j * 2 + 2 <= N; j = child)//j�ӽڵ�i��ʼ����,ֱ����û�к���
	{
		child = j * 2 + 1;
		if (child != N - 1 && a[child + 1] < a[child])//������Һ�������������С
			child++;//ָ���Һ���
		if (temp > a[child])//������Ӹ�С��������������������һ��ѭ��
			a[j] = a[child];
		else
			break;//��ʱ��temp��childС��
	}
	//��ѭ��ΪҪôû���ӣ�Ҫô�ҵ�λ��
	a[j] = temp;
}
void BuildHeap(int N)//a[i]С��a[2*i+1]��a[2*i+2]
{
	for (int i = N / 2 - 1; i >= 0; i--)//�˸�Ԫ�أ����һ��Ϊa[7]������N=8��Ҫ�ӵ�����Ԫ�ؿ�ʼ����Ϊû���ڱ�
		percdownmin(i, N);
}
int heapsize;//ָʾ�ѹ�ģ,size����ȷ
int deletemin()//ȡ�����ж���Ԫ�أ�������Ϊ��С��
{
	int min = a[0];//�ȴ���Ҫ����Ԫ��
	heapsize--;
	a[0] = a[heapsize];
	percdownmin(0, heapsize);//�ӽڵ�0��ʼ����
	return min;
}
void Heapsort1(int N)//ʹ����С��
{
	BuildHeap(N);//������a����Ϊ��С�ѣ�
	heapsize = N;
	int b[100000];//�½�һ�����飬����������������
	for (int i = 0; i < N; i++)
		b[i] = deletemin();//�ѶѶ�Ԫ�ظ���b,ÿ����һ�ι�ģ��һ
	for (int i = 0; i < N; i++)
		a[i] = b[i];
}//��Ҫ����Ŀռ�洢����������ٵ���ȥ
void Heapsort2(int N)//ʹ�����ȶ���
{
	priority_queue<int, vector<int>, greater<int>>Q;//��ס����ĸ�ʽ��greater���������Ĭ�ϵݼ�
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
	int temp = a[i]; /* ȡ��������ŵ�ֵ */
	for (Parent = i; (Parent * 2 + 1) < N; Parent = Child) {
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (a[Child] < a[Child + 1]))
			Child++;  /* Childָ�������ӽ��Ľϴ��� */
		if (temp >= a[Child]) break; /* �ҵ��˺���λ�� */
		else  /* ����X */
			a[Parent] = a[Child];
	}
	a[Parent] = temp;
}
void Heapsort3(int N)//ʹ������
{
	for (int i = N / 2 - 1; i >= 0; i--)
		Percdownmax(i, N);
	for (int i = N - 1; i > 0; i--)//����N-1��
	{
		swap(a[0], a[i]);//������һ�������һ��Ԫ��
		Percdownmax(0, i);
	}
}//����,ѭ��N-1��{������β������}
void Merge(int b[], int start, int mid, int end)//�鲢����Ҫ��һ������ָʾ���˷ֽ��(ʵ��������b���ڴ�ʹ��,��Ϊ��ʱ����
{
	int left = start;
	int leftend = mid;
	int right = mid + 1;
	int rightend = end;
	int temp = left;
	int num = end - start + 1;//��¼Ԫ�ظ���
	while (left <= leftend && right <= rightend)//�򵥵��������кϲ�
	{
		if (a[left] > a[right])//������ң��������У���������
			b[temp++] = a[right++];
		else
			b[temp++] = a[left++];
	}
	while (left <= leftend)
		b[temp++] = a[left++];
	while (right <= rightend)
		b[temp++] = a[right++];
	//����temp��ָ�붼ָ��ĩβ����Ҫ��b����Ԫ�ظ��ƻ�a����
	for (int i = end; i > end - num; i--)
	{
		a[i] = b[i];
	}
}//���ƺϲ������������ǵõ���ԭʼ����
void MSort(int b[], int start, int end)//�ݹ飬������Ұ��+�鲢
{
	int mid = (start + end) / 2;
	if (start < end)
	{
		MSort(b, start, mid);
		MSort(b, mid + 1, end);
		Merge(b, start, mid, end);
	}
}
void Mergesort1(int N)//�����������ռ䣬�����룬ͳһ�ӿ�
{
	int* b = (int*)malloc(N * sizeof(int));
	MSort(b, 0, N - 1);
	free(b);
	return;
}

void Mergesort2(int N)
{
	int* TmpA= (int*)malloc(N * sizeof(int));
	int length = 1; /* ��ʼ�������г���*/
	int i;
	while (length < N) {
	\
		for (i = 0; i <= N - 2 * length; i += 2 * length)
			Merge(TmpA, i, i + length-1, i + 2 * length - 1);//ÿ�ι鲢2*length��������
		if (i + length < N) /* �鲢���2������*/
			Merge(TmpA, i, i + length-1, N - 1);
		length *= 2;
	}
	free(TmpA);
}
int Median(int Left, int Right)//���������ƣ���������ѡ���м�ֵ������ߵ�λ��
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
	}//ֻ������Ԫ������ʱ�ǿ����������ֹ����
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
	}//Ҫע����ֹʱ��left��rightλ�ã��պò�һ��
	swap(a[Left + 1], a[right]);
	Qsort(Left, right - 1);
	Qsort(left, Right);
}
void Quicksort(int N)
{
	Qsort(0, N - 1);
}
