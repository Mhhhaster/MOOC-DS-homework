#include <iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
int node[100002][2];
int main()
{
    int list[100002];
    int i;
    int st,k;
    int n;
    cin>>st>>n>>k;//������ʼ��ַ���ڵ����Լ���ת�ĳ���k
    for(i=0;i<n;i++){
        int add,data,next;
        cin>>add>>data>>next;//�����ַ�����ݡ��Լ���һ�ڵ�
        node[add][0]=data;//�����ά����
        node[add][1]=next;
    }
    int cnt=0;
    int cur=st;
    while(cur!=-1){
        list[cnt++]=cur;//list��˳��洢��һ����ַ 
        cur=node[cur][1];//����һ�ڵ��𽥲���
    }
    i=0;
    while(i+k<=cnt){
        reverse(list+i,list+i+k);//�Դ����� 
        i+=k;
    }//���� 
    for(i=0;i<cnt-1;i++){
        printf("%05d %d %05d\n",list[i],node[list[i]][0],list[i+1]);//����ĸ�ʽ�����%05dΪ������λ 
    }
    printf("%05d %d -1",list[i],node[list[i]][0]);
    return 0;
}

