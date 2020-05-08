#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 100000
#define address Next

typedef struct vector {
	int Data;
	int Next;
}list;
void swap(list b[], int i, int j)
 {
 	if(j>i)
	 {
	   
 	int temp_data=b[i].Data;
 	b[i].Data=b[j].Data;
 	b[j].Data=temp_data;
 	int temp_address=b[i].address;
 	b[i].address=b[j].address;
 	b[j].address=temp_address;
 	swap(b[],i+1,j-1);
 }
}
void Link(list a[],list b[],int firstadd,int N)//将数据按地址串好在b列表,包含数据和本身地址 
{
	int aimadd=firstadd;
	for(int i=0;i<N;i++)
	{
		b[i].Data=a[aimadd].Data;
		b[i].address=aimadd;
		aimadd=a[aimadd].Next;
	}
}
void Reverse(list b[],int K,int N)//程序将每K个翻转，只交换数组的data和address 
{
	int times=N/K;
	int i=0;
	while(times--)
	{
		swap(b[],i,i+K-1);
		i+=K;
	}	
}
void Output(list b[],int N)
{
	printf("%05d %d",b[0].address,b[0].Data);
	for(int i=1;i<N;i++)
	printf("%05d\n%05d %d",b[i].address,b[i].address,b[i].Data);
	printf("-1");
}
int main()
{
	int firstadd,K,N;
	int i=0;
	scanf("%d%d%d",&firstadd,&N,&K);
	list a[MAXSIZE];
	list b[N-1];
	int n=N;
	while(n--)//输入N次 
	{
		int add;
		scanf("%d",&add);
		scanf("%d%d",&a[add].Data,&a[add].Next);
	}
	Link(a[],b[],firstadd,N);//实现将a赋给b 
	Reverse(b[],K,N);//对b翻转 
	Output(b[],N);//输出b 
}
