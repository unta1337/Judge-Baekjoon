#include <stdio.h>
#include <stdlib.h>

int comp(const void* p, const void* q)
{
	int i = ((int*)p)[1];
	int j = ((int*)q)[1];

	if (i < j) return -1;
	if (i > j) return 1;
	return 0;
}

int main()
{
	int arr[][2] = {
		{ 1, 9 },
		{ 2, 8 },
		{ 3, 7 },
		{ 4, 6 },
		{ 4, 5 },
		{ 6, 4 },
		{ 7, 3 },
		{ 8, 2 },
		{ 9, 1 },
	};

	for (int i = 0; i < 9; i++)
		printf("%d %d\n", arr[i][0], arr[i][1]);
	printf("\n\n");

	qsort(arr, 9, sizeof(int) * 2, comp);

	for (int i = 0; i < 9; i++)
		printf("%d %d\n", arr[i][0], arr[i][1]);
	printf("\n\n");

	return 0;
}
