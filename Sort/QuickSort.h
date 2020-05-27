#pragma once
using namespace std;

#ifndef QUICKSORT
#define QUICKSORT

void _QuickSort(int arr[], int begin, int N) {
	if (N < 2)
	{
		return;
	}
	int pivot = begin + N - 1;
	int numOfElement = N--;
	for (int i = 0; i < N; i++)
	{
		while (true)
		{
			if (arr[N + begin - 1] > arr[pivot])
			{
				--N;
			}
			else break;
		}
		if (i >= N)
		{
			break;
		}
		if (arr[i + begin] > arr[pivot])
		{
			int temp = arr[N + begin - 1];
			arr[N + begin - 1] = arr[i + begin];
			arr[i + begin] = temp;
			--N;
		}
	}
	int temp = arr[N + begin];
	arr[N + begin] = arr[pivot];
	arr[pivot] = temp;
	_QuickSort(arr, begin, N);
	_QuickSort(arr, begin + N + 1, numOfElement - N - 1);
}
void QuickSort(int arr[], int N) {
	_QuickSort(arr, 0, N);
}

#endif // !QUICKSORT
