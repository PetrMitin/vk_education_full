//1.3 ≈сли в числе содержитс€ только один бит со значением 1, записать в выходной поток OK. »наче записать FAIL
#include <iostream>

bool isOneThruthfulBit(unsigned long x) {
	int countOnes = 0;
	for (int i = 0; i < 32; ++i) {
		if (x & 1) ++countOnes;
		x >>= 1;
	}
	return countOnes == 1;
}

int main() {
	unsigned long val;
	std::cin >> val;
	std::cout << (isOneThruthfulBit(val) ? "OK" : "FAIL");
	return 0;
}