// 1003: 피보나치 함수
/*
 * 피보나치의 n번째 항을 계산하는 프로그램을 동적 계획법을 사용해 작성하시오.
 */
// https://www.acmicpc.net/problem/1003

#include <stdio.h>

int zero_count = 0;
int one_count = 0;
int fibonacci(int n);

int main(void)
{
	int n;
	scanf("%d", &n);

	fibonacci(n);

	printf("%d %d\n", zero_count, one_count);

	return 0;
}

int fibonacci(int n)
{
	if (n == 0)
	{
		//printf("0");
		zero_count++;
		return 0;
	}
	else if (n == 1)
	{
		//printf("1");
		one_count++;
		return 1;
	}
	else
	{
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}
