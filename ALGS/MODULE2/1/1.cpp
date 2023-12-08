// ���������� ��������� ������ ���� ���������� ����� �� ������ ������������ ��� - ������� � �������� ����������.
// �������� ������ �������� � ������� �� �������� ��������� ����.
// ��� - ������� ������ ������ ���� ����������� � ������� ���������� �������� ���������� ������� �������.
// ��������� ������ ������� ������ ���� ������ 8 - ��.
// ��������������� ���������� ��� ���������� ��������� � ������, ����� ����������� ���������� ������� ��������� 3 / 4.
// ��������� ������ ������ ������������ �������� ���������� ������ � ���������, �������� ������ �� ��������� � �������� �������������� ������ ������ ���������.
// 1_1. ��� ���������� �������� ����������� ������������ ������������.
// i - �� ����� g(k, i) = g(k, i - 1) + i(mod m).m - ������� ������.


#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T, class H>
class HashTable {
public:
	HashTable(int initialSize, const H& hasher);

	// Empty: return false;
	// Key: key == Key ? return true : ����������� ������
	// Deleted: ����������� ������
	bool Has(const T& key) const;

	// Empty: firstDeleted == -1 ?
	//			 (���������� ���� � ������� �������, �������� ������ Key � return true) :
	//			 (���������� ���� � ������� firstDeleted, �������� ������ Key � return true)
	// Key: key == Key ? return false : ����������� ������
	// Deleted: ��������� �� ������ Deleted ? ����������� ������ : ���������� firstDeleted
	bool Add(const T& key);

	// Empty: return false;
	// Key: key == Key ? �������� ������ Deleted � return true : ����������� ������
	// Deleted: ����������� ������
	bool Delete(const T& key);

	void Print();

private:
	enum NodeState { Empty, Deleted, Key };

	struct HashTableNode {
		T key;
		NodeState status;
		unsigned int hash;

		HashTableNode() : status(Empty) {};
	};

	H hasher;
	vector<HashTableNode> table;
	unsigned int keysCount;
	unsigned int deletedCount;

	// ��������������� ������ ���� �����: � ����������� ������� ������� � ��� (��� ���������� deleted �����)
	void Grow();

	int GetNextHash(int prevPos, int i) const;
};

template <class T, class H>
HashTable<T, H>::HashTable(int initialSize, const H& hasher) : hasher(hasher), table(initialSize), keysCount(0), deletedCount(0) {}

template <class T, class H>
bool HashTable<T, H>::Has(const T& key) const {
	int initialHash = -1;
	int currentHash = hasher(key) % table.size();
	int i = 0;
	while (currentHash != initialHash &&
		(table[currentHash].status != Empty && table[currentHash].key != key
			|| table[currentHash].status == Deleted)) {
		if (initialHash == -1)
			initialHash = currentHash;
		currentHash = GetNextHash(currentHash, ++i) % table.size();
	}
	if (currentHash == initialHash || table[currentHash].status == Empty)
		return false;
	return true;
}

template <class T, class H>
bool HashTable<T, H>::Add(const T& key) {
	if (keysCount + deletedCount > table.size() * 3 / 4)
		Grow();
	int absHash = hasher(key);
	int initialHash = -1;
	int currentHash = absHash % table.size();
	int firstDeleted = -1;
	int i = 0;
	while (currentHash != initialHash &&
		(table[currentHash].status != Empty && table[currentHash].key != key
			|| table[currentHash].status == Deleted)) {
		if (initialHash == -1)
			initialHash = currentHash;
		if (firstDeleted == -1 && table[currentHash].status == Deleted)
			firstDeleted = currentHash;
		currentHash = GetNextHash(currentHash, ++i) % table.size();
	}
	if ((currentHash == initialHash || table[currentHash].status == Empty) && firstDeleted != -1) {
		table[firstDeleted].key = key;
		table[firstDeleted].status = Key;
		++keysCount;
		--deletedCount;
		return true;
	}
	else if (currentHash != initialHash) {
		if (table[currentHash].status == Key && table[currentHash].key == key)
			return false;
		else {
			table[currentHash].status = Key;
			table[currentHash].key = key;
			table[currentHash].hash = absHash;
			++keysCount;
			return true;
		}
	}
	else {
		Grow();
		return Add(key);
	}
}

template <class T, class H>
bool HashTable<T, H>::Delete(const T& key) {
	int initialHash = -1;
	int currentHash = hasher(key) % table.size();
	int i = 0;
	while (currentHash != initialHash &&
		(table[currentHash].status != Empty && table[currentHash].key != key
			|| table[currentHash].status == Deleted)) {
		if (initialHash == -1)
			initialHash = currentHash;
		currentHash = GetNextHash(currentHash, ++i) % table.size();
	}
	if (currentHash == initialHash || table[currentHash].status != Key)
		return false;
	table[currentHash].status = Deleted;
	++deletedCount;
	--keysCount;
	return true;
}

template <class T, class H>
void HashTable<T, H>::Grow() {
	vector<HashTableNode> newTable(deletedCount > table.size() / 4 ? table.size() : table.size() * 2);
	for (int i = 0; i < table.size(); ++i) {
		if (table[i].status == Key) {
			int absHash = table[i].hash;
			int currentHash = absHash % newTable.size();
			int initialHash = -1;
			int counter = 0;
			while (currentHash != initialHash && newTable[currentHash].status != Empty) {
				if (initialHash == -1)
					initialHash = currentHash;
				currentHash = GetNextHash(currentHash, ++counter) % newTable.size();
			}
			if (currentHash != initialHash && newTable[currentHash].status == Empty) {
				newTable[currentHash] = table[i];
			}
		}
	}
	table = newTable;
	deletedCount = 0;
}

template <class T, class H>
int HashTable<T, H>::GetNextHash(int prevPos, int i) const {
	return prevPos + i;
}

template <class T, class H>
void HashTable<T, H>::Print() {
	for (int i = 0; i < table.size(); ++i) {
		cout << '(' << table[i].key << ", " << table[i].hash << ')';
	}
	cout << endl;
}

struct StringHasher {
	unsigned int operator()(const string& key) const {
		unsigned int hash = 0;
		for (int i = 0; i < key.size(); ++i) {
			hash = hash * 137 + key[i];
		}
		return hash;
	}
};

int main() {
	StringHasher hasher;
	HashTable<string, StringHasher> table(2, hasher);
	char operation = 0;
	string word;
	while (cin >> operation >> word) {
		switch (operation) {
		case '+':
			cout << (table.Add(word) ? "OK" : "FAIL") << endl;
			break;
		case '-':
			cout << (table.Delete(word) ? "OK" : "FAIL") << endl;
			break;
		case '?':
			cout << (table.Has(word) ? "OK" : "FAIL") << endl;
			break;
		default:
			break;
		}
	}
	return 0;
}