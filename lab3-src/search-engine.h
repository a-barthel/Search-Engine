
#include "minihttpd.h"
#include "dictionary.h"
#include "array-dictionary.h"
#include "hash-dictionary.h"
#include "bsearch-dictionary.h"
#include "avl-dictionary.h"

// Types of dictionaries used
enum DictionaryType {
  ArrayDictionaryType,
  HashDictionaryType,
  AVLDictionaryType,
  BinarySearchDictionaryType
};

// Inherits from MiniHTTPD
class SearchEngine : public MiniHTTPD {
  Dictionary * _wordToURLList;
  
  // Add any other member variables you need
 public:
  // Constructor for SearchEngine
  SearchEngine( int port, DictionaryType dictionaryType);
  char* toLower(char* line);
  // Called when a request arrives
  void dispatch( FILE * out, const char * requestLine );

};



