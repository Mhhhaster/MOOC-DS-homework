/*4 3 4 - 5 2  6 1 - 2 0
3 5 20 - 7 4  3 1
输出样例:
15 24 - 25 22 30 21 - 10 20 - 21 8 35 6 - 33 5 14 4 - 15 3 18 2 - 6 1
5 20 - 4 4 - 5 2 9 1 - 2 08*/
#include<iostream>
#include<vector>
using namespace std;
typedef struct PolyNode* Ptr;
struct PolyNode
{
	int expon;
	int coef;
};
void Print(vector<Ptr>P)
{
	printf("%d %d", P[0]->coef, P[0]->expon);
	for (int i = 1; i < P.size(); i++) 
		if(P[i]->coef)
			printf(" %d %d", P[i]->coef, P[i]->expon);
}
vector<Ptr> Add(vector<Ptr>P1, vector<Ptr>P2)
{
	int i = 0, j = 0, sum;
	vector<Ptr>AP;
	while (i < P1.size() && j < P2.size())
	{
		if (P1[i]->expon > P2[j]->expon)//P1所指大于P2
		{
			Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
			P->coef = P1[i]->coef;
			P->expon = P1[i]->expon;
			AP.push_back(P);
			i++;
		}
		else if (P1[i]->expon < P2[j]->expon)
		{
			Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
			P->coef = P2[j]->coef;
			P->expon = P2[j]->expon;
			AP.push_back(P);
			j++;
		}
		else
		{
			sum = P1[i]->coef + P2[j]->coef;
			if (sum)
			{
				Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
				P->coef = sum;
				P->expon = P2[j]->expon;
				AP.push_back(P);
			}//如果等于零就略过attach
			i++; j++;
		}
	}
	for (; i < P1.size(); i++)
	{
		Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
		P->coef = P1[i]->coef;
		P->expon = P1[i]->expon;
		AP.push_back(P);
	}
	for (; j < P2.size(); j++)
	{
		Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
		P->coef = P2[j]->coef;
		P->expon = P2[j]->expon;
		AP.push_back(P);
	}
	if (!AP.size())
	{
		Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
		P->coef = 0;
		P->expon = 0;
		AP.push_back(P);
	}
	return AP;
}
vector<Ptr> Multiply(vector<Ptr>P1, vector<Ptr>P2)
{
	vector<Ptr>MP;
	int i = 0;
	if (!P1[0]->coef || !P2[0]->coef)
	{
		Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
		P->coef = 0;
		P->expon = 0;
		MP.push_back(P);
		return MP;
	}
	else
	{
		while (i < P1.size())
		{
			vector<Ptr>temp;
			int j = 0;
			while (j < P2.size())
			{
				Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
				P->coef = P1[i]->coef*P2[j]->coef;
				P->expon = P1[i]->expon+P2[j]->expon;
				temp.push_back(P);
				j++;
			}
			MP = Add(MP, temp);
			i++;
		}
		return MP;
	}
}

int main()
{
	vector<Ptr>P1;//个人习惯，更喜欢操作指针类型,故用Ptr
	vector<Ptr>P2;
	int N1, N2;
	scanf("%d", &N1);
	int expon, coef;
	if (!N1)//边界
	{
		Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
		P->coef = 0;
		P->expon = 0;
		P1.push_back(P);
	}
	while (N1--)
	{
		scanf("%d%d", &coef, &expon);
		Ptr P = (Ptr)malloc(sizeof(struct PolyNode));//记得每次都要申请一块空间
		P->coef = coef;
		P->expon = expon;
		P1.push_back(P);
	}
	scanf("%d", &N2);
	if (!N2)
	{
		Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
		P->coef = 0;
		P->expon = 0;
		P2.push_back(P);
	}
	while (N2--)
	{
		scanf("%d%d", &coef, &expon);
		Ptr P = (Ptr)malloc(sizeof(struct PolyNode));
		P->coef = coef;
		P->expon = expon;
		P2.push_back(P);
	}
	Print(Multiply(P1, P2));
	printf("\n");
	Print(Add(P1, P2));
	return 0;
}