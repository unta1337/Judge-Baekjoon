#include <stdio.h>
#include <stdlib.h>

int comp(const void* p, const void* q)
{
	int i = ((int*)p)[1];
	int j = ((int*)q)[1];

	return (i > j) - (i < j);
}

int get_max_value(int input[][2], int size, int number)
{
}

int main()
{
	//int input[100][2]; = { };
	int input[][2] = {
		{ 6, 13 },
		{ 4, 8 },
		{ 3, 6 },
		{ 5, 12 }
	};

	int n = 4;
	int max_weight = 7;
	//scanf("%d %d", &n, &max_weight);
	
	qsort(input, n, sizeof(int) * 2, comp);

	for (int i = 0; i < n; i++)
		printf("%d %d\n", input[i][0], input[i][1]);

	return 0;
}
