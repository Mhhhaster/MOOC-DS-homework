/*�ܽ� strcmp��strcpy��Ҫ����ʹ�ã�����atoi�����ǴӴ���ĵ�ַ��ʼת��
�õ���
Create������nextprime,�������οռ估��ʼ����
find��ע�⿪ʼ���ҵ�λ�ú����ķ���ֵ��
Insert������find�����������)
destroy(����ڵ�������hashtable�ṹ��)
*/
#include<iostream>
#include<string.h>
#define Keylength 11
using namespace std;
typedef char ElementType[Keylength + 1];//�ַ�����β'\0\ռһ���ֽڣ�����ͬ��typedef string ElementType
typedef int Index;
//��ȫͬ������
typedef struct LNode* PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;//��ȫͬ������
typedef struct TblNode* HashTable;
struct TblNode {//������QNode
    int TableSize;
    List Heads;//TblNodeһ���ռ��ű��С��һ����LNodeͷָ��//������front��rear
};/*LNode=Node�٣�����ָ��ֱ�ΪList��front��rear�ڣ�
  �ֱ��¼��TblNode��QNode�ṹ���ͬʱ�ṹ���ָ��ֱ���HashTable��Queue��*/
int NextPrime(int N)//�ҵ���2*N�����С����
{
    int tablesize = 2 * N;
    if (tablesize % 2 == 0)
        tablesize++;//Ϊż���ͼ�1
    for (; tablesize < 210000; tablesize += 2)
    {
        for (int i = 2; i * i <= tablesize; i++)
        {
            if (tablesize % i == 0)//��������
                break;
            if (i * i >= tablesize)//Ϊ����
                return tablesize;
        }
    }
    return tablesize;
}
HashTable CreateTable(int N)//���ݴ�������N��������е�ɢ�б��С���ڽӴ����������飬��ÿ���ڵ㸳ֵ����������Ϊ'\0'��nextΪ��
{
    HashTable H;
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* ��֤ɢ�б���󳤶�������*/
    H->TableSize = NextPrime(N);
    /* ���·�������ͷ������� */
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));//����ģʽ
    /* ��ʼ����ͷ��� */
    for (int i = 0; i < H->TableSize; i++) {//��������
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
    Position P;//ָ������P
    Index Pos;//���������±�Pos
    Pos = Hash(atoi(Key + 6), H->TableSize); /* ��ʼɢ��λ�� */  //�ҵ���һ����ͷ
    P = H->Heads[Pos].Next; /* �Ӹ�����ĵ�1����㿪ʼ */
    /* ��δ����β������Keyδ�ҵ�ʱ */
    while (P && strcmp(P->Data, Key))//P�ǿ������߲���ȣ���ȥ��һ��
        P = P->Next;

    return P; //��ʱPҪô��ȣ�ҪôΪ�գ�Ϊ����insert���ж�
}
bool Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos;
    P = Find(H, Key);
    if (!P) { /* �ؼ���δ�ҵ������Բ��� */
        NewCell = (Position)malloc(sizeof(struct LNode));//����һ��LNode�ռ䡢��ֵ
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;
        Pos = Hash(atoi(Key + 6), H->TableSize); /* ��ʼɢ��λ�� */
        /* ��NewCell����ΪH->Heads[Pos]����ĵ�1����� */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else { /* �ؼ����Ѵ��� */
        P->Count++;
        return false;
    }
}
void DestroyTable(HashTable H)
{
    int i;
    Position P, Tmp;

    /* �ͷ�ÿ������Ľ�� */
    for (i = 0; i < H->TableSize; i++) {
        P = H->Heads[i].Next;
        while (P) {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads); /* ָ������ͷ���ͷ�ͷ������� */
    free(H);        /* ������ͷ��ͷ�ɢ�б��� */
}
void ScanOutput(HashTable H)
{
    int i, MaxCnt = 0, PCnt = 0;
    ElementType MinPhone;
    List Ptr;
    MinPhone[0] = '\0';
    for (i = 0; i < H->TableSize; i++) { /* ɨ������ */
        Ptr = H->Heads[i].Next;
        while (Ptr) {
            if (Ptr->Count > MaxCnt) { /* �������ͨ������ */
                MaxCnt = Ptr->Count;
                strcpy(MinPhone, Ptr->Data);
                PCnt = 1;
            }
            else if (Ptr->Count == MaxCnt) {
                PCnt++; /* ���˼��� */
                if (strcmp(MinPhone, Ptr->Data) > 0)
                    strcpy(MinPhone, Ptr->Data); /* ���¿��˵���С�ֻ����� */
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
    //����ɢ�б�
    //����
    //ɨ������
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
