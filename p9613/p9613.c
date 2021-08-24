// 9613: GCD 합
/*
 * n개의 수가 주어졌을 때, 가능한 모든 순서쌍의 최대공약수의 합을 구하여라.
 */
// https://www.acmicpc.net/problem/9613

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 941 bytes
// http://boj.kr/711596d34e3b4801a83391b969679f09

#include <stdio.h>
#include <stdlib.h>

int gcdRec(int p, int q);
int gcd(int p, int q);

int main(void)
{
	int n;
	scanf("%d", &n);
	long long* results = (long long*)malloc(n * sizeof(long long));

	for (int i = 0; i < n; i++)
	{
		int m;
		scanf("%d", &m);
		int* inputs = (int*)malloc(m * sizeof(int));

		for (int j = 0; j < m; j++)
			scanf("%d", &inputs[j]);

		long long sum = 0;
		for (int j = 0; j < m; j++)
		{
			for (int k = j + 1; k < m; k++)
				sum += gcd(inputs[j], inputs[k]);
		}
		results[i] = sum;

		free(inputs);
	}

	for (int i = 0; i < n; i++)
		printf("%lld\n", results[i]);

	free(results);

	return 0;
}

int gcdRec(int p, int q)
{
	return p % q ? gcdRec(q, p % q) : q;
}

int gcd(int p, int q)
{
	return p > q ? gcdRec(p, q) : gcdRec(q, p);
}