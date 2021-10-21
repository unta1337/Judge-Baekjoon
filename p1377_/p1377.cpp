#include <iostream>

using namespace std;

int bubble_sort_ret(int arr[], int size)
{
	int target = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > target)
			return target;

		target = arr[i];
	}

	return -1;
}

int main(void)
{
	int n;
	cin >> n;

	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	cout << bubble_sort_ret(arr, n);

	delete[] arr;

	return 0;
}
