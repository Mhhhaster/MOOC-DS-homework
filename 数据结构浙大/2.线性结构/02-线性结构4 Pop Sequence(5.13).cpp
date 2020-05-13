#include<iostream>
#include<stack>
using namespace std;
void Judge(int maxsize,int seqlength)
{
	int* a = (int* )malloc((seqlength+1) * sizeof(int));//可以用vector<int>a(seqlength+1);代替
	stack<int>S;
	for (int i = 1; i <= seqlength; i++)
		cin >> a[i];
	int cur = 1;//指示序列号
	for (int i = 1; i <= seqlength; i++) {//模拟从1开始进栈
		S.push(i);
		if (S.size() > maxsize)
			break;
		while (!S.empty() && S.top() == a[cur]) {//如果S不为空并且序列与栈顶元素相同，该pop
			S.pop();
			cur++;//指向下一个
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
//conclude：设定计数器，当执行完所有合法操作后对值进行判断。做法相对于判断所有违法操作更简便。