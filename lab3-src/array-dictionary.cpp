
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include <string.h>

#include "array-dictionary.h"

// Constructor
ArrayDictionary::ArrayDictionary() {

	// Initialize Array Dictionary.
	_maxNumber = 1000;
	_currentNumber = 0;
	_array = new ArrayDictionaryNode[_maxNumber];
 
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record) {
        
	// Check if key exists and update data.
	int i = -1;
	for (; i++ < _currentNumber-1;) {

		// Check for match.
		if (!strcmp(_array[i]._key, key)) {

			// Update data and return.
			_array[i]._data = (DataType*)record;
			return false;

		}

	}

	// Key is not in array - add
	
	// Resize if needed.
	if (_currentNumber == _maxNumber) {

		// Double max size for O(n log n)
		int oldMax = _maxNumber;
		_maxNumber <<= 1;

		// Create temporal array and copy items.
		ArrayDictionaryNode* temp = new ArrayDictionaryNode[_maxNumber];
		int i = -1;
		for (; i++ < oldMax-1;) {

			// Copy item.
			temp[i]._key = (char*)malloc(sizeof(_array[i]._key));
			strcpy(temp[i]._key, _array[i]._key);
			temp[i]._data = new DataType;
			temp[i]._data = (DataType*)_array[i]._data;

		}

		// Clean up mess.
		delete[] _array;
		_array = temp;

	}

	// Add new element.
	_array[_currentNumber]._key = (char*)malloc(sizeof(key));
	strcpy(_array[_currentNumber]._key, key);
	_array[_currentNumber]._data = new DataType;
	_array[_currentNumber]._data = (DataType*)record;
	_currentNumber++;
	
	// Return.
	return true;

}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord( KeyType key) {
        
	// Check if array is empty.
	if (!_currentNumber) return NULL;

	// Iterate through array to find key.
	int i = -1;
	for(; i++ < _currentNumber-1;) {

		// Compare keys.
		if (!strcasecmp(_array[i]._key, key)) return (DataType)_array[i]._data;

	}

	// Not found.
	return NULL;

}

// Removes one element from the table
bool
ArrayDictionary::removeElement(KeyType key) {

	// Check if key is in array or if array is empty.
	DataType found = findRecord(key);
	if (found == NULL) return false;

	// Key is in array - move elements after key up one.
	int foundIndex = 0;
	int i = -1;
	ArrayDictionaryNode* temp = new ArrayDictionaryNode[_maxNumber];
	for (; i++ < _currentNumber-1;) {

		// Skip if found key.
		if (!strcmp(_array[i]._key, key)) continue;

		// If not - add to temp array.
		temp[foundIndex]._key = (char*)malloc(sizeof(char)*strlen(_array[i]._key));
		strcpy(temp[foundIndex]._key, _array[i]._key);
		temp[foundIndex]._data = new DataType;
		temp[foundIndex]._data = _array[i]._data;
		foundIndex++;

	}

	// Change array to temp, free allocated memory, and adjust.
	delete[] _array;
	_array = temp;
	_currentNumber--;
	
	// Return.
	return true;
	
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
ArrayDictionary::keys(int * n) {

	// Create temportal storage.
	KeyType* table = new KeyType[_currentNumber];

	// Copy table.
	int i = -1;
	for (; i++ < _currentNumber-1;) {

		// Copy
		table[i] = (char*)malloc(sizeof(_array[i]._key));
		strcpy((char*)table[i], _array[i]._key);

	}

	// Return n.
	*n = _currentNumber;
	return table;

}










