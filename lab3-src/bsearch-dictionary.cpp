
// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bsearch-dictionary.h"

// Constructor
BinarySearchDictionary::BinarySearchDictionary() {
	
	// Set sort flag.
	_sorted = false;

}

bool
BinarySearchDictionary::addRecord( KeyType key, DataType record) {
	
	// Add record and set flag.
	_sorted = false;
	return ArrayDictionary::addRecord(key, record);

}

// Find a key in the dictionary and return corresponding record or NULL
DataType
BinarySearchDictionary::findRecord( KeyType key) {

	// Sort if needed.
	if (!_sorted) {
		sort();
		_sorted = true;
	}
	
	// Use binary search
	int min = 0;
	int max = _currentNumber-1;

	// ALGORITHM
	while (max >= min) {

		// find middle and check if it is a match.
		int mid = (min + max) / 2;
		int match = strcasecmp(_array[mid]._key, key);

		// Adjust accordingly.
		/*switch(match) {

			case(0): return (DataType)_array[mid]._data;
			default: {

				// Check for < vs >
				if (match > 0) min = mid + 1;
				else max = mid - 1;

			}

		}*/
		if (match==0) return (DataType)_array[mid]._data;
		else if (match>0) max = mid - 1;
		else min = mid + 1;

	}

	return NULL;

}


// Sort array using heap sort
void
BinarySearchDictionary::sort() {

	// Sort.
	ArrayDictionaryNode temp;

	// Simulate heap.
	int i;
	for(i = _currentNumber / 2; i >= 0; i--) shift(i, _currentNumber - 1);
	for(i = _currentNumber-1; i >= 1; i--) {

		// Simulate heap insert.
		temp = _array[0];
		_array[0] = _array[i];
		_array[i] = temp;
		shift(0, i - 1);

	}

}

void BinarySearchDictionary::shift(int first, int last) {

	// Local vars needed.
	int finish = 0;
	int max;
	ArrayDictionaryNode temp;

	// Shift.
	while ((first * 2) <= last && !finish) {

		if ((first * 2) == last) max = (first * 2);
		else if (strcmp(_array[(first * 2)]._key, _array[(first * 2) + 1]._key) > 0) max = (first * 2);
		else max = (first * 2) + 1;

		if (strcmp(_array[first]._key, _array[max]._key) < 0) {

			temp = _array[first];
			_array[first] = _array[max];
			_array[max] = temp;
			first = max;

		} else finish = 1;

	}

}







