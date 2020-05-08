#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include<string>
#include<iostream>
using namespace std;
typedef int Position;
#define NotFound -1

void BuildMatch(string pattern, int* match)
{
    Position i, j;
    int m = pattern.length();
    match[0] = -1;//先给最初的位置设置初值
    for (j = 1; j < m; j++) {
        i = match[j - 1];//记录变量名
        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
            i = match[i];//回退
        if (pattern[i + 1] == pattern[j])
            match[j] = i + 1;
        else match[j] = -1;//循环退出条件为i=-1时，match也为1(找不到match串)
    }
}
Position KMP(string string1, string pattern)
{
    int n = string1.length();
    int m = pattern.length();
    Position s, p, * match;

    if (n < m) return NotFound;
    match = (Position*)malloc(sizeof(Position) * m);
    BuildMatch(pattern, match);
    s = p = 0;
    while (s < n && p < m) {//走完n或者m
        if (string1[s] == pattern[p]) {//匹配上的情况
            s++; p++;
        }
        else if (p > 0) p = match[p - 1] + 1;//匹配不上分为第一个匹配不上以及其他位置匹配不上
        else s++;//如果第一个匹配不上那么选择走n
    }
    return (p == m) ? (s - m) : NotFound;//走完了m就为匹配成功
}
int main()
{
    string purpose;
    cin >> purpose;
    int N;
    scanf("%d", &N);
    while (N--)
    {
        string module;
        cin >> module;
        Position p = KMP(purpose, module);
        if (p == NotFound) printf("Not Found\n");
        else
            printf("%s\n", purpose.c_str() + p);
    }
    return 0;
}
/*
结论：最方便的还是使用string类型，输入很方便，然后使用KMP算法获取int类型的position
const char* k = s.c_str();转换string类型为const char*，然后 printf("%s",k+position)即可
strcpy(ch, s.c_str());也可进一步转换为字符数组
*/