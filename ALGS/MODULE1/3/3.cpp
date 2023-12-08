//����������� ��� � ������������ ����������� �������(�� ������ ������������� �������).

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
	// ����������� ���������� ���������, ��� ������� ����� �������� ������
	const unsigned int minSize = 7;
	// ������ ������
	long size;
	// ���������� ���������
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
	// ���� �� ������ ������������� ������
	if (buffer != nullptr) {
		// ���� ������� ��������� � ����������� ������� ������������� ��������� ������� ���������
		if (head == 0 && tail == size - 1)
			std::copy(buffer, buffer + size, newBuffer);
		else {
			// ���������� �� head �� ����� �������
			std::copy(buffer + head, buffer + size, newBuffer);
			// ���������� �� ������ ������� �� tail
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
	// ���� head ������ �� ����� ������� �������, ��������� ������
	if (--head == -1)
		head = size - 1;
	// ���� � ������� �� ���� ���������
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
	// �������� ������ head ������, ���� �� ����� �� ������� �������, ��������� ��� � ������ (��������� ������)
	++head %= size;
	--length;
	// ���� ��� ������ ��������� �������, ���������� head � tail ������� -1
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
	// �������� ������ tail ������, ���� �� ����� �� ������� �������, ��������� ��� � ������ (��������� ������)
	++tail %= size;
	// ���� ��� ������ ��������� �������, ���������� head � tail ������� -1
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
	// ���� tail ������ �� ����� ������� �������, ��������� ������
	if (--tail == -1)
		tail = size - 1;
	--length;
	// ���� ��� ������ ��������� �������, ���������� head � tail ������� -1
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
		// �������� ������ ��� ��������� ����
		moveValue = deque.getLength() > 0 ? deque.popFront() : -1;
		result = result && moveValue == value;
		break;
	case 3:
		deque.pushBack(value);
		break;
	case 4:
		// �������� ������ ��� ��������� ����
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