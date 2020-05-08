#include<iostream>
#include<stdlib.h>
using namespace std;
int a[51];
int main()
{
    int N;
    scanf("%d",&N);
    int age;
    while(N--)
    {
        scanf("%d",&age);
        a[age]++;
    }
    for(int i=0;i<51;i++)
    {
        if(a[i])
        {
            printf("%d:%d\n",i,a[i]);
        }
    }
    return 0;
}