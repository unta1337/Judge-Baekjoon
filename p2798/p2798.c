// 2798: 블랙잭
/*
 * 숫자 n과 숫자들에 대해서, 숫자들 중 세 개를 뽑아 더한 값이 n에 가장 가까우면서 크지 않은 수를 구하여라.
 */
// https://www.acmicpc.net/problem/2798

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 946 bytes
// http://boj.kr/dbd0efc0219b412ca1be1f396fc4a8a5

#include <stdio.h>
#include <limits.h>

int get_closest_sum(int arr[], int size, int target)
{
	int closest_sum = 0;
	int diff = INT_MAX;

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			for (int k = j + 1; k < size; k++)
			{
				int sum = arr[i] + arr[j] + arr[k];
				int diff_local = target - sum;

				if (diff_local < 0)
					continue;

				closest_sum = diff_local < diff ? sum : closest_sum;
				diff = diff_local < diff ? diff_local : diff;
			}
		}
	}

	return closest_sum;
}

int main(void)
{
	int n, target;
	int inputs[100] = { 0 };
	scanf("%d %d", &n, &target);
	for (int i = 0; i < n; i++)
		scanf("%d", &inputs[i]);

	printf("%d\n", get_closest_sum(inputs, n, target));

	return 0;
}
