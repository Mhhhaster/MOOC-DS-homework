#include<iostream>
#include<stdio.h>
using namespace std;
int position = 1;
int Insertionsort(int ins[])//����һ��ѡ������
{
	int j;
	int temp = ins[position];//�ҵ���θò����Ԫ��
	for (j = position; j >= 1 && ins[j - 1] > temp; j--)//Ҳ����j=position-1
		ins[j] = ins[j - 1];
	ins[j] = temp;
	position++;
	if (j == position - 1)
		return 0;
	else
		return 1;
}
int heapsize;
void percdown(int hea[], int i)//���±�Ϊi������
{
	int temp = hea[i];
	int parent;
	int child;
	for (parent = i; parent * 2 + 1 <= heapsize - 1; parent = child)
	{
		child = 2 * parent + 1;//�����ڵ�һ�仰
		if (child != heapsize - 1 && hea[child] < hea[child + 1])
			child++;//childָ�����ĺ���
		if (hea[child] > temp)//������ӱȶ���Ԫ��Ҫ�󣨦�ע�⣬���Ǳȸ��״�
			hea[parent] = hea[child];//�Ѻ���������
		else
			break;
	}
	//������˵�����Ӹ�С��parent����Ҫ����λ��
	hea[parent] = temp;
}

void Heapsort(int hea[], int N)//ִ��һ�ε���������
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
	}//��ʼ������������������
	for (int i = N / 2 - 1; i >= 0; i--)//BuildHeap;
		percdown(hea, i);//���±�Ϊi�ĵط���ʼ����
	while (--times)//����������N-1��
	{//�����ins�������mer������fin������ȫ��ͬ����ô���xxx��break;
		int j = 0;
		int k = 0;
		for (int i = 0; i < N; i++)
		{
			if (fin[i] == ins[i])
				j++;
			if (fin[i] == hea[i])
				k++;
		}//j��¼ins��ini�ж��ٸ�Ԫ����ȣ�kΪmer��ini
		if (j == N)//˵��ins,fin��ȫ��ͬ
		{
			while (1) {
				if (Insertionsort(ins) == 1)
					break;//ֻҪ�����Ľ�������֮ǰ��Ⱦ�break
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