//��� ������, ������� ������� ����� ���������� ����������� ������� ��������� ���������������� �������.
//����� ����� ������ ��������, � �������� ��������� �������� ������.

#include <iostream>

int solve(int* arr, int n) {
	int lb = 0;
	int rb = n;
	int currIndex = lb + (rb - lb) / 2;
	while ((rb - lb) > 1) {
		if (arr[currIndex] >= arr[rb - 1]) {
			lb = currIndex;
		}
		else if (arr[currIndex] <= arr[lb]) {
			rb = currIndex + 1;
		}
		currIndex = lb + (rb - lb) / 2;
	}
	return currIndex;
}

int main() {
	int n;
	std::cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}
	std::cout << solve(arr, n);
	delete[] arr;
	return 0;
}