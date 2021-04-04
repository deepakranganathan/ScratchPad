#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <queue>

#include "Hierarchy.h"

Node::Node(std::string name, unsigned int level)
{
	m_name = name;
	m_level = level;
}

string Node::getName()
{
	return m_name;
}

unsigned int Node::getLevel()
{
	return m_level;
}

list<Node*> Node::children()
{
	return m_children;
}

void Node::addChild(Node* child)
{
	if (child != NULL)
	{
		m_children.push_back(child);
	}
}

Hierarchy::Hierarchy()
{
	root = NULL;
}

Node* Hierarchy::getRoot() const
{
	return this->root;
}

// Return false if any I/O errors occur, otherwise return true.
// The input file should have only one root node.
bool Hierarchy::LoadFromFile(const std::string& infile)
{
	stack<Node*> nodeStack;
	// NOTE: Feel free to replace the entire implementation of
	// this function.
	std::ifstream ifs(infile.c_str());
	if (!ifs)
	{
		return false;
	}

	std::string line;
	unsigned int computedLevel = 0;
	while (std::getline(ifs, line))
	{
		computedLevel = 0;
		// TODO: Parse input line by line.  Handle bad input data elegantly,
		// or at least describe how in comments.
		while (line.at(computedLevel) == '.')
		{
			computedLevel++;
		}

		if (computedLevel > nodeStack.size())
		{
			return false;
		}
		else
		{
			if (root == NULL)
			{
				root = new Node(line, computedLevel);
				nodeStack.push(root);

			}
			else
			{
				while (computedLevel < nodeStack.size())
				{
					nodeStack.pop();
				}
				Node *curNode = nodeStack.top();
				Node *childNode = new Node(line.substr(computedLevel), computedLevel);
				curNode->addChild(childNode);
				nodeStack.push(childNode);
			}

		}
	}

	return true;
}

// TODO: Implement the following Print* functions.
// - Print each node on a separate line, with two leading spaces for each depth
//   level.
// - The depth-first output should match the input order but the prefix should be
//   different.
// - The sorted depth-first output should sort the children of each node before
//   recursing into their children.
// - The breadth-first output should print all nodes at a given depth before
//   printing any deeper nodes.
// - See the files HierarchyTest_expected_*.txt in the
// Data directory for the expected results.
//
// Feel free to use helper functions, but don't change the signatures of these
// functions.

void PrintHierarchyDepthFirst(const Hierarchy& h, std::ostream& output)
{
	stack<Node*> BFSS;
	stack<unsigned int> level;
	Node *curNode = h.getRoot();
	BFSS.push(curNode);

	while (!BFSS.empty())
	{
		Node* top = BFSS.top();
		for (unsigned int i = 0; i < top->getLevel(); i++)
		{
			output << "  ";
		}
		output << top->getName() << endl;
		BFSS.pop();
		list<Node*> &children = top->children();
		for (auto ch = children.end(); ch != children.begin(); )
		{
			BFSS.push(*--ch);
		}
	}
}

void PrintHierarchyDepthFirstSorted(const Hierarchy& h, std::ostream& output)
{

}

void PrintHierarchyBreadthFirst(const Hierarchy& h, std::ostream& output)
{
	queue<Node*> BFSQ;
	queue<unsigned int> level;
	Node *curNode = h.getRoot();
	BFSQ.push(curNode);

	while (!BFSQ.empty())
	{
		Node* front = BFSQ.front();
		for (unsigned int i = 0; i < front->getLevel(); i++)
		{
			output << "  ";
		}
		output << front->getName() << endl;
		for (auto &ch : front->children())
		{
			BFSQ.push(ch);
		}
		BFSQ.pop();
	}

}

// TODO: Improve this test method.
// How could you verify your outputs are correct?
// How could you refactor this function to be less repetitive?
void TestHierarchy(std::ostream& error_output)
{
	const std::string failure_msg("Hierarchy tests failed!");

	bool success = false;

	Hierarchy h;
	std::string infile(data_location + "HierarchyTest.txt");
	success = h.LoadFromFile(infile);
	CHECK(success, failure_msg << "  I/O error.", error_output);

	std::string outfile;
	std::string testfile;
	bool identical(false);

	outfile = data_location + "HierarchyTest_output_DFS.txt";
	{
		std::ofstream ofs(outfile.c_str());
		// If this fails, manually verify that outfile is not read-only on disk
		CHECK(ofs, failure_msg << "  I/O error.", error_output);

		PrintHierarchyDepthFirst(h, ofs);
	}

	outfile = data_location + "HierarchyTest_output_DFS_sorted.txt";
	{
		std::ofstream ofs(outfile.c_str());
		// If this fails, manually verify that outfile is not read-only on disk
		CHECK(ofs, failure_msg << "  I/O error.", error_output);

		PrintHierarchyDepthFirstSorted(h, ofs);
	}

	outfile = data_location + "HierarchyTest_output_BFS.txt";
	{
		std::ofstream ofs(outfile.c_str());
		// If this fails, manually verify that outfile is not read-only on disk
		CHECK(ofs, failure_msg << "  I/O error.", error_output);

		PrintHierarchyBreadthFirst(h, ofs);
	}
}

void RunTestHierarchy()
{
	std::ostringstream oss;

	TestHierarchy(oss);

	// Print output to console
	std::cout << oss.str();

	// Pause...
	std::cout << std::endl
		<< std::endl
		<< "Press enter to quit..." << std::endl;
	char c;
	std::cin >> std::noskipws >> c;
}
