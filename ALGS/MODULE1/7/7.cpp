// Дан массив строк. Количество строк не больше 105. 
// Отсортировать массив методом поразрядной сортировки MSD по символам. 
// Размер алфавита - 256 символов.Последний символ строки = ‘\0’.

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

// получить индекс символа в массиве count
int charIndexAt(char* s, int d, char minChar) {
	char currChar = s[d];
	if (d < strlen(s)) return currChar - minChar;
	else return -1;
}

// рекурсивно отсортировать массив arr с hi по lo включительно по символу с порядковым номером d
void MSDSort(char** arr, char** other, int lo, int hi, int d, int alphabetLength, char minChar) {
	if (hi <= lo) return;
	// массив счетчиков, включая два дополнительных счетчика для начала и конца заполнения результирующего массива
	int* count = new int[alphabetLength + 2];
	for (int i = 0; i < alphabetLength + 2; ++i)
		count[i] = 0;
	for (int i = lo; i <= hi; ++i) {
		int idx = charIndexAt(arr[i], d, minChar) + 2;
		++count[idx];
	}
	for (int r = 0; r < alphabetLength + 1; ++r)
		count[r + 1] += count[r];
	// копируем результат сортировки в массив other поверхностным копированием (данные в массивах не меняются)
	for (int i = lo; i <= hi; ++i) {
		int idx = charIndexAt(arr[i], d, minChar) + 1;
		other[count[idx]++] = arr[i];
	}
	for (int i = lo; i <= hi; ++i)
		arr[i] = other[i - lo];
	for (int r = 0; r < alphabetLength; ++r)
		MSDSort(arr, other, lo + count[r], lo + count[r + 1] - 1, d + 1, alphabetLength, minChar);
	delete[] count;
}

int main() {
	char** arr = new char*[100000];
	string s;
	int length = 0;
	char minChar = WCHAR_MAX;
	char maxChar = WCHAR_MIN;
	while (cin >> s) {
		// при считывании строк сохраняем максимальный и минимальный символ для подсчета длины алфавита 
		// и корректной индексации символов функцией charIndexAt
		for (int i = 0; i < s.length(); ++i) {
			minChar = min(s[i], minChar);
			maxChar = max(maxChar, s[i]);
		}
		const char* char_string = s.c_str();
		arr[length] = new char[s.length() + 1];
		arr[length][s.length()] = '\0';
		copy(char_string, char_string + s.length(), arr[length++]);
	}
	char** other = new char* [length];
	MSDSort(arr, other, 0, length - 1, 0, maxChar + 1 - minChar, minChar);
	for (int i = 0; i < length; ++i)
		cout << arr[i] << '\n';
	for (int i = 0; i < length; ++i)
		delete[] arr[i];
	delete[] other;
	delete[] arr;
	return 0;
}