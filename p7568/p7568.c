// 7568: 덩치
/*
 * n명의 몸무게와 키가 주어졌을 때, 각 사람의 덩치 순위를 구하여라.
 */
// https://www.acmicpc.net/problem/7568

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 683 bytes
// http://boj.kr/e59cc31fc8274c1a8c557a21268b3b81

#include <stdio.h>

int is_smaller(int A[], int B[])
{
	if ((A[0] < B[0]) && (A[1] < B[1]))
		return 1;

	return 0;
}

int get_place(int target[], int data[][2], int size)
{
	int lose_count = 0;
	for (int i = 0; i < size; i++)
		lose_count += is_smaller(target, data[i]);

	return lose_count + 1;
}

int main(void)
{
	int data[50][2];

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &data[i][0], &data[i][1]);

	for (int i = 0; i < n; i++)
		printf("%d\n", get_place(data[i], data, n));

	return 0;
}
