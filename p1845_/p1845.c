#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate_array(int arr[], int size, int start, int end)
{
	start--;
	end--;

	int condition1 = 0 <= start && start < size;
	int condition2 = 0 <= end && end < size;
	int condition3 = start <= end;
	if (!(condition1 && condition2 && condition3))
	{
		printf("rotate_array: invalied indices\n");
		return;
	}

	int range = (end - start + 1) / 2;
	for (int i = 0; i < range; i++)
	{
		int temp = arr[start + i];
		arr[start + i] = arr[end - i];
		arr[end - i] = temp;
	}

	for (int i = start; i <= end; i++)
		arr[i] *= -1;
}

int array_equal(int arr1[], int arr2[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr1[i] != arr2[i])
			return 0;
	}

	return 1;
}

void rec(int arr[], int size, int prev_move[], int depth)
{
	int target[] = { -4, -3, -5, 1, 2, 6 };
	if (array_equal(arr, target, size))
	{
		printf("rec depth %d\n", depth);
		for (int i = 0; i < size; i++)
			printf("%d ", arr[i]);
		printf("\n");

		return;
	}

	if (depth == 3)
		return;

	for (int i = 1; i <= size; i++)
	{
		for (int j = i; j <= size; j++)
		{
			int* new_arr = (int*)malloc(size * sizeof(int));
			memcpy(new_arr, arr, size * sizeof(int));

			rotate_array(new_arr, size, i, j);

			rec(new_arr, size, prev_move, depth + 1);

			free(new_arr);
		}
	}
}

int main(void)
{
	int arr[250];
	for (int i = 0; i < 250; i++)
		arr[i] = i + 1;

	int size;
	scanf("%d", &size);
	
	int prev_move[2] = { };

	rec(arr, size, prev_move, 0);

	return 0;
}
