#include <iostream>

template <class T, class Compare = std::less<T>>
void InsertionSort(T* a, int size, Compare cmp = Compare()) {
	T x;
	int i, j;
	for (i = 0; i < size; i++) {  // цикл проходов, i - номер прохода
		x = a[i];
		// поиск места элемента в готовой последовательности 
		for (j = i - 1; j >= 0 && cmp(x, a[j]); j--)
			// сдвигаем элемент направо, пока не дошли
			a[j + 1] = a[j];
		// место найдено, вставить элемент
		a[j + 1] = x;
	}
}

struct Point {
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	int x;
	int y;
};

class Compare {
public:
	Compare(Point p) : initialPoint(p) {}
	bool operator() (const Point& p1, const Point& p2) {
		int px1 = abs(initialPoint.x - p1.x);
		int py1 = abs(initialPoint.y - p1.y);
		int px2 = abs(initialPoint.x - p2.x);
		int py2 = abs(initialPoint.y - p2.y);
		if (px1 == 0 && px2 == 0)
			return p1.y < p2.y;
		else if (px1 == 0) {
			return px1;
		}
		else if (px2 == 0) {
			return px2;
		}
		return atan(py1 / px1) > atan(py2 / px2);
	}
private: 
	Point initialPoint;
};

void solve(Point* arr, int length, Point minPoint) {
	InsertionSort(arr, length, Compare(minPoint));
	for (int i = 0; i < length; ++i) {
		std::cout << arr[i].x << ' ' << arr[i].y << '\n';
	}
}

int main() {
	int n;
	std::cin >> n;
	Point* arr = new Point[n];
	Point minPoint;
	for (int i = 0; i < n; ++i) {
		int x, y;
		std::cin >> x >> y;
		arr[i] = { x, y };
		if (x < minPoint.x || (x == minPoint.x && y < minPoint.y))
			minPoint = { x, y };
	}
	solve(arr, n, minPoint);
	delete[] arr;
	return 0;
}