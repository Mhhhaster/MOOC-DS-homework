//增量q>TableSize/2时即认为平方探测失败
#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct TblNode* HashTable;
struct TblNode {
	int TableSize;
	bool* heads;
};
HashTable CreateTable(int TableSize)
{
	HashTable H = (HashTable)malloc(sizeof(struct TblNode));
	H->TableSize = TableSize;
	H->heads = (bool*)malloc(TableSize * sizeof(bool));
	for (int i = 0; i < TableSize; i++)
		H->heads[i] = true;//true代表没元素可以插入
	return H;
}
int Hash(HashTable H, int key)
{
	return key % H->TableSize;
}
int NextPrime(int N)
{
	if (N == 1 || N % 2 == 0)
		N++;//偶数就加一
	int i;
	while (N <= 100000)//最大表大小为100000
	{
		for (i = 2; i * i <= N; i++)
			if (N % i == 0)
				break;
		if (i * i > N)
			return N;
		N += 2;
	}
	return N;
}
int Insert(HashTable H, int pos)//没位置false，有位置true
{
	if (H->heads[pos] == false)//该位置已经有元素了
	{
		int i, q;
		for (i = 1; i <= H->TableSize / 2; i++)
		{
			q = i * i;
			if (H->heads[(pos + q) % H->TableSize] == true)//该位置还没有元素,插入
			{
				H->heads[(pos + q) % H->TableSize] = false;
				return (pos + q) % H->TableSize;
			}
		}
		return -1;
	}
	else//该位置还没有元素
	{
		H->heads[pos] = false;
		return pos;
	}
}
int main()
{
	int MSize, N;
	scanf("%d%d", &MSize, &N);
	HashTable H = CreateTable(NextPrime(MSize));
	int pos, temp;
	//先输出第一个
	scanf("%d", &temp);
	pos = Hash(H, temp);
	Insert(H, pos);
	printf("%d", pos);
	while (--N)
	{
		printf(" ");
		scanf("%d", &temp);
		pos = Hash(H, temp);
		int result = Insert(H, pos);
		if (result < 0)
			printf("-");
		else
			printf("%d", result);
	}
}
/*
总结：对于开放地址法，如果元素只有一个或没有属性可以将哈希表视为一个数组，否则需要为元素建立结构体；
NextPrime需要判断1的边界条件
Insert函数视探测要求而定，对于需要取取两面的平方探测法，记住负数取余仍为负数，此外，如果根号增量已经大于表大小的一半，可以认为无法插入表中
*/