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
    cin>>st>>n>>k;//输入起始地址、节点数以及反转的长度k
    for(i=0;i<n;i++){
        int add,data,next;
        cin>>add>>data>>next;//输入地址、数据、以及下一节点
        node[add][0]=data;//存入二维数组
        node[add][1]=next;
    }
    int cnt=0;
    int cur=st;
    while(cur!=-1){
        list[cnt++]=cur;//list按顺序存储下一跳地址 
        cur=node[cur][1];//将下一节点逐渐插入
    }
    i=0;
    while(i+k<=cnt){
        reverse(list+i,list+i+k);//自带函数 
        i+=k;
    }//倒序 
    for(i=0;i<cnt-1;i++){
        printf("%05d %d %05d\n",list[i],node[list[i]][0],list[i+1]);//这里的格式化输出%05d为补足五位 
    }
    printf("%05d %d -1",list[i],node[list[i]][0]);
    return 0;
}

