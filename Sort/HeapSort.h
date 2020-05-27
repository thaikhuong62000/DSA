#pragma once
#include <iostream>
using namespace std;

#ifndef HEAPSORT
#define HEAPSORT
void HeapDown(int* arr, int N, int i) {
	while (i < N) {
		int left = i * 2 + 1;
		if (left >= N) return;
		if (left + 1 < N)
			if (arr[left] < arr[left + 1]) left++;
		if (arr[i] >= arr[left])
			return;
		swap(arr[i], arr[left]);
		i = left;
	}
}

void BuildHeap(int* arr, int N) {
	for (int i = N / 2; i > -1; i--)
		HeapDown(arr, N, i);
}

void HeapSort(int* arr, int N) {
	int* arrTemp = new int[N];
	BuildHeap(arr, N);
	int HeapSize = N;
	for (int i = 0; i < N; i++)
	{
		arrTemp[N - 1 - i] = arr[0];
		arr[0] = arr[--HeapSize];
		HeapDown(arr, HeapSize, 0);
	}
	for (int i = 0; i < N; i++)
	{
		arr[i] = arrTemp[i];
	}
	delete[]arrTemp;
}

#endif // !HEAPSORT
