// C program for different tree traversals
#include <iostream>
using namespace std;

/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct Node
{
	int data;
	Node* left, *right;
	Node(int data)
	{
		this->data = data;
		left = right = NULL;
	}
};

/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct Node* node)
{
	if (node == NULL)
		return;
	cout << node->data << " ";
	printPreorder(node->left);
	printPreorder(node->right);
}

/* Given a binary tree, print its nodes according to the
"bottom-up" postorder traversal. */
void printPostorder(struct Node* node)
{
	if (node == NULL)
		return;
	printPostorder(node->left);
	printPostorder(node->right);
	cout << node->data << " ";
}

/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct Node* node)
{
	if (node == NULL)
		return;
	printInorder(node->left);
	cout << node->data << " ";
	printInorder(node->right);
}

bool isBST(struct Node* node, int min = INT_MIN, int max = INT_MAX)
{
	if (node == nullptr)
		return true;
	if (node->data < min || node->data >max)
		return false;
	return (isBST(node->left, min, node->data) &&
			isBST(node->right, node->data, max));
}

void RunTestBinaryTree()
{
	struct Node *root = new Node(50);
	root->left = new Node(30);
	root->right = new Node(70);
	root->left->left = new Node(10);
	root->left->right = new Node(45);
	root->right->left = new Node(55);
	root->right->right = new Node(100);

	cout << "\nPreorder traversal of binary tree is \n";
	printPreorder(root);

	cout << "\nInorder traversal of binary tree is \n";
	printInorder(root);

	cout << "\nPostorder traversal of binary tree is \n";
	printPostorder(root);

	cout << (isBST(root) ? "Is BST" : "Not a BST") << endl;

}
