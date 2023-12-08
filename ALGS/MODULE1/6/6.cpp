// Реализуйте стратегию выбора опорного элемента “медиана трёх”. 
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

#include <iostream>
#include <cassert>

// выбор опорного элемента медиана трех
template<class T, class Compare=std::less<T>>
int medianIndex(const T* arr, int aIndex, int bIndex, int cIndex, Compare cmp=Compare()) {
	T a = arr[aIndex];
	T b = arr[bIndex];
	T c = arr[cIndex];
	if (cmp(b, a)) { // b < a
		if (cmp(a, c)) // a < c
			return aIndex;
		return cmp(c, b) ? bIndex : cIndex;
	}
	// a < b
	if (cmp(b, c)) // b < c
		return bIndex;
	return cmp(c, a) ? aIndex : cIndex; // c < a
}

template<class T, class Compare=std::less<T>>
int partition(T* arr, int left, int right, Compare cmp=Compare()) {
	int length = right - left;
	if (length < 2)
		return left;
	int pivotIndex = medianIndex(arr, left, right - 1, left + (right - left) / 2, cmp);
	// поставить опроный элемент в начало
	std::swap(arr[pivotIndex], arr[left]);
	T pivot = arr[left];
	int i = right;
	int j = right;
	// пока i не дошел до опорного элемента от конца массива и j < i
	while (i > left + 1 && i <= j) {
		--i;
		// если arr[i] > опорного элемента, сдвинуть участок с элементами меньше опорного влево, 
		// поменяв текущий элемент с самым правым из этого участка
		if (!cmp(arr[i], pivot))
			std::swap(arr[i], arr[--j]);
	}
	// поставить опорный элемент на свою позицию
	std::swap(arr[left], arr[--j]);
	return j;
}

template<class T, class Compare = std::less<T>>
T& findKStat(T* arr, int left, int right, int k, Compare cmp=Compare()) {
	assert(left <= right);
	// пока участок поиска не пустой
	while (left <= right) {
		if (left == right)
			return arr[left];
		int pivotIndex = partition(arr, left, right, cmp);
		if (k == pivotIndex)
			return arr[k];
		else if (k < pivotIndex)
			right = pivotIndex;
		else
			left = pivotIndex + 1;
	}
}

int main() {
	int length;
	std::cin >> length;
	int* arr = new int[length];
	for (int i = 0; i < length; ++i) {
		std::cin >> arr[i];
	}
	std::cout << findKStat(arr, 0, length, length / 10) << '\n';
	std::cout << findKStat(arr, 0, length, length / 2) << '\n';
	std::cout << findKStat(arr, 0, length, length * 9 / 10) << '\n';
	return 0;
}