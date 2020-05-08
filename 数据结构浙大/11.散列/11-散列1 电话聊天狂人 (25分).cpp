/*总结 strcmp，strcpy需要熟练使用，还有atoi函数是从传入的地址开始转换
用到了
Create（调用nextprime,分配两次空间及初始化）
find（注意开始查找的位置和最后的返回值）
Insert（调用find函数，分情况)
destroy(链表节点→数组→hashtable结构体)
*/
#include<iostream>
#include<string.h>
#define Keylength 11
using namespace std;
typedef char ElementType[Keylength + 1];//字符串结尾'\0\占一个字节，不等同于typedef string ElementType
typedef int Index;
//完全同单链表
typedef struct LNode* PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;//完全同单链表
typedef struct TblNode* HashTable;
struct TblNode {//类似于QNode
    int TableSize;
    List Heads;//TblNode一个空间存放表大小，一个是LNode头指针//类似于front和rear
};/*LNode=Node①，它们指针分别为List和front、rear②，
  分别记录在TblNode和QNode结构体里，同时结构体的指针分别是HashTable和Queue③*/
int NextPrime(int N)//找到比2*N大的最小素数
{
    int tablesize = 2 * N;
    if (tablesize % 2 == 0)
        tablesize++;//为偶数就加1
    for (; tablesize < 210000; tablesize += 2)
    {
        for (int i = 2; i * i <= tablesize; i++)
        {
            if (tablesize % i == 0)//不是素数
                break;
            if (i * i >= tablesize)//为素数
                return tablesize;
        }
    }
    return tablesize;
}
HashTable CreateTable(int N)//根据传进来的N计算出该有的散列表大小，邻接创造链表数组，对每个节点赋值：所有数据为'\0'，next为空
{
    HashTable H;
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* 保证散列表最大长度是素数*/
    H->TableSize = NextPrime(N);
    /* 以下分配链表头结点数组 */
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));//数组模式
    /* 初始化表头结点 */
    for (int i = 0; i < H->TableSize; i++) {//链表类型
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Next = NULL;
        H->Heads[i].Count = 0;
    }
    return H;
}
int Hash(int key, int tablesize)
{
    return key % tablesize;
}
Position Find(HashTable H, ElementType Key)
{
    Position P;//指针类型P
    Index Pos;//整数数组下表Pos
    Pos = Hash(atoi(Key + 6), H->TableSize); /* 初始散列位置 */  //找到这一链表头
    P = H->Heads[Pos].Next; /* 从该链表的第1个结点开始 */
    /* 当未到表尾，并且Key未找到时 */
    while (P && strcmp(P->Data, Key))//P非空且两者不相等，就去下一个
        P = P->Next;

    return P; //此时P要么相等，要么为空（为空在insert再判断
}
bool Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos;
    P = Find(H, Key);
    if (!P) { /* 关键词未找到，可以插入 */
        NewCell = (Position)malloc(sizeof(struct LNode));//分配一个LNode空间、赋值
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;
        Pos = Hash(atoi(Key + 6), H->TableSize); /* 初始散列位置 */
        /* 将NewCell插入为H->Heads[Pos]链表的第1个结点 */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else { /* 关键词已存在 */
        P->Count++;
        return false;
    }
}
void DestroyTable(HashTable H)
{
    int i;
    Position P, Tmp;

    /* 释放每个链表的结点 */
    for (i = 0; i < H->TableSize; i++) {
        P = H->Heads[i].Next;
        while (P) {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads); /* 指向数组头即释放头结点数组 */
    free(H);        /* 最后再释放释放散列表结点 */
}
void ScanOutput(HashTable H)
{
    int i, MaxCnt = 0, PCnt = 0;
    ElementType MinPhone;
    List Ptr;
    MinPhone[0] = '\0';
    for (i = 0; i < H->TableSize; i++) { /* 扫描链表 */
        Ptr = H->Heads[i].Next;
        while (Ptr) {
            if (Ptr->Count > MaxCnt) { /* 更新最大通话次数 */
                MaxCnt = Ptr->Count;
                strcpy(MinPhone, Ptr->Data);
                PCnt = 1;
            }
            else if (Ptr->Count == MaxCnt) {
                PCnt++; /* 狂人计数 */
                if (strcmp(MinPhone, Ptr->Data) > 0)
                    strcpy(MinPhone, Ptr->Data); /* 更新狂人的最小手机号码 */
            }
            Ptr = Ptr->Next;
        }
    }
    printf("%s %d", MinPhone, MaxCnt);
    if (PCnt > 1) printf(" %d", PCnt);
    printf("\n");
}
int main()
{
    //创建散列表
    //读入
    //扫描表并输出
    int N;
    scanf("%d", &N);
    HashTable H;
    H = CreateTable(N);
    ElementType Key;
    while (N--)
    {
        cin >> Key;
        Insert(H, Key);
        cin >> Key;
        Insert(H, Key);
    }
    ScanOutput(H);
    DestroyTable(H);
    return 0;
}
