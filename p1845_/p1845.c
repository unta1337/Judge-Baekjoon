#include <stdio.h>

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

int main(void)
{
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	int size = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");

	rotate_array(arr, size, 1, 4);

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");

	rotate_array(arr, size, 3, 5);

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}
