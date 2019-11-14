
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 
//
// The code in here is used for testing and debugging purposes. 
// Read it and understand it but you do not neet to modify it.

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "avl-dictionary.h"

//
// Goes over the nodes in the tree to verify that the height and keys 
// of the AVL tree are correct. It prints a message and exits if it is not a
// valid AVL tree.
//
void
AVLDictionary::check()
{
	checkRecursive(_root);
}

void
AVLDictionary::checkRecursive(AVLNode * node) {
	if (node == NULL) {
		return;
	}

	if (node->_left!=NULL) {
		// Make sure that it is sorted
		if ( strcmp(node->_key, node->_left->_key) <= 0) {
			fprintf(stderr,
				"*** NOT SORTED: parent->key=\"%s\" <= left->key=\"%s\"\n",
			       node->_key, node->_left->_key);
			assert(0);
		}
	}

	if (node->_right!=NULL) {
		// Make sure that it is sorted
		if ( strcmp(node->_key, node->_right->_key) >= 0) {
			fprintf(stderr,
				"*** NOT SORTED: parent->key=\"%s\" >= right->key=\"%s\"\n",
				node->_key, node->_right->_key);
			assert(0);
		}
	}

	checkRecursive(node->_left);
	checkRecursive(node->_right);

	// Check height
	int lHeight = 0;
	if (node->_left!=0) {
		lHeight = node->_left->_height;
	}

	int rHeight = 0;
	if (node->_right!=0) {
		rHeight = node->_right->_height;
	}

	int diff = lHeight - rHeight;
	if (diff<0) {
		diff = - diff;
	}

	if (diff>1) {
		fprintf(stderr,
			"*** HEIGHT DIFFERENCE > 1: key=\"%s\" lheight=%d rheight=%d\n",
			node->_key, lHeight, rHeight);
		assert(0);
	}

	// Compute height
	int maxHeight = lHeight;
	if (maxHeight<rHeight) {
		maxHeight = rHeight;
	}

	if (node->_height != maxHeight + 1) {
		fprintf(stderr,
			"*** WRONGH HEIGHT: key=\"%s\" height=%d should be %d\n",
			node->_key, node->_height, maxHeight + 1);
		assert(0);
	}
}

void
AVLDictionary::printNode(const char * s, AVLNode * node, int depth) {
	AVLNode *current = _root;

	for (int i = 0; i < depth; i++) {
		printf(" ");
	}

	if (node==NULL) {
		printf("%s:NULL\n", s);
		return;
	}

	printf("%s:key=\"%s\" data=%ld height=%d\n",
	       s, node->_key, (long) node->_data, node->_height);
	printNode("L", node->_left, depth+2);
	printNode("R", node->_right, depth+2);
}

void
AVLDictionary::print()
{
	printNode("ROOT", _root, 0);
}

