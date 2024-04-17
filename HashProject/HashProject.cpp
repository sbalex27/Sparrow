#include <iostream>
#include <list>
#define TABLE_SIZE 10

using namespace std;

class HashTable {
private:
	list<int> table[TABLE_SIZE];

	int hashFunction(int key) {
		return key % TABLE_SIZE;
	}

public:
	void insert(int key) {
		int index = hashFunction(key);
		table[index].push_back(key);
	}

	void remove(int key) {
		int index = hashFunction(key);
		table[index].remove(key);
	}

	bool search(int key) {
		int index = hashFunction(key);
		for (int element : table[index]) {
			if (element == key) {
				return true;
			}
		}
		return false;
	}

	void display() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			cout << i;
			for (int element : table[i]) {
				cout << " --> " << element;
			}
			cout << endl;
		}
	}
};

int main()
{
	HashTable hashTable;

	hashTable.insert(5);
	hashTable.insert(15);
	hashTable.insert(25);
	hashTable.insert(35);
	hashTable.insert(45);

	hashTable.display();

	int key = 25;

	if (hashTable.search(key)) {
		cout << "El elemento " << key << " fue encontrado" << endl;
	}
	else {
		cout << "El elemento " << key << " no fue encontrado" << endl;
	}

	hashTable.remove(15);

	hashTable.display();

	return 0;
}
