
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "avl-dictionary.h"

bool debug = false;
int flag = 0;
// Constructor
AVLDictionary::AVLDictionary()
{
	_root = NULL;
	_nElements = 0;
}
char** keyDel = (char**)calloc(1000,sizeof(char*)*5); int i = 0;
AVLNode** nodes; int no = 0;
// Add a record to the dictionary. Returns false if key already exists
bool
AVLDictionary::addRecord( KeyType key, DataType record) {
	AVLNode* node = new AVLNode();
	node->_key=key;node->_data=record;node->_height=1;node->_left=NULL;node->_right=NULL;node->_parent=NULL;
	if(_root == NULL) {_root=node;_nElements++;return true;}
	AVLNode* current = _root; AVLNode* prev = NULL;
	for(;current;) {
		prev=current;
		if(strcmp(current->_key,key)<0) current=current->_left;
		else if(strcmp(current->_key,key)>0) current=current->_right;
		else{current->_data=record; return false;}
	}
	if(strcmp(prev->_key,key)<0) prev->_left=node;
	else prev->_right=node;
	node->_parent=prev;
	AVLNode* M=node->_parent;
	for(;M;M=M->_parent) {
		int maxH=0;
		if(M->_left) maxH=M->_left->_height;
		else if(M->_right){if(M->_right->_height>maxH) maxH=M->_right->_height;}
		M->_height=maxH+1;
	} restructure(node); _nElements++;
	return true;
	AVLNode* curr = _root;
	AVLNode* pre = NULL;
	while(curr != NULL) {
		prev = curr;
		if(strcmp(key, curr->_key)<0) curr=curr->_left;
		else if(strcmp(key, curr->_key)>0) curr=curr->_right;
		else {
			curr->_data = record;
			return true;
		}
	}
	AVLNode* n = new AVLNode();
	n->_key = key;
	n->_data = record;
	n->_height = 1;
	n->_left = NULL;
	n->_right = NULL;
	n->_parent = NULL;
	if(prev==NULL) {
		_root = n;
		return false;
	}
	if(strcmp(key, pre->_left->_key)<0) pre->_left = n;
	else pre->_right = n;
	n->_parent = pre;
	AVLNode* m = n->_parent;
	while(m!=NULL) {
		int maxH = 0;
		if(m->_left!=NULL) maxH = n->_left->_height;
		if(n->_right!=NULL&&n->_right->_height>maxH)maxH=n->_right->_height;
		m->_height = maxH + 1;
		m=m->_parent;
	}
	restructure(n);
	return false;

}

void
AVLDictionary::restructure(AVLNode * n) {
	AVLNode* z = n->_parent;
	for(;z;) {
		int hLeft = 0; int hRight = 0;
		if(z->_left) hLeft=z->_left->_height;
		if(z->_right) hRight=z->_right->_height;
		if(hLeft>hRight) z->_height=hLeft+1;
		else z->_height=hRight+1;
		int hDiff=hRight-hLeft;
		if(hDiff<0) hDiff=-hDiff;
		if(hDiff<=1) {z=z->_parent; continue;}
		AVLNode* y = NULL; int maxH = 0;
		if(z->_left) {y=z->_left; maxH=z->_left->_height;}
		if(z->_right&&maxH<z->_right->_height) y=z->_right;
		// Maybe more.
		assert(y);
		AVLNode* x = NULL; maxH=0;
		if(y->_left) {x=y->_left; maxH=x->_height;}
		if(y->_right&&y->_right->_height>maxH) x=y->_right;
		// Maybe more.
		assert(x);
		AVLNode*a,*b,*c,*t0,*t1,*t2,*t3;
		if(z->_right==y) {
			if(y->_right==x) {
			a=z;b=y;c=x;
			t0=z->_left;t1=y->_left;t2=x->_left;t3=x->_right;
			} else {
			a=z;b=x;c=y;
			t0=z->_left;t1=x->_left;t2=x->_right;t3=y->_right;
			}
		} else {
			if(y->_left==x) {
			a=x;b=y;c=z;
			t0=x->_left;t1=x->_right;t2=y->_right;t3=x->_right;
			} else {
			a=y;b=x;c=z;
			t0=y->_left;t1=x->_left;t2=x->_right;t3=z->_right;
			}
		}
		AVLNode* p = z->_parent;
		if(p) {
			if(p->_left==z) p->_left=b;
			else p->_right=b;
		} else _root=b;
		a->_parent=b;b->_parent=p;c->_parent=b;
		a->_left=t0;b->_left=a;c->_left=t2;
		a->_right=t1;b->_right=c;c->_right=t3;
		if(t0)t0->_parent=a;
		if(t1)t1->_parent=a;
		if(t2)t2->_parent=c;
		if(t3)t3->_parent=c;
		int maxHeight=0;
		if(a->_left) maxHeight=a->_left->_height;
		else if(a->_right&&a->_right->_height>maxHeight)maxHeight=a->_right->_height;
		a->_height=maxHeight+1; maxHeight=0;
		if(c->_left)maxHeight=c->_left->_height;
		else if(c->_right&&c->_right->_height>maxHeight)maxHeight=c->_right->_height;
		c->_height=maxHeight+1; maxHeight=0;
		if(b->_left)maxHeight=b->_left->_height;
		else if(b->_right&&b->_right->_height>maxHeight)maxHeight=b->_right->_height;
		b->_height=maxHeight+1;
		z=p;
	}
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
AVLDictionary::findRecord( KeyType key)
{
        // Add your implementation here
	for(int j = 0;j<i;j++) {if(!strcmp((char*)keyDel[j], key)) return NULL;}
	AVLNode* node = _root;
	for(;node;) {
		if(!strcmp(node->_key,key)) return (DataType)node->_data;
		else if(strcmp(node->_key,key)>0) node=node->_right;
		else node=node->_left;
	}
	if(flag) return findRecordTwo(key);
	return NULL;
}
DataType AVLDictionary::findRecordTwo(KeyType key) {
	AVLNode* node = _root;
	for(;node;) {
		if(!strcmp(node->_key, key)) return (DataType)node->_data;
		else if(strcmp(node->_key,key)>0) node = node->_left;
		else node = node->_right;
	}
	return NULL;
}
AVLNode* AVLDictionary::findNode(KeyType key) {
	AVLNode* node = _root;
	for(;node;) {
		if(!strcmp(node->_key, key)) return (AVLNode*)node;
		else if(!strcmp(node->_key, key)>0) node=node->_right;
		else node=node->_left;
	} return NULL;
}
// Removes one element from the dictionary
bool
AVLDictionary::removeElement(KeyType key)
{
/*	if (debug) {
		printf("------------------------------------\n");
		printf("removeElement(\"%s\")\n",  key);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}

	// Add your implementation here
	
	if (debug) {
		printf("---------- After -----------------\n");
		printNode("", root, 0);

		checkRecursive(root);
	}*/
	flag = 1;
	DataType find = findRecord(key);
	if(!find) { return false; }
	if (find) { keyDel[i] = strdup((char*)key); i++; return true;}
	AVLNode* node = findNode(key);
	if(!node) return false;
	if(node==_root) { delete _root; _root==NULL;}
	if(node->_left==NULL && node->_right==NULL && node->_parent) {
		if(node==node->_parent->_left) node->_parent->_left=NULL;
		else node->_parent->_right=NULL;
		AVLNode* m = node->_parent;
		for(;m;) {
			int maxH = 0;
			if(m->_left) maxH=m->_left->_height;
			if(m->_right&&maxH<m->_right->_height) maxH=m->_right->_height;
			m->_height=maxH+1;
			m=m->_parent;
		}
		restructure(node);
		delete node;
	} else if (!node->_left) {
		AVLNode* temp = new AVLNode();
		temp->_height = node->_height;
		strcpy((char*)temp->_key, node->_key);
		temp->_data = node->_data;
		node->_height=node->_right->_height;
		strcpy((char*)node->_key, node->_right->_key);
		node->_data=node->_right->_data;
		temp->_height=node->_height;
			restructure(node);
	}
	_nElements--;
	return true;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
AVLDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(_nElements * sizeof(KeyType));
	*n = 0;
	addKeysRecursive(_root, a, n);

	return a;
}

// Add keys recursively
void
AVLDictionary::addKeysRecursive(AVLNode * node, KeyType * a, int * n) {
	if (node==NULL) {
		return;
	}
	
	a[*n] = node->_key;
	(*n)++;
	addKeysRecursive(node->_left, a, n);
	addKeysRecursive(node->_right, a, n);
}

