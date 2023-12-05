#include <iostream>
#include <cmath>
#include <stdexcept>
#include <random>

using namespace std;

std::random_device random_device_new{};

struct Node {
	float motivation;
	float power;
	Node* next = nullptr;
	Node() : motivation(0), power(0), next(nullptr) {};
	Node(float new_motivation, float new_power) : motivation(new_motivation), power(new_power) {};

};



class LinkedList {
private:
	Node* head;

	
	void copy(const LinkedList& list) {
		head = new Node;
		head->motivation = list.head->motivation;
		head->power = list.head->power;

		Node* current_source = list.head->next;
		Node* current_this = head;
		while (current_source != list.head)
		{
			Node* temp_this = new Node;

			current_this->next = temp_this;
			current_this = temp_this;

			current_this->motivation = current_source->motivation;
			current_this->power = current_source->power;
			current_source = current_source->next;
		}

		current_this->next = head;
	}

public:
	LinkedList() : head(head) {};




	LinkedList(const LinkedList& list) {
		copy(list);
	}

	LinkedList(int size, float low, float high) {
		std::mt19937 random_engine(random_device_new());
		std::uniform_real_distribution<> dist(low, high);
		for (int i = 0; i < size; i++) {
			Node* node = new Node(dist(random_engine), dist(random_engine));
			push_tail(node);
		}
	}

	~LinkedList(){
		Node* old_head = head;
		if (head == nullptr)
			return;
		Node* cur = head->next;
		delete head;
		while (cur != old_head) {
			Node* prev = cur;
			cur = cur->next;
			delete prev;
		}
	}

	void push_tail(Node* node) {
		if (head == nullptr) {
			head = node;
			head->next = head;
		}

		Node* current = head;
			
		while (current->next != head) {
			current = current->next;
		}
		
		current->next = node;
		node->next = head;
	}

	void push_tail(LinkedList& list) {
		
		if (head == nullptr) {
			copy(list);
		}

		Node* current = list.get_head();

		Node* nodeh = new Node(current->motivation, current->power);
		push_tail(nodeh);
		current = current->next;

		while (current != list.get_head()) {
			Node* node = new Node(current->motivation, current->power);
			push_tail(node);
			current = current->next;
		}
	}



	void push_head(Node* node) {
		push_tail(node);
		head = node;
	}

	void push_head(LinkedList& list) {

		if (head == nullptr) {
			copy(list);
		}

		Node* current = list.get_head();

		Node* nodeh = new Node(current->motivation, current->power);
		push_tail(nodeh);
		current = current->next;

		while (current != list.get_head()) {
			Node* node = new Node(current->motivation, current->power);
			push_tail(node);
			current = current->next;
		}

		head = nodeh;
	}


	Node* get_head() { // ;)
		return head;
	}

	void pop_head() {
		Node* current = head;

		while (current->next != head) {
			current = current->next;
		}
		Node* ded_head = head;
		current->next = head->next;
		head = head->next;
		delete ded_head;
	}

	void pop_tail() {
		Node* current = head;

		while (current->next->next != head) {
			current = current->next;
		}
		delete current->next;
		current->next = head;

	}


	void delete_node(Node* node) {
		Node* ded_node = new Node(node->motivation, node->power);
		Node* current = head;

		while (current->next != head) {
			if (current->next->motivation == ded_node->motivation && current->next->power == ded_node->power) {
				Node* repair_node = current->next->next;
				delete current->next;
				current->next = repair_node;
			}
			else
				current = current->next;
		}
		if (head->motivation == ded_node->motivation && head->power == ded_node->power)
			pop_head();

	}

};

std::ostream& operator<<(std::ostream& out, LinkedList& list) {
	Node* my_head = list.get_head();

	if (my_head == nullptr)
		return out;

	out << my_head->motivation << ' ' << my_head->power << endl;

	Node* cur = list.get_head();
	while (cur->next != my_head) {
		cur = cur->next;
		out << cur->motivation << ' ' << cur->power << endl;
	}
	return out;
}


int main() {
	LinkedList list1;

	Node* node1 = new Node(2, 4);
	Node* node2 = new Node(3, 6);
	Node* node3 = new Node(3, 6);
	Node* node4 = new Node(2, 4);
	Node* node5 = new Node(2, 4);

	list1.push_tail(node1);
	list1.push_tail(node2);
	list1.push_tail(node3);
	list1.push_tail(node4);
	list1.push_tail(node5);

	cout << list1 << endl;

	LinkedList list2(5, 1, 20);
	cout << list2 << endl;

	/*LinkedList list3(list2);
	cout << list3 << endl;

	list1.push_tail(list3);
	cout << list1 << endl;

	Node* node3 = new Node(33, 36);
	list2.push_head(node3);
	cout << list2 << endl;

	list2.push_head(list1);
	cout << list2 << endl;*/

	/*list2.pop_head();
	cout << list2 << endl;

	list2.pop_tail();
	cout << list2 << endl;*/

	list1.delete_node(node1);
	cout << list1 << endl;
}