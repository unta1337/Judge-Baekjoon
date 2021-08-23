// 15727: 조별과제를 하려는데 조장이 사라졌다
/*
 * 도망친 조장 민건이의 거리가 주어졌을 때, 1분에 1-5의 거리를 갈 수 있는 성우가 민건이를 찾는 데 걸리는 최소 시간을 구하는 프로그램을 작성하시오.
 */
// URL: https://www.acmicpc.net/problem/15727

#include <stdio.h>

int getMinTime(int distance)
{
	return distance / 5 + (distance % 5 > 0);
}

int main(void)
{
	int distance;
	scanf("%d", &distance);

	printf("%d\n", getMinTime(distance));

	return 0;
}
