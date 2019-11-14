
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 

#include "dictionary.h"

struct AVLNode {
	KeyType _key;
	DataType _data;
	AVLNode * _parent;
	AVLNode * _left;
	AVLNode * _right;
	int _height;
};

class AVLDictionary : public Dictionary {
  // Add any member variables you need
	AVLNode * _root;
	int _nElements;
public:
  // Constructor
  AVLDictionary();
  AVLNode* findNode(KeyType key);
  // Restrcture tree starting at "node"
  void restructure(AVLNode * node);
  
  // Add a record to the dictionary. Returns false if key already exists
  bool addRecord( KeyType key, DataType record);
  
  // Find a key in the dictionary and return corresponding record or NULL
  DataType findRecord( KeyType key);
  DataType findRecordTwo(KeyType key);
  // Removes one element from the table
  bool removeElement(KeyType key);

  // Returns all the elements in the table as an array of strings.
  // *n is the size of the table and it is returned by reference
  KeyType * keys(int * n);

  void addKeysRecursive(AVLNode * node, KeyType * a, int * n);

  void check();
  
  void checkRecursive(AVLNode * node);

  // Print a node and children
  void printNode(const char * s, AVLNode * node, int depth);

  void print();

};

