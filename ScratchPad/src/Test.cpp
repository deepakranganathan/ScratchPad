#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

void RunTestHierarchy();
void RunTestStringRotation();
void RunTestBinaryTree();
int RunTestGraph();
void TestLRUCache();
void TestTiling();
void TestTraits();


void TestFun() {
	int arr[64];
	int num = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			arr[i*8+j] = num++;

	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			std::cout << *(arr + 4*(8 * x + y)) << std::endl;
}

class Node {
public:
	Node * next;
	int value;

	Node() {
		next = nullptr;
		value = 0;
	}
};

// Insert at the end
void append(Node **n, int i) {
	Node *newNode = new Node();
	newNode->value = i;
	newNode->next = nullptr;

	if (*n == nullptr) {
		*n = newNode;
		return;
	}
	//else traverse till end
	Node* cur = *n;
	while (cur->next != nullptr) {
		cur = cur->next;
	}
	cur->next = newNode;
}

// Insert at the beginning
void push(Node** n, int i) {
	Node* newNode = new Node();
	newNode->value = i;
	newNode->next = *n;
	//move the head to point to the new node
	*n = newNode;
}

// Insert after a certain node
void insert(Node* n, int i) {
	Node* newNode = new Node();
	newNode->value = i;
	newNode->next = n->next;
	n->next = newNode;
}

// Delete a note
void remove(Node* head, Node* n) {
	if (head == nullptr) {
		return;
	}
	else {
		while (head->next != nullptr && head->next != n) {
			head = head->next;
		}
		if (head->next == n) {
			head->next = n->next;
			delete n;
		}
		else
			return;
	}
}

void printList(Node *node)
{
	while (node != NULL)
	{
		cout << " " << node->value;
		node = node->next;
	}
}

// -----------------------------------------------------------------------------

int main()
{
	RunTestHierarchy();
	RunTestStringRotation();
	RunTestBinaryTree();
	RunTestGraph();
	TestLRUCache();
	TestTiling();
	TestTraits();

	Node *head = nullptr;
	// Insert 6. So linked list becomes 6->NULL  
	append(&head, 6);

	// Insert 7 at the beginning.  
	// So linked list becomes 7->6->NULL  
	push(&head, 7);

	// Insert 1 at the beginning.  
	// So linked list becomes 1->7->6->NULL  
	push(&head, 1);

	// Insert 4 at the end. So  
	// linked list becomes 1->7->6->4->NULL  
	append(&head, 4);

	// Insert 8, after 7. So linked  
	// list becomes 1->7->8->6->4->NULL  
	insert(head->next, 8);

	// Delete 6. So linked list
	// becomes 1->7->8->4->NULL
	remove(head, head->next->next->next);

	cout << "Created Linked list is: ";
	printList(head);
}
