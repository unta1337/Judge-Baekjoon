#include <stdio.h>

int dp[10000] = { 665, 666 };

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

int non_dp(int n)
{
	int count = 0;
	int six_count = 0;
	int name = 0;

	for (int i = 666; count < n; i++)
	{
		int digits[20] = { };
		get_digits(i, digits);

		six_count = six_in_a_row(digits, 20);
		if (six_count >= 3)
		{
			name = i;
			count++;
		}
	}

	return name;
}

int dp_1(int start, int n)
{
	int current = start;

	while (1)
	{
		int digits[20] = { };
		get_digits(current, digits);

		int six_count = six_in_a_row(digits, 20);
		if (six_count >= 3)
		{
			dp[n] = dp[n] ? dp[n] : current;
			break;
		}

		current++;
	}

	return current;
}

int dp_2(int n)
{
	if (dp[n])
		return dp[n];

	int index = n - 1;
	while (!dp[index])
		index--;

	for (int i = index + 1; i <= n; i++)
		dp_1(dp[i - 1] + 1, i);

	return dp[n];
}

int main(void)
{
	for (int i = 1; i < 10000; i++)
	{
		int a = non_dp(i);
		int b = dp_2(i);
		if (a != b || i % 100 == 0)
			printf("%d %d %d %d\n", i, a, b, a ==b);
	}
	printf("done!\n");
	return 0;
}
