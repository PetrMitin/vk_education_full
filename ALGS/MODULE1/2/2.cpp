//Дан отсортированный массив различных целых чисел A[0..n - 1] и массив целых чисел B[0..m - 1].
//Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].n ≤ 110000, m ≤ 1000. 
//Время работы поиска для каждого элемента B[i]: O(log(k)).

#include <iostream>
#include <cmath>

// бинарный поиск в найденных границах
int binarySearch(const int* arr, int length, int leftBound, int rightBound, int value) {
	int leftSearchBound = leftBound;
	int rightSearchBound = rightBound;
	while (rightSearchBound - leftSearchBound > 1) {
		int middle = (rightSearchBound + leftSearchBound) / 2;
		if (value > arr[middle])
			leftSearchBound = middle;
		else
			rightSearchBound = middle;
	}
	if (std::abs(arr[leftSearchBound] - value) <= std::abs(arr[rightSearchBound] - value))
		return leftSearchBound;
	else
		return rightSearchBound;
}

// нахождение границ поиска, возврат результата бинарного поиска в этих границах для одного элемента
int findClosestIndex(const int* arr, int length, int value) {
	if (length == 1 || value <= arr[0]) return 0;
	if (value > arr[length - 1]) return length - 1;
	int leftBound = 0;
	int rightBound = 1;
	for (int i = 0; std::pow(2, i) < length; ++i) {
		if (value > arr[rightBound]) {
			leftBound = rightBound;
			rightBound = pow(2, i + 1);
		}
	}
	rightBound = std::min(length - 1, rightBound);
	return binarySearch(arr, length, leftBound, rightBound, value);
}

// вызов функции нахождения ближайшего индекса элемента из a для каждого элемента b, запись в result
void findClosestIndexesFromA(const int* a, const int* b, int* result, int lengthA, int lengthB) {
	for (int i = 0; i < lengthB; ++i)
		result[i] = findClosestIndex(a, lengthA, b[i]);
}

void getArray(int* arr, int length) {
	for (int i = 0; i < length; ++i)
		std::cin >> arr[i];
}

void printArray(int* arr, int length) {
	for (int i = 0; i < length; ++i)
		std::cout << arr[i] << ' ';
}

int main() {
	int lengthA;
	std::cin >> lengthA;
	int* a = new int[lengthA];
	getArray(a, lengthA);

	int lengthB;
	std::cin >> lengthB;
	int* b = new int[lengthB];
	getArray(b, lengthB);

	int* result = new int[lengthB];
	findClosestIndexesFromA(a, b, result, lengthA, lengthB);
	printArray(result, lengthB);

	delete[] a;
	delete[] b;
	delete[] result;

	return 0;
}