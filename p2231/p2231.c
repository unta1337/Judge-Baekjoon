// 2231: 분해합
/*
 * 어떤 자연수 n에 대한 생성자를 분해합을 이용해 구하여라.
 */
// https://www.acmicpc.net/problem/2231

// 메모리: 1116 KB
// 시간: 12 ms
// 코드 길이: 679 bytes
// http://boj.kr/910455735ebf4c6299a775f8b87f74c2

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

int get_decomposition(int number)
{
	for (int n = 0; n <= number; n++)
	{
		int digits[7] = { };
		get_digits(n, digits);

		int sum_of_digits = 0;
		for (int i = 0; i < 7; i++)
			sum_of_digits += digits[i];

		if (n + sum_of_digits == number)
			return n;
	}

	return 0;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	printf("%d\n", get_decomposition(n));

	return 0;
}
