#include <iostream>

using namespace std;

struct Node {
	float motivation;
	float power;
	Node* next = nullptr;
	Node() : motivation(0), power(0), next(nullptr) {};
	Node(float new_coefficient, float new_power) : motivation(new_coefficient), power(new_power) {};
};



class LinkedList {
private:
	Node* head;
public:
	LinkedList() : head(head) {};

	LinkedList(const LinkedList& list) {
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

	Node* get_head() { // ;)
		return head;
	}

};

std::ostream& operator<<(std::ostream& out, LinkedList list) {
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
	LinkedList list2;


	Node* node1 = new Node(2, 4);
	Node* node2 = new Node(3, 6);

	list1.push_tail(node1);
	list1.push_tail(node2);
	cout << list1 << endl;

}