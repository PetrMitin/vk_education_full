//Реализовать дек с динамическим зацикленным буфером(на основе динамического массива).

#include <iostream>
#include <cassert>

class Deque {
public:
	explicit Deque() : size(0), length(0), head(-1), tail(-1), buffer(nullptr) {}

	~Deque();

	Deque(Deque& _other) = delete;

	Deque& operator=(Deque const& _other) = delete;

	void pushFront(long value);

	long popFront();

	void pushBack(long value);

	long popBack();

	long getLength() const;

protected:
	// минимальное количество элементов, под которые будет выделена память
	const unsigned int minSize = 7;
	// размер буфера
	long size;
	// количество элементов
	long length;
	long head;
	long tail;
	long* buffer;

	void grow();
};

Deque::~Deque() {
	delete[] buffer;
}

void Deque::grow() {
	long newSize = std::max(long(minSize), size * 2);
	long* newBuffer = new long[newSize];
	// если не первая инициализация буфера
	if (buffer != nullptr) {
		// если порядок элементов в циклическом массиве соответствует реальному порядку элементов
		if (head == 0 && tail == size - 1)
			std::copy(buffer, buffer + size, newBuffer);
		else {
			// копировать от head до конца массива
			std::copy(buffer + head, buffer + size, newBuffer);
			// копировать от начала массива до tail
			std::copy(buffer, buffer + tail + 1, newBuffer + size - (tail + 1));
			head = 0;
			tail = size - 1;
		}
		delete[] buffer;
	}
	size = newSize;
	buffer = newBuffer;
}

void Deque::pushFront(long value) {
	if (length == size) {
		grow();
	}
	// если head выйдет за левую границу массива, зациклить массив
	if (--head == -1)
		head = size - 1;
	// если в массиве не было элементов
	if (head == -1 || tail == -1) {
		head = 0;
		tail = 0;
	}
	buffer[head] = value;
	++length;
}

long Deque::popFront() {
	assert(length > 0);
	long result = buffer[head];
	// сдвинуть индекс head вправо, если он вышел за границу массива, поставить его в начало (зациклить массив)
	++head %= size;
	--length;
	// если был удален последний элемент, установить head и tail равными -1
	if (length == 0) {
		head = -1;
		tail = -1;
	}
	return result;
}

void Deque::pushBack(long value) {
	if (length == size) {
		grow();
	}
	// сдвинуть индекс tail вправо, если он вышел за границу массива, поставить его в начало (зациклить массив)
	++tail %= size;
	// если был удален последний элемент, установить head и tail равными -1
	if (head == -1 || tail == -1) {
		head = 0;
		tail = 0;
	}
	buffer[tail] = value;
	++length;
}

long Deque::popBack() {
	assert(length > 0);
	long result = buffer[tail];
	// если tail выйдет за левую границу массива, зациклить массив
	if (--tail == -1)
		tail = size - 1;
	--length;
	// если был удален последний элемент, установить head и tail равными -1
	if (length == 0) {
		head = -1;
		tail = -1;
	}
	return result;
}

long Deque::getLength() const {
	return length;
}

bool makeMove(Deque& deque, int move, long value) {
	bool result = true;
	long moveValue;
	switch (move) {
	case 1:
		deque.pushFront(value);
		break;
	case 2:
		// удаление только для непустого дека
		moveValue = deque.getLength() > 0 ? deque.popFront() : -1;
		result = result && moveValue == value;
		break;
	case 3:
		deque.pushBack(value);
		break;
	case 4:
		// удаление только для непустого дека
		moveValue = deque.getLength() > 0 ? deque.popBack() : -1;
		result = result && moveValue == value;
		break;
	}
	return result;
}

int main() {
	int numberOfMoves;
	std::cin >> numberOfMoves;
	bool isOkay = true;
	Deque deque;
	for (int i = 0; i < numberOfMoves; ++i) {
		int move;
		long value;
		std::cin >> move >> value;
		isOkay = makeMove(deque, move, value) && isOkay;
	}
	std::cout << (isOkay ? "YES" : "NO");
	return 0;
}