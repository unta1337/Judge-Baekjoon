#include <stdio.h>
#include <stdlib.h>

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

int dp_[10001] = { 665, 666 };

int dp__(int start, int n)
{
	int current = start;

	while (1)
	{
		int digits[20] = { };
		get_digits(current, digits);

		int six_count = six_in_a_row(digits, 20);
		if (six_count >= 3)
		{
			dp_[n] = current;
			break;
		}

		current++;
	}

	return current;
}

int dp(int n)
{
	if (dp_[n])
		return dp_[n];

	int index = n - 1;
	while (!dp_[index])
		index--;

	for (int i = index + 1; i <= n; i++)
		dp__(dp_[i - 1] + 1, i);

	return dp_[n];
}

int main(int argc, char* const argv[])
{
	int iteration = argc > 1 ? strtol(argv[1], NULL, 10) : 10000;

	for (int i = 1; i <= iteration; i++)
	{
		if (i % 100 == 0)
			printf("Non-DP[%d]: %d\n", i, non_dp(i));
	}

	for (int i = 1; i <= iteration; i++)
	{
		if (i % 100 == 0)
			printf("DP[%d]: %d\n", i, dp(i));
	}

	return 0;
}
