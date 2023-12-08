//На числовой прямой окрасили N отрезков.Известны координаты левого и правого концов каждого отрезка(Li и Ri). 
//Найти длину окрашенной части числовой прямой.

#include <iostream>

template <class T, class Compare=std::less<T>>
void Merge(T* left, int leftLength, T* right, int rightLength, T* arr, Compare cmp=Compare()) {
	int i = 0, j = 0, k = 0;
	// пока не пройден полностью хотя бы один массив
	while (i < leftLength && j < rightLength) {
		if (cmp(left[i], right[j]))
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	// пока не пройден left
	while (i < leftLength)
		arr[k++] = left[i++];
	// пока не пройден right
	while (j < rightLength)
		arr[k++] = right[j++];
}

template <class T, class Compare=std::less<T>>
void MergeSort(T* arr, int length, Compare cmp=Compare()) {
	if (length < 2) {
		return;
	}
	int firstLen = length / 2;
	int secondLen = length - firstLen;
	MergeSort(arr, firstLen, cmp);
	MergeSort(arr + firstLen, secondLen, cmp);
	// массив для результата слияния
	T* temp = new T[length];
	Merge(arr, firstLen, arr + firstLen, secondLen, temp, cmp);
	std::copy(temp, temp + length, arr);
	delete[] temp;
}

struct Coordinate {
	Coordinate(int _value=0, int _flag=0) : value(_value), flag(_flag) {}
	int value;
	// 1 - если начало покрашенного отрезка, -1 - если конец
	int flag;
};

bool IsLessByValue(const Coordinate& l, const Coordinate& r) {
	// если значения координаты равны, считать элемент с флагом -1 меньшим
	if (l.value == r.value)
		return l.flag == -1;
	return l.value < r.value;
}

void solve(Coordinate* arr, int length) {
	if (length < 2) 
		return;
	int result = 0;
	// сортировать по координате
	MergeSort(arr, length, IsLessByValue);
	// метод сканирующей прямой, d currState - во сколько слоев в данный момент покрашена прямая
	int currState = arr[0].flag;
	int prevValue = arr[0].value;
	for (int i = 1; i < length; ++i) {
		if (currState > 0)
			result += arr[i].value - prevValue;
		currState += arr[i].flag;
		prevValue = arr[i].value;
	}
	std::cout << result;
}

int main() {
	int n;
	std::cin >> n;
	Coordinate* arr = new Coordinate[n * 2];
	for (int i = 0; i < 2 * n; i += 2) {
		int l, r;
		std::cin >> l >> r;
		arr[i] = { l, 1 };
		arr[i + 1] = { r, -1 };
	}
	solve(arr, n * 2);
	return 0;
}