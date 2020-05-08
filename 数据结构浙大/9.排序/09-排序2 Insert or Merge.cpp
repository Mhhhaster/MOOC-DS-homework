#include<iostream>
#define ElementType int
using namespace std;
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{ /* �������A[L]~A[R-1]��A[R]~A[RightEnd]�鲢��һ���������� */
	int LeftEnd, NumElements, Tmp;
	int i;

	LeftEnd = R - 1; /* ����յ�λ�� */
	Tmp = L;         /* �������е���ʼλ�� */
	NumElements = RightEnd - L + 1;

	while (L <= LeftEnd && R <= RightEnd) {
		if (A[L] <= A[R])
			TmpA[Tmp++] = A[L++]; /* �����Ԫ�ظ��Ƶ�TmpA */
		else
			TmpA[Tmp++] = A[R++]; /* ���ұ�Ԫ�ظ��Ƶ�TmpA */
	}
	while (L <= LeftEnd)
		TmpA[Tmp++] = A[L++]; /* ֱ�Ӹ������ʣ�µ� */
	while (R <= RightEnd)
		TmpA[Tmp++] = A[R++]; /* ֱ�Ӹ����ұ�ʣ�µ� */
}
int length = 1;
void Merge_Sort(int A[], int N)//��һ�ι鲢��length*=2
{
	int* TmpA;
	TmpA = (int*)malloc(N * sizeof(int));
	int i, j;
	for (i = 0; i <= N - 2 * length; i += 2 * length)
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);//������Ϊlength��һ�ԶԷ���tmpA��
	if (i + length < N) /* �鲢���2������*/
		Merge(A, TmpA, i, i + length, N - 1);
	else /* ���ֻʣ1������*/
		for (j = i; j < N; j++) TmpA[j] = A[j];
	for (int i = 0; i < N; i++)
		A[i] = TmpA[i];
	length *= 2;
	free(TmpA);
}
int position = 1;
int Insertionsort(int ins[])//����һ��ѡ������
{
	int j;
	int temp = ins[position];//�ҵ���θò����Ԫ��
	for (j = position; j >= 1&& ins[j-1] > temp; j--)//Ҳ����j=position-1
			ins[j] = ins[j-1];
	ins[j] = temp;
	position++;
	if (j == position-1)
		return 0;
	else
		return 1;
}
int main()
{
	int N;
	cin >> N;
	int* ini = (int*)malloc(N * sizeof(int));
	int* fin = (int*)malloc(N * sizeof(int));
	int* ins = (int*)malloc(N * sizeof(int));
	int* mer = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		scanf_s("%d", &ini[i]);
	for (int i = 0; i < N; i++)
		scanf_s("%d", &fin[i]);
	int times = N;
	for (int i = 0; i < N; i++)
	{
		ins[i] = ini[i];
		mer[i] = ini[i];
	}//��ʼ������������������
	while(times)//����������N-1��
	{//�����ins�������mer������fin������ȫ��ͬ����ô���xxx��break;
		int j = 0;
		int k = 0;
		for (int i = 0; i < N; i++)
		{
			if (fin[i] == ins[i])
				j++;
			if (fin[i] == mer[i])
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
			printf("Merge Sort\n");
			Merge_Sort(mer,N);
			printf("%d",mer[0]);
			for (int i = 1; i < N; i++)
				printf(" %d", mer[i]);
			return 0;
		}
		Merge_Sort(mer, N);
		Insertionsort(ins);
	}
}