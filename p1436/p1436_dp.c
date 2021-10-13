// 1436: 영화감독 숌
/*
 * 종말의 숫자로 지은 영화 이름을 구하여라.
 */
// https://www.acmicpc.net/problem/1436

#include <stdio.h>

void get_digits(int number, int digits[])
{
	int index = 0;
	while (number > 0)
	{
		digits[index++] = number % 10;
		number /= 10;
	}
}

int six_in_a_row(int digits[], int size)
{
	int max_count = 0;

	int six_count = 0;
	for (int i = 0; i < size; i++)
	{
		if (digits[i] == 6)
			six_count++;
		else
		{
			max_count = six_count > max_count ? six_count : max_count;
			six_count = 0;
		}
	}

	return max_count;
}

int dp[10001] = { 665, 666 };

int get_movie_name_loop(int start, int n)
{
	int current = start;

	while (1)
	{
		int digits[20] = { };
		get_digits(current, digits);

		int six_count = six_in_a_row(digits, 20);
		if (six_count >= 3)
		{
			dp[n] = current;
			break;
		}

		current++;
	}

	return current;
}

int get_movie_name(int n)
{
	if (dp[n])
		return dp[n];

	int index = n - 1;
	while (!dp[index])
		index--;

	for (int i = index + 1; i <= n; i++)
		get_movie_name_loop(dp[i - 1] + 1, i);

	return dp[n];
}

int main(void)
{
	int n;
	scanf("%d", &n);

	printf("%d\n", get_movie_name(n));

	return 0;
}
