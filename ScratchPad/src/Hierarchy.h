#pragma once

#include <list>

using namespace std;

// Append data filenames to this string to read/write files in the data folder.
const std::string data_location("");

#define CHECK(cond, errstream, oss) \
    if (!(cond)) \
    { \
        (oss) << errstream << std::endl; \
        return; \
    }


// -----------------------------------------------------------------------------
// Problem:
// Create a simple data structure to represent a hierarchy.  Write a parser to
// read files in the following format and store them in your hierarchy structure.
// Then write functions that print the hierarhcy using multiple traversal
// algorithms.
// 
// Example input file format (note that leading periods specify depth):
//
// grandpa & grandma
// .mom
// ..me
// ...my son
// ...my daughter
// ..my brother
// ..my sister
// ...my nephew
// .aunt gertrude
// ..my annoying cousin
//
// Make sure that you detect nonsensical structures in the input file.  For
// example, the first line should not contain any leading periods, and a line
// with one leading period cannot be followed by a line with more than two
// leading periods.
//
// Because the printing functions are external to your class, you'll need to
// choose what type of interface to expose for those functions to be simple.
//
// The logic for the printing functions should NOT be contained within the class.

class Node
{
private:
    string m_name;
    unsigned int m_level;
    list<Node*> m_children;
public:
    Node(string name, unsigned int level);
    string getName();
    unsigned int getLevel();
    list<Node*> children();
    void addChild(Node* child);
};


class Hierarchy
{

    // TODO: Implement this class
    Node* root;

public:
    Hierarchy();
    Node* getRoot() const;
    bool LoadFromFile(const string& infile);
};


void TestHierarchy(ostream& error_output);