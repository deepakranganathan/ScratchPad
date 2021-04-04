#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

class Trie
{
public:

private:
	bool isLeaf;
	map<char,Trie*> trieMap;

public:
	Trie() {
		this->isLeaf = false;
		this->trieMap.clear();
	}

	void insert(string str) {
		// start from the root node
		Trie *cur = this;
		for (int i = 0; i < str.length(); i++) {
			if (cur->trieMap.find(str[i]) == cur->trieMap.end()) {
				cur->trieMap.insert({ str[i], new Trie() });
			}

			cur = cur->trieMap[str[i]];
		}

		cur->isLeaf = true;
	}

	void insertRecursive(Trie* cur, string str, int index = 0) {
		if (index == str.length()) {
			cur->isLeaf = true;
			return;
		}
		if (cur->trieMap.find(str[index]) == cur->trieMap.end()) {
			cur->trieMap.insert({ str[index], new Trie() });
		}
		insertRecursive(cur->trieMap[str[index]], str, index + 1);
	}

	bool remove(Trie* cur, string str, int index = 0) {
		if (cur == nullptr) {
			return false;
		}

		if (index == str.length()) {
			if (!cur->isLeaf) {
				return false;
			}
			cur->isLeaf = false;
			return cur->trieMap.empty();
		}

		if(cur->trieMap.find(str[index]) == cur->trieMap.end()) {
			return false;
		}

		bool shouldDelete = remove(cur->trieMap[str[index]], str, index + 1);
		if (shouldDelete) {
			cur->trieMap.erase(str[index]);
			return cur->trieMap.empty();
		}
		return false;
	}

	bool search(string str) {
		if (this == nullptr) {
			return false;
		}

		Trie* cur = this;
		for (int i = 0; i < str.length(); i++) {
			cur = cur->trieMap[str[i]];
			if (cur == nullptr) {
				return false;
			}
		}
		return cur->isLeaf;
	}

	bool searchRecursive(Trie* cur, string str, int index = 0) {
		if (index == str.length()) {
			return cur->isLeaf;
		}
		cur = cur->trieMap[str[index]];
		if (cur == nullptr) {
			return false;
		}
		return searchRecursive(cur, str, index + 1);
	}
};

int solution(vector<int> &A) {
	// write your code in C++14 (g++ 6.2.0)
	unordered_map<int, bool> intMap;

	for (auto& a : A) {
		intMap.insert({ a,true });
	}

	unsigned int i = 1;
	while (i<A.size()) {
		if (intMap.find(i) == intMap.end()) {
			return i;
		}
		i++;
	}
	return ++i;

}

int main2() {

	vector<int> A = { 1,2,3 };
	cout << solution(A) << endl;



	//Trie *head = new Trie();

	//head->insertRecursive(head,"hello");
	//cout << head->searchRecursive(head,"hello") << " ";      // print 1

	//head->insertRecursive(head, "helloworld");
	//cout << head->searchRecursive(head, "helloworld") << " "; // print 1

	//cout << head->searchRecursive(head, "helll") << " ";      // print 0 (Not found)

	//head->insert("hell");
	//cout << head->searchRecursive(head, "hell") << " ";       // print 1

	//head->insert("h");
	//cout << head->searchRecursive(head, "h");                 // print 1

	//cout << endl;

	//head->remove(head, "hello");
	//cout << head->searchRecursive(head, "hello") << " ";      // print 0

	//cout << head->search("helloworld") << " "; // print 1
	//cout << head->searchRecursive(head, "hell");              // print 1

	//cout << endl;

	//head->remove(head, "h");
	//cout << head->search("h") << " ";          // print 0
	//cout << head->search("hell") << " ";       // print 1
	//cout << head->search("helloworld");        // print 1

	//cout << endl;

	//head->remove(head, "helloworld");
	//cout << head->search("helloworld") << " "; // print 0
	//cout << head->search("hell") << " ";       // print 1

	//head->remove(head, "hell");
	//cout << head->search("hell");              // print 0

	//cout << endl;

	//if (head == nullptr) {
	//	cout << "Trie empty!!\n";              // Trie is empty now
	//}

	//cout << head->search("hell");              // print 0

	// Pause...
	std::cout << std::endl
		<< std::endl
		<< "Press enter to quit..." << std::endl;
	char c;
	std::cin >> std::noskipws >> c;

	return 0;
}