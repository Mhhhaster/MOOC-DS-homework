#include<iostream>
#define ElementType int
using namespace std;
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{ /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
	int LeftEnd, NumElements, Tmp;
	int i;

	LeftEnd = R - 1; /* 左边终点位置 */
	Tmp = L;         /* 有序序列的起始位置 */
	NumElements = RightEnd - L + 1;

	while (L <= LeftEnd && R <= RightEnd) {
		if (A[L] <= A[R])
			TmpA[Tmp++] = A[L++]; /* 将左边元素复制到TmpA */
		else
			TmpA[Tmp++] = A[R++]; /* 将右边元素复制到TmpA */
	}
	while (L <= LeftEnd)
		TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
	while (R <= RightEnd)
		TmpA[Tmp++] = A[R++]; /* 直接复制右边剩下的 */
}
int length = 1;
void Merge_Sort(int A[], int N)//做一次归并，length*=2
{
	int* TmpA;
	TmpA = (int*)malloc(N * sizeof(int));
	int i, j;
	for (i = 0; i <= N - 2 * length; i += 2 * length)
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);//将长度为length的一对对放入tmpA中
	if (i + length < N) /* 归并最后2个子列*/
		Merge(A, TmpA, i, i + length, N - 1);
	else /* 最后只剩1个子列*/
		for (j = i; j < N; j++) TmpA[j] = A[j];
	for (int i = 0; i < N; i++)
		A[i] = TmpA[i];
	length *= 2;
	free(TmpA);
}
int position = 1;
int Insertionsort(int ins[])//进行一次选择排序
{
	int j;
	int temp = ins[position];//找到这次该插入的元素
	for (j = position; j >= 1&& ins[j-1] > temp; j--)//也可令j=position-1
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
	}//初始化两个排序结果的数组
	while(times)//排序最多进行N-1次
	{//如果，ins数组或者mer数组与fin数组完全相同，那么输出xxx，break;
		int j = 0;
		int k = 0;
		for (int i = 0; i < N; i++)
		{
			if (fin[i] == ins[i])
				j++;
			if (fin[i] == mer[i])
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