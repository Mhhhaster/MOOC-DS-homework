#include<iostream>
#include<string>
#include<map>
using namespace std;
int main()
{
	int N;
	scanf("%d", &N);
	map<string, string>M;
	char c;
	string id, pw;
	while (N--)
	{
		cin >> c;
		cin >> id >> pw;
		auto it = M.find(id);
		if (c == 'L')
		{
			if (it == M.end())//没有找到账号
				cout << "ERROR: Not Exist" << endl;
			else
			{
				if (it->second == pw)//密码正确
					cout << "Login: OK" << endl;
				else//密码错误
					cout << "ERROR: Wrong PW" << endl;
			}
		}
		else if (c == 'N')
		{
			if (it == M.end())//没有找到账号，新建
			{
				cout << "New: OK" << endl;
				M.insert({ id, pw });//这里一定要注意insert的格式  insert({A,B})//小括号括大括号
			}
			else//找到了账号
				cout << "ERROR: Exist"<<endl;
		}
	}
	return 0;
}