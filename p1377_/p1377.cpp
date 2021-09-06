#include <iostream>

using namespace std;

int bubble_sort_ret(int A[], int N) {
	bool changed = false;
	for (int i=1; i<=N+1; i++) {
		changed = false;
		for (int j=1; j<=N-i; j++) {
			if (A[j] > A[j+1]) {
				changed = true;
				swap(A[j], A[j+1]);
			}
		}
		if (changed == false) {
			return i;
		}
	}

	return -1;
}

int main(void)
{
	int n;
	cin >> n;

	int *arr = new int[n];
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	cout << bubble_sort_ret(arr, n);

	return 0;
}
