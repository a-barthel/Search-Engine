
// Implementation of a dictionary using a hash table

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash-dictionary.h"

// Constructor
HashDictionary::HashDictionary() {
  
	// Initialize buckets to null.
	int i = 0;
	for(;i<MaxBuckets;) _buckets[i++]=NULL;
}

int
HashDictionary::hash(KeyType key) {
  // Add your code here
  int sum = 0;
  int len = strlen(key);
  for (int i = 0; i < len; i++) {
		sum += i*key[i];
  }
  return sum%MaxBuckets;
}

// Add a record to the dictionary. Returns false if key already exists
bool
HashDictionary::addRecord( KeyType key, DataType record) {

	int hashKey = hash(key);
	HashNode* ent = _buckets[hashKey];
	for(;ent;ent=ent->_next) {

		if (!strcmp(ent->_key, key)) {ent->_data = record; return false;}

	}
	ent = new HashNode();
	ent->_key = strdup(key);
	ent->_data = record;
	ent->_next = _buckets[hashKey];
	_buckets[hashKey] = ent;
	_nElements++;
	return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
HashDictionary::findRecord( KeyType key) {
	int hashKey = hash(key);
	HashNode* ent = _buckets[hashKey];
	for(;ent;ent=ent->_next) if(!strcasecmp(ent->_key,key)) return (DataType)ent->_data;
	return NULL;
}

// Removes one element from the table
bool
HashDictionary::removeElement(KeyType key) {
	int hashKey = hash(key);
	HashNode* ent = _buckets[hashKey];
	HashNode* pre = NULL;
	for(;ent;ent=ent->_next) {
		if(!strcmp(ent->_key,key)) {
			if(pre) pre->_next = ent->_next;
			else _buckets[hashKey] = ent->_next;
			_nElements--;
			delete ent; return true;
		} pre = ent;
	}
	return false;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
HashDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(_nElements * sizeof(KeyType));

	*n = _nElements;
	int i = 0;
	for (int h = 0; h < MaxBuckets; h++) {
		HashNode * n = _buckets[h];
		while (n!=NULL) {
			a[i] = n->_key;
			i++;
			n = n->_next;
		}
	}
	*n = _nElements;
	return a;
}

