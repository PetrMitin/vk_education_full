//Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
//Требования: время работы O(N* logK).Ограничение на размер кучи O(K).

#include <iostream>

template <class T, class Compare=std::less<T>>
class Heap {
public:
	explicit Heap(Compare _cmp=Compare());
	explicit Heap(const T* _arr, size_t _size, Compare _cmp=Compare());
	~Heap();
	// правило трех
	Heap(Heap<T, Compare>& _other) = delete;
	Heap<T, Compare>& operator=(Heap<T, Compare> const& _other) = delete;

	void add(const T& element);
	T extract();
	T peek() const;
	size_t size() { return length; };
	void printBuffer() {
		for (int i = 0; i < length; i++)
			std::cout << buffer[i] << ' ';
	}

private:
	Compare cmp;
	T* buffer;
	size_t bufferSize;
	size_t length;
	const size_t MIN_SIZE = 29;

	void grow();
	void siftDown(int index);
	void siftUp(int index);
};

template <class T, class Compare>
Heap<T, Compare>::Heap(Compare _cmp) : cmp(_cmp), buffer(nullptr), bufferSize(0), length(0) {}

// построение кучи за O(n)
template <class T, class Compare>
Heap<T, Compare>::Heap(const T* _arr, size_t _size, Compare _cmp) : cmp(_cmp), bufferSize(std::max(_size, MIN_SIZE)), length(_size) {
	buffer = new T[bufferSize];
	std::copy(_arr, _arr + length, buffer);
	for (int i = (length / 2 - 1); i >= 0; --i)
		siftDown(i);
}

template <class T, class Compare>
Heap<T, Compare>::~Heap() {
	delete[] buffer;
}

template <class T, class Compare>
void Heap<T, Compare>::grow() {
	size_t newBufferSize = std::max(length * 2, MIN_SIZE);
	T* newBuffer = new T[newBufferSize];
	std::copy(buffer, buffer + length, newBuffer);
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
}

template <class T, class Compare>
void Heap<T, Compare>::siftDown(int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int largest = index;
	if (left < length && !cmp(buffer[left], buffer[index]))
		largest = left;
	if (right < length && !cmp(buffer[right], buffer[largest]))
		largest = right;
	if (largest != index) {
		std::swap(buffer[index], buffer[largest]);
		siftDown(largest);
	}
}

template <class T, class Compare>
void Heap<T, Compare>::siftUp(int index) {
	while (index > 0) {
		int parent = (index - 1) / 2;
		if (cmp(buffer[index], buffer[parent])) return;
		std::swap(buffer[index], buffer[parent]);
		index = parent;
	}
}

template <class T, class Compare>
void Heap<T, Compare>::add(const T& element) {
	if (length == bufferSize)
		grow();
	// добавить элемент в конец и просеять вверх
	buffer[length] = element;
	++length;
	siftUp(length - 1);
}

template <class T, class Compare>
T Heap<T, Compare>::extract() {
	T maxValue = buffer[0];
	// поставить на место корневого элемента последний
	buffer[0] = buffer[--length];
	siftDown(0);
	return maxValue;
}

template <class T, class Compare>
T Heap<T, Compare>::peek() const {
	return buffer[0];
}

struct ElementData {
	ElementData(int _arrayIndex=-1, int _valueIndex=-1, int _value=0) : arrayIndex(_arrayIndex), valueIndex(_valueIndex), value(_value) {}
	int arrayIndex;
	int valueIndex;
	int value;
};

class IsMoreByValue {
public:
	bool operator()(const ElementData& l, const ElementData& r) { return l.value > r.value; }
};

void solve(int** arrays, int n, int k, const int* lengths) {
	Heap<ElementData, IsMoreByValue> minHeap;
	for (int i = 0; i < k; ++i)
		minHeap.add(ElementData(i, 0, arrays[i][0]));
	ElementData currMin;
	for (int i = 0; i < n; ++i) {
		currMin = minHeap.extract();
		std::cout << currMin.value << ' ';
		// если извлечен не последний элемент массива, добавить в кучу следующий элемент того же массива
		if ((currMin.valueIndex + 1) < lengths[currMin.arrayIndex]) {
			int newValueIndex = currMin.valueIndex + 1;
			ElementData newElement = ElementData(currMin.arrayIndex, newValueIndex, arrays[currMin.arrayIndex][newValueIndex]);
			minHeap.add(newElement);
		}
	}
}

int main() {
	int k;
	std::cin >> k;
	int* lengths = new int[k];
	int** arrays = new int* [k];
	int n = 0;
	for (int i = 0; i < k; ++i) {
		int curr_length;
		std::cin >> curr_length;
		lengths[i] = curr_length;
		n += curr_length;
		arrays[i] = new int[curr_length];
		for (int j = 0; j < curr_length; ++j) {
			int value;
			std::cin >> value;
			arrays[i][j] = value;
		}
	}
	solve(arrays, n, k, lengths);
	delete[] lengths;
	for (int i = 0; i < k; ++i) {
		delete[] arrays[i];
	}
	delete[] arrays;
	return 0;
}