#include <iostream>

class Node {
public:
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = nullptr;
	}
};

class SimplyLinkedQueue {
private:
	Node* head;

public:
	SimplyLinkedQueue() {
		head = nullptr;
	}

	/// <summary>
	/// Encola en el frente de la cola simplemente enlazada
	/// </summary>
	/// <param name="data">Entero para encolar</param>
	/// <returns>Verdadero si se encoló correctamente</returns>
	bool enqueueFront(int data) {
		Node* newNode = new Node(data);
		if (head == nullptr) {
			head = newNode;
			return true;
		}
		newNode->next = head;
		head = newNode;
		return true;
	}

	/// <summary>
	/// Encola al final de la cola simplemente enlazada
	/// </summary>
	/// <param name="data">Entero para encolar</param>
	/// <returns>Verdadero si se encoló correctamente</returns>
	bool enqueueEnd(int data) {
		Node* newNode = new Node(data);
		if (head == nullptr) {
			head = newNode;
			return true;
		}
		Node* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
		return true;
	}

	/// <summary>
	/// Imprime la cola simplemente enlazada
	/// </summary>
	void print() {
		Node* current = head;
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
};

int main()
{
	SimplyLinkedQueue queue;

	queue.enqueueEnd(100);
	queue.enqueueEnd(200);
	queue.enqueueEnd(300);

	queue.print();

	queue.enqueueFront(50);
	queue.enqueueFront(25);

	queue.print();

	return 0;
}
