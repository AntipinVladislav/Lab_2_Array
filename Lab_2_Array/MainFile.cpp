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

	~LinkedList() {
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
		if (node->motivation == 0) {
			return;
		}

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

	Node*& operator[](const size_t index) {
		Node* current = head;
		int count = 0;


		while (count != index) {
			current = current->next;
			count++;
		}

		return current;
	}

	const Node* operator[](const size_t index) const{
		Node* current = head;
		int count = 0;


		while (count != index) {
			current = current->next;
			count++;
		}

		return current;
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

std::ostream& operator<<(std::ostream& out, Node* node) {

	out << node->motivation << ' ' << node->power << endl;

	return out;
}



float problem_solver_9000(LinkedList list, float x) {
	float result = 0;
	Node* current = list.get_head();
	Node* head = list.get_head();

	while (current->next != head) {
		result += current->motivation * pow(x, current->power);
		current = current->next;
	}
	result += current->motivation * pow(x, current->power);
	return result;
}


int main() {
	LinkedList list1;

	Node* node1 = new Node(2, 4);
	Node* node2 = new Node(3, 6);
	Node* node3 = new Node(7, 10);
	Node* node4 = new Node(3, 6);
	Node* node5 = new Node(11, 8);

	list1.push_tail(node1);
	list1.push_tail(node2);
	list1.push_tail(node3);
	list1.push_tail(node4);
	list1.push_tail(node5);

	cout << list1 << endl;
	cout << "JUST LIST" << endl << endl << endl;

	//Рандом
	LinkedList list2(5, 1, 20);
	cout << list2 << endl;
	cout << "RANDOM" << endl << endl << endl;

	//Копибарование
	LinkedList list3(list2);
	cout << list3 << endl;
	cout << "COPY" << endl << endl << endl;

	//Лист в конец
	list1.push_tail(list3);
	cout << list1 << endl;
	cout << "PUSH LIST" << endl << endl << endl;

	//Лист и нод в нычало
	Node* node88 = new Node(33, 36);
	list1.push_head(node88);
	cout << list1 << endl;
	cout << "PUSH HEAD NODE" << endl << endl << endl;

	list1.push_head(list2);
	cout << list1 << endl;
	cout << "PUSH HEAD LIST" << endl << endl << endl;

	//Франция
	list1.pop_head();
	cout << list1 << endl;
	cout << "GUILLOTINE" << endl << endl << endl;

	//Ящурица
	list1.pop_tail();
	cout << list1 << endl;
	cout << "NO TAIL" << endl << endl << endl;

	//Удаление ненужного нода
	Node* node222 = new Node(3, 6);
	Node* node22 = new Node(3, 6);
	list1.push_head(node22);
	list1.push_tail(node222);
	list1.delete_node(node2);
	cout << list1 << endl;
	cout << "NO NODES?" << endl << endl << endl;

	//Скобочки
	cout << list2[2] << endl;
	list2[2]->motivation = 0;
	list2[2]->power = 0;
	cout << list2 << endl;
	cout << "\[0_0]/" << endl << endl << endl;

	//СЛОЖНОЕ ЗАДАНИЕ
	Node* polynomial1 = new Node(2, 5);
	Node* polynomial2 = new Node(1, 4);
	Node* polynomial3 = new Node(5, 2);
	Node* polynomial4 = new Node(1, 1);
	Node* polynomial5 = new Node(0, 1);

	LinkedList result_list;
	result_list.push_tail(polynomial1);
	result_list.push_tail(polynomial2);
	result_list.push_tail(polynomial3);
	result_list.push_tail(polynomial4);
	result_list.push_tail(polynomial5);
	cout << result_list << endl;

	float x = 0;
	cout << "x = ";
	cin >> x;

	
	cout << "ANSWER --->>" << problem_solver_9000(result_list, x) << endl;
}