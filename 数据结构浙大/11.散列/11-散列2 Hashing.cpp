//����q>TableSize/2ʱ����Ϊƽ��̽��ʧ��
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
		H->heads[i] = true;//true����ûԪ�ؿ��Բ���
	return H;
}
int Hash(HashTable H, int key)
{
	return key % H->TableSize;
}
int NextPrime(int N)
{
	if (N == 1 || N % 2 == 0)
		N++;//ż���ͼ�һ
	int i;
	while (N <= 100000)//�����СΪ100000
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
int Insert(HashTable H, int pos)//ûλ��false����λ��true
{
	if (H->heads[pos] == false)//��λ���Ѿ���Ԫ����
	{
		int i, q;
		for (i = 1; i <= H->TableSize / 2; i++)
		{
			q = i * i;
			if (H->heads[(pos + q) % H->TableSize] == true)//��λ�û�û��Ԫ��,����
			{
				H->heads[(pos + q) % H->TableSize] = false;
				return (pos + q) % H->TableSize;
			}
		}
		return -1;
	}
	else//��λ�û�û��Ԫ��
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
	//�������һ��
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
�ܽ᣺���ڿ��ŵ�ַ�������Ԫ��ֻ��һ����û�����Կ��Խ���ϣ����Ϊһ�����飬������ҪΪԪ�ؽ����ṹ�壻
NextPrime��Ҫ�ж�1�ı߽�����
Insert������̽��Ҫ�������������Ҫȡȡ�����ƽ��̽�ⷨ����ס����ȡ����Ϊ���������⣬������������Ѿ����ڱ��С��һ�룬������Ϊ�޷��������
*/