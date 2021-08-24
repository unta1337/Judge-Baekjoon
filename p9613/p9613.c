// 9613: GCD 합
/*
 * n개의 수가 주어졌을 때, 가능한 모든 순서쌍의 최대공약수의 합을 구하여라.
 */
// https://www.acmicpc.net/problem/9613

#include <stdio.h>
#include <stdlib.h>

int euclideanAlgorithm(int p, int q);
int gcd(int p, int q);

int getSumOfGCDs(int* inputs, int size);

int main(void)
{
	int n;
	scanf("%d", &n);
	int** inputs = (int**)malloc(n * sizeof(int*));
	int* results = (int*)malloc(n * sizeof(int));
	int resultIndex = 0;

	for (int i = 0; i < n; i++)
	{
		int m;
		scanf("%d", &m);
		inputs[i] = (int*)malloc(m * sizeof(int));

		for (int j = 0; j < m; j++)
			scanf("%d", &inputs[i][j]);

		results[resultIndex++] = getSumOfGCDs(inputs[i], m);
	}

	for (int i = 0; i < n; i++)
		printf("%d\n", results[i]);

	for (int i = 0; i < n; i++)
		free(inputs[i]);
	free(inputs);

	return 0;
}

int euclideanAlgorithm(int p, int q)
{
	return p % q ? euclideanAlgorithm(q, (p % q)) : q;
}

int gcd(int p, int q)
{
	return p > q ? euclideanAlgorithm(p, q) : euclideanAlgorithm(q, p);
}

int getSumOfGCDs(int* inputs, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
			sum += gcd(inputs[i], inputs[j]);
	}

	return sum;
}
