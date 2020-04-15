#include<stdio.h>
int a = 0;
int fib(int k)
{
    a++;
    if (k == 1 || k == 2)
        return 1;
    else
        return fib(k - 1) + fib(k - 2);
    return a;
}
int main(void)
{
    int n;
    scanf("%d", &n);
    printf("%d\n", fib(n));
    printf("递归调用了%d次", a);
    return 0;
}