#include<iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;
int main()
{
	int N;
	scanf("%d", &N);
	map<string, int>Mmap;
	string name;
	N *= 2;
	while (N--)
	{
		cin >> name;
		auto it = Mmap.find(name);
		if (Mmap.end() == it)//这个元素没有出现过
			Mmap.insert({ name,1 });
		else
			it->second++;//按键大小排序，改变key值不影响
	}
	int maxcallnum = 0, same = 1;//分别记录最大的通话次数和相同次数的人
	auto M = Mmap.begin();//M指示通话次数最大的位置
	for (auto it = Mmap.begin(); it != Mmap.end(); it++)
	{
		if (it->second > maxcallnum)//更新最大通话次数
		{
			maxcallnum = it->second;
			M = it;
			same = 1;
		}
		else if (it->second == maxcallnum)
			same++;
	}
	cout << M->first << " " << M->second;
	if (same > 1)
		cout << " " << same;
}