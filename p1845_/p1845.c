#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack
{
	int** arr;
	int size;
	int index;

	void (*push)(struct Stack* this, int value[]);
	void (*pop)(struct Stack* this, int dest[]);
} Stack;

void Stack_push(Stack* this, int value[])
{
	if (this->index == this->size)
	{
		this->size *= 2;
		this->arr = (int**)realloc(this->arr, this->size * sizeof(int*));
	}

	this->arr[this->index++] = (int*)malloc(2 * sizeof(int));
	this->arr[this->index - 1][0] = value[0];
	this->arr[this->index - 1][1] = value[1];
}

void Stack_pop(Stack* this, int dest[])
{
	if (this->index == 0)
		return;

	if (this->index == this->size / 2)
	{
		this->size /= 2;
		this->arr = (int**)realloc(this->arr, this->size * sizeof(int*));
	}

	dest[0] = this->arr[--this->index][0];
	dest[1] = this->arr[this->index][1];

	free(this->arr[this->index]);
}

Stack* create_stack()
{
	Stack* this = (Stack*)malloc(sizeof(Stack));

	this->arr = (int**)malloc(sizeof(int*));
	this->size = 1;
	this->index = 0;

	this->push = &Stack_push;
	this->pop = &Stack_pop;

	return this;
}

void delete_stack(Stack* this)
{
	for (int i = 0; i < this->index; i++)
		free(this->arr[i]);
	free(this->arr);
	free(this);
}

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

void rec(int arr[], int size, int depth)
{
	int target[] = { -4, -3, -5, 1, 2, 6 };
	if (array_equal(arr, target, size))
	{
		//printf("rec depth %d\n", depth);
		//for (int i = 0; i < size; i++)
			//printf("%d ", arr[i]);
		//printf("\n");

		return;
	}

	if (depth == 5)
		return;

	for (int i = 1; i <= size; i++)
	{
		for (int j = i; j <= size; j++)
		{
			int* new_arr = (int*)malloc(size * sizeof(int));
			memcpy(new_arr, arr, size * sizeof(int));

			rotate_array(new_arr, size, i, j);

			rec(new_arr, size, depth + 1);

			free(new_arr);
		}
	}
}

int main(void)
{
	return 0;
}
