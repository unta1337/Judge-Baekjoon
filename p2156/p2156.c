#include <stdio.h>
#include <stdlib.h>

int* _input;
int _n;
int _max;

void findMax(int current, int consec, int sum)
{
	if (current >= _n)
	{
		_max = _max > sum ? _max : sum;
		return;
	}

	if (current == -1)
	{
		findMax(0, 1, 0);
		findMax(1, 1, 0);
		return;
	}

	findMax(current + 2, 1, sum + _input[current]);
	if (consec < 2)
		findMax(current + 1, consec + 1, sum + _input[current]);
}

int main(void)
{
	scanf("%d", &_n);

	_input = (int*)malloc(_n * sizeof(int));
	for (int i = 0; i < _n; i++)
		scanf("%d", &_input[i]);

	findMax(-1, 1, 0);

	printf("%d\n", _max);

	return 0;
}
