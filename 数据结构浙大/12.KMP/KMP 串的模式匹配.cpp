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
    match[0] = -1;//�ȸ������λ�����ó�ֵ
    for (j = 1; j < m; j++) {
        i = match[j - 1];//��¼������
        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
            i = match[i];//����
        if (pattern[i + 1] == pattern[j])
            match[j] = i + 1;
        else match[j] = -1;//ѭ���˳�����Ϊi=-1ʱ��matchҲΪ1(�Ҳ���match��)
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
    while (s < n && p < m) {//����n����m
        if (string1[s] == pattern[p]) {//ƥ���ϵ����
            s++; p++;
        }
        else if (p > 0) p = match[p - 1] + 1;//ƥ�䲻�Ϸ�Ϊ��һ��ƥ�䲻���Լ�����λ��ƥ�䲻��
        else s++;//�����һ��ƥ�䲻����ôѡ����n
    }
    return (p == m) ? (s - m) : NotFound;//������m��Ϊƥ��ɹ�
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
���ۣ����Ļ���ʹ��string���ͣ�����ܷ��㣬Ȼ��ʹ��KMP�㷨��ȡint���͵�position
const char* k = s.c_str();ת��string����Ϊconst char*��Ȼ�� printf("%s",k+position)����
strcpy(ch, s.c_str());Ҳ�ɽ�һ��ת��Ϊ�ַ�����
*/