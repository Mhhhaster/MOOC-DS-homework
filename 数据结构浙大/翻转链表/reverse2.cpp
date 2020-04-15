#include <stdlib.h>
#include <stdio.h>


typedef struct node {
	int Address;
	int Data;
	int Next;
}list;

void Array(list a[], int N, int headaddress);
void Exchange(list a[], int i, int j);
void Reverse(list a[], int N, int K);

int main(){
	int K, N, headaddress, eff;
	scanf("%d %d %d", &headaddress, &N, &K);
	list a[N];
	for (int i = 0; i<N; i++) {
		scanf("%d %d %d", &a[i].Address, &a[i].Data, &a[i].Next);
	}
	Array(a, N, headaddress);
	for (int i = 0; i<N; i++) {
		if (a[i].Next == -1) {
			eff = i + 1;//¼ÇÂ¼ÏÂÄ©Î²ĞòºÅ 
		}
	}
	Reverse(a, eff, K);
	for (int i = 0; i<eff; i++)	{
		a[i].Next = a[i + 1].Address;
		if (i == eff - 1) {
			a[i].Next = -1;
		}
	}
	for (int i = 0; i<eff - 1; i++) {
		printf("%05d %d %05d\n", a[i].Address, a[i].Data, a[i].Next);
	}
	printf("%05d %d %d\n", a[eff - 1].Address, a[eff - 1].Data, -1);
	return 0;
}


void Array(list a[], int N, int headaddress) {
	for (int i = 0; i<N; i++) {
		if (a[i].Address == headaddress) {
			Exchange(a, i, 0);
			break;
		}
	}
	for (int i = 0; i<N; i++) {
		for (int j = i + 1; j<N; j++) {
			if (a[i].Next == a[j].Address) {
				Exchange(a, i + 1, j);
				break;
			}
		}
	}
}


void Exchange(list a[], int i, int j) {
	list temp;
	temp.Address = a[j].Address;
	temp.Data = a[j].Data;
	temp.Next = a[j].Next;
	a[j].Address = a[i].Address;
	a[j].Data = a[i].Data;
	a[j].Next = a[i].Next;
	a[i].Address = temp.Address;
	a[i].Data = temp.Data;
	a[i].Next = temp.Next;
}

void Reverse(list a[], int N, int K) {
	int cnt = N / K;
	if (cnt) {
		for (int j = 1; j <= cnt; j++) {
			for (int i = 1; i <= K; i++) {
				if ((j - 1)*K + i - 1 <= j * K - i - 1) {
					Exchange(a, (j - 1)*K + i - 1, j*K - i);
				}
			}
		}
	}
}


