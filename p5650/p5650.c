// 5650: Software License
/*
 * 어떤 소프트웨어의 초기 비용과 이자가 주어졌을 때, 해당 소프트웨어를 가장 저렴하게 구매할 수 있는 가격을 구하여라.
 */
// https://www.acmicpc.net/problem/5650

#include <stdio.h>

typedef struct Software_license
{
	double current_price;
	double delta_price;
	double regulation;
	int doesItCount;
} Software_license;

double get_delta_p(Software_license* sl)
{
	return sl->delta_price = sl->current_price * (sl->regulation - 1);
}

void raise_price(Software_license* sl)
{
	sl->current_price += sl->delta_price;
}

int get_max_delta_index(Software_license sl[], int size)
{
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (!sl[i].doesItCount)
			continue;

		if (sl[i].delta_price > sl[max].delta_price)
			max = i;
	}

	return max;
}

void raise_step(Software_license sl[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!sl[i].doesItCount)
			continue;

		get_delta_p(&sl[i]);
	}

	int max_index = get_max_delta_index(sl, size);

	for (int i = 0; i < size; i++)
	{
		if (!sl[i].doesItCount)
			continue;

		if (i == max_index)
		{
			sl[i].doesItCount = 0;
			sl[i].delta_price = 0;
			continue;
		}

		raise_price(&sl[i]);

	}
}

void raise_all_step(Software_license sl[], int size)
{
	for (int i = 0; i < size; i++)
		raise_step(sl, size);
}

double get_total_price(Software_license sl[], int size)
{
	double sum = 0.0;

	for (int i = 0; i < size; i++)
		sum += sl[i].current_price;

	return sum;
}

int main(void)
{
	Software_license sl[100];

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%lf %lf", &sl[i].current_price, &sl[i].regulation);
		sl[i].delta_price = 0;
		sl[i].doesItCount = 1;
	}

	raise_all_step(sl, n);

	printf("%.2lf", get_total_price(sl, n));

	return 0;
}
