#include <iostream>
#include <string>

#define TABLE_SIZE 1000

using std::string;
using std::cout;
using std::endl;

class Node {
public:
	string key;
	string value;
	Node* next;
	Node* prev;

	Node(string key, string value) {
		this->key = key;
		this->value = value;
		this->next = nullptr;
		this->prev = nullptr;
	}
};

class HashTable {
private:
	Node** table;

public:
	HashTable() {
		table = new Node * [TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++) {
			table[i] = nullptr;
		}
	}

	~HashTable() {
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			Node* current = table[i];
			while (current != nullptr)
			{
				Node* next = current->next;
				delete current;
				current = next;
			}
		}
		delete[] table;
	}

	int hashFunction(string key) {
		int sum = 0;
		for (char c : key) {
			sum += c;
		}
		return sum % TABLE_SIZE;
	}

	void insert(string key, string value) {
		int index = hashFunction(key);
		Node* newNode = new Node(key, value);

		if (table[index] == nullptr) {
			table[index] = newNode;
		}
		else {
			Node* current = table[index];
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = newNode;
			newNode->prev = current;
		}
	}

	void remove(string key) {
		int index = hashFunction(key);
		Node* current = table[index];

		while (current != nullptr)
		{
			if (current->key == key) {
				if (current->prev != nullptr) {
					current->prev->next = current->next;
				}
				else {
					table[index] = current->next;
				}

				if (current->next != nullptr) {
					current->next->prev = current->prev;
				}

				delete current;
				return;
			}
			current = current->next;
		}
	}

	string search(string key) {
		int index = hashFunction(key);
		Node* current = table[index];

		while (current != nullptr)
		{
			if (current->key == key) {
				return current->value;
			}
			current = current->next;
		}

		return "No se encontraron resultados";
	}

	void displayTable() {
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			cout << "Indice " << i << ": ";

			Node* current = table[i];

			while (current != nullptr)
			{
				cout << current->value << " ";
				current = current->next;
			}
			cout << endl;
		}
	}
};

std::string gen_random(const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(len);

	for (int i = 0; i < len; ++i) {
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return tmp_s;
}

int main()
{
	HashTable hashTable;

	// Generate reandom keys and values
	for (int i = 0; i < 100000; i++) {
		string key = gen_random(5);
		string value = gen_random(10);
		hashTable.insert(key, value);
	}

	hashTable.insert("key1", "valor1");
	hashTable.insert("key2", "valor2");
	hashTable.insert("key3", "valor3");
	hashTable.insert("key4", "valor4");
	hashTable.insert("key5", "valor5");

	/*cout << "Tabla de hash original:" << endl;
	hashTable.displayTable();
	cout << endl;*/

	cout << "Buscar elemento con clave 'key2': " << hashTable.search("key2") << endl;
	cout << "Buscar elemento con clave 'key6': " << hashTable.search("key6") << endl;
	cout << endl;

	hashTable.remove("key2");

	cout << "Tabla de hash despues de eliminar el elemento con clave 'key2':" << endl;

	hashTable.displayTable();

	return 0;
}
