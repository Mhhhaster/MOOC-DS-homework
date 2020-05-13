#include<iostream>
#include<stack>
using namespace std;
void Judge(int maxsize,int seqlength)
{
	int* a = (int* )malloc((seqlength+1) * sizeof(int));//������vector<int>a(seqlength+1);����
	stack<int>S;
	for (int i = 1; i <= seqlength; i++)
		cin >> a[i];
	int cur = 1;//ָʾ���к�
	for (int i = 1; i <= seqlength; i++) {//ģ���1��ʼ��ջ
		S.push(i);
		if (S.size() > maxsize)
			break;
		while (!S.empty() && S.top() == a[cur]) {//���S��Ϊ�ղ���������ջ��Ԫ����ͬ����pop
			S.pop();
			cur++;//ָ����һ��
		}
	}
	if (cur == seqlength+1)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}
int main()
{
	int M, N, K;
	scanf("%d%d%d", &M, &N, &K);
	while (K--)
		Judge(M,N);
	return 0;
}
//conclude���趨����������ִ�������кϷ��������ֵ�����жϡ�����������ж�����Υ����������㡣