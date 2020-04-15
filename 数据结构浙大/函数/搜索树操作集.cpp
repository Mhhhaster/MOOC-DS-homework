#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};


BinTree Insert(BinTree BST, ElementType X)//��׼
{
    if (!BST)
    {
        BinTree T = (BinTree)malloc(sizeof(struct TNode));//Ҳ��ֱ��BST=malloc;
        T->Data = X;
        T->Left = NULL;
        T->Right = NULL;
        BST = T;
    }
    else {
        if (X > BST->Data)
            BST->Right = Insert(BST->Right, X);
        else
            BST->Left = Insert(BST->Left, X);
    }
    return BST;
}

Position Find(BinTree BST, ElementType X)//��׼
{
    if (!BST)
        return NULL;
    if ( X>BST->Data)
        return Find(BST->Right, X);
    else if ( X<BST->Data)
        return Find(BST->Left, X);
    else//˵���ҵ���
        return BST;
}
Position FindMin(BinTree BST)
{
    if(BST)
    if (BST->Left)
        return FindMin(BST->Left);
    else
        return BST;
}
Position FindMax(BinTree BST)
{
    if(BST)
    if (BST->Right)
        return FindMax(BST->Right);
    else
        return BST;
}
BinTree Delete(BinTree BST, ElementType X)//֮ǰû��һ��ʼ�Ͷ���temp��������else����ж��岢free��������
{
    BinTree temp;
    if (!BST)
        printf("Not Found\n");
    else
    {
        if (X > BST->Data)
            BST->Right = Delete(BST->Right, X);
        else if (X < BST->Data)
            BST->Left = Delete(BST->Left, X);
        else//�ҵ���ɾ��Ԫ�أ���Ϊ�����ڵ�����������ڵ�����
        {
            if (BST->Left && BST->Right)//����Ϊ��
            {
               temp = FindMin(BST->Right);
                BST->Data = temp->Data;
                BST->Right = Delete(BST->Right, BST->Data);
                //Ϊʲô���ﲻ��free temp,��Ϊ���ϸ�������Ѿ���free���ˣ�
            }
            else//���ٿ�һ��
            {
                temp = BST;
                if (!BST->Left)       /* ֻ���Һ��ӻ����ӽ�� */
                    BST = BST->Right;
                else                   /* ֻ������ */
                    BST = BST->Left;
                free(temp);
            }
        }
    }
    return BST;
}
int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:");  printf("\n");//��
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:");  printf("\n");

    return 0;
}
/* ��Ĵ��뽫��Ƕ������ */
/*����������
10
5 8 6 2 4 1 0 10 9 7
5
6 3 10 0 5
5
5 7 0 10 3
���������
Preorder: 5 2 1 0 4 8 6 7 10 9
6 is found
3 is not found
10 is found
10 is the largest key
0 is found
0 is the smallest key
5 is found
Not Found
Inorder: 1 2 4 6 8 9*/