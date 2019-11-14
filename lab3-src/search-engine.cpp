#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "search-engine.h"
#include "webcrawl.h"
struct timespec gettime;
int searches = 0;
float totalTime = 0.0;
SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
	// Create dictionary of the indicated type
	switch(dictionaryType) {
		case(ArrayDictionaryType): { _wordToURLList = new ArrayDictionary(); break; }
		case(HashDictionaryType): { _wordToURLList = new HashDictionary(); break; }
		case(AVLDictionaryType): { _wordToURLList = new ArrayDictionary(); break; }
		case(BinarySearchDictionaryType): { _wordToURLList = new BinarySearchDictionary(); break; }
		default: _wordToURLList = NULL;
	}
	// Populate dictionary and sort it if necessary
	URLRecord** record = new URLRecord*[1024];
	int i = 0;
	for(;i<1024;) record[i++] = new URLRecord();
	FILE* readURL = fopen("url.txt", "r");
	char* indexURL = new char[512];
	for(; fgets(indexURL, 512, readURL);) {
		if(strcmp(indexURL, "\n")) {
			char* line = new char[512];
			line = strtok(indexURL, " \n");
			int index = atoi(line);
			line = strtok(NULL, " \n");
			char* url = new char[512];
			strcpy(url, line);
			fgets(indexURL, 512, readURL);
			char* des = new char[512];
			line = strtok(indexURL, "\n");
			strcpy(des, line);
			record[index]->_url = url;
			record[index]->_description = des;
		}
	}
	delete[] indexURL; fclose(readURL);
	FILE* readWord = fopen("word.txt", "r");
	char* wordList = new char[512];
	for(;fgets(wordList, 512, readWord);) {
		if(strcmp(wordList, "\n")) {
			char* line = new char[512];
			line = strtok(wordList, " \n");
			char* word = new char[100];
			strcpy(word, line);
			URLRecordList* root = NULL;
			URLRecordList* prev = NULL;
			line = strtok(NULL, " \n");
			for(; line ;) {
				int pos = atoi(line);
				if(record[pos]->_url==NULL) continue;
				URLRecordList* ent = new URLRecordList();
				if(root==NULL) root = ent;
				ent->_urlRecord = record[pos];
				ent->_next = NULL;
				if(prev!=NULL) prev->_next = ent;
				prev = ent;
				line = strtok(NULL, " \n");
			}
			_wordToURLList->addRecord(word, (URLRecordList*)root);
			delete word; delete line;
		}
	}
	delete wordList; fclose(readWord);
}


void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
  if (strcmp(documentRequested, "/")==0) {
    // Send initial form
    fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
    fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
    fprintf(fout, "<H2>\n");
    fprintf(fout, "<FORM ACTION=\"search\">\n");
    fprintf(fout, "Search:\n");
    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
    fprintf(fout, "</H2>\n");
    fprintf(fout, "</FORM></CENTER>\n");
    return;
  }

  // TODO: The words to search in "documentRequested" are in the form
  // /search?word=a+b+c
  //
  // You need to separate the words before search
  // Search the words in the dictionary and find the URLs that
  // are common for al the words. Then print the URLs and descriptions
  // in HTML. Make the output look nicer.

  // Here the URLs printed are hardwired
  //printf("%s\n", documentRequested);
  for(;*documentRequested++!='=';);
  char* request = (char*)documentRequested; // Cause man strtok...
  printf("%s\n", request);
  char** searchWords = new char*[69];
  int i = 0;
  for(;i<69;) searchWords[i++] = NULL;
  i = 0;
  const char* plus = "+";
  char* word = strtok(request, plus);
  for(; word!=NULL;) {
  	searchWords[i] = new char[50]; 
	  strcpy(searchWords[i], word); 	
	  word = strtok(NULL,plus); // Cause man strtok...
	  i++;
  } 
  char* search = new char[69*50];
  strcpy(search, "");
  int j = 0;
  for (; j<i;j++) {
	  strcat(search, searchWords[j]);
	  if (j < i-1) strcat(search, " ");
  }
  printf("%s\n", search);
  



  const int nurls=2;

  const char * words = "data structures";

  const char * urls[] = {
    "http://www.cs.purdue.edu",
    "http://www.cs.purdue.edu/homes/cs251"
  };
  
  const char * description[] = {
    "Computer Science Department. Purdue University.",
    "CS251 Data Structures"
  };
  





  long int start, finish;
  clock_gettime(CLOCK_REALTIME, &gettime);
  start = gettime.tv_nsec;
  float startMS = (start+0.0)/1000000;
  int matches = 0;
  int listCount = 0;
  URLRecord** list = new URLRecord*[100];
  int index = 0;
  for(;index<j;index++) {
		printf("%d\n", index);
		printf("%s\n", searchWords[index]);
		URLRecordList* data = (URLRecordList*)_wordToURLList->findRecord(searchWords[index]);
		for(;data;) {
			int flag = 0;
			int k = 0;
			for(;k<listCount;k++) {
				if(list[k]==data->_urlRecord) {flag = 1; break;}
				//if(!flag) records[count++]=data->_urlRecord;
				//data=data->_next
			}
			if(!flag) { matches++;  list[listCount++]=data->_urlRecord; }
			data=data->_next;
		}
  }
  printf("%d\n", j);
  printf("%d\n", listCount);
  //printf("%s\n", list[0]->_url);
  index = 0;
  for (; index<listCount; index++) {
	int k = 0;
	for(;k<j;k++) {
		URLRecordList* data = (URLRecordList*)_wordToURLList->findRecord(searchWords[k]);
		int flag = 0;
		for(;data;) {
			if(data->_urlRecord==list[index]) flag = 1;
			data = data->_next;
		}
		if(!flag) list[index]=NULL;
	}
  }
  /*
  int loop = 0;
  for(;loop<listCount;loop++) {
	if(!list[loop]) continue;
	printf("%s\n", list[loop]->_url);
  }*/





  clock_gettime(CLOCK_REALTIME, &gettime);
  finish = gettime.tv_nsec;
  float finishMS = (finish+0.0)/1000000;
  totalTime += (finishMS-startMS);
  searches++;
  printf("%f\n", finishMS - startMS);
  printf("%s\n", search);
  fprintf( stderr, "Search for words: \"%s\"\n", search);
  //if(!strcmp(search, "Go IU")) "<H1> FUCK YOU YOU CUNT </H1>\n";
  fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
  fprintf( fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
  //if(!strcmp(search, "Go IU")) "<H2> FUCK YOU YOU CUNT </H2>\n";
  fprintf( fout, "<H2> Search Results for \"%s\"</center></H2>\n", search );
  fprintf( fout, "<H5> Search time: %f ms </H5>\n", finishMS - startMS);
  fprintf( fout, "<H5> Average time: %f ms </H5>\n", totalTime / searches);
  if(!strcmp(search, "Go IU")) fprintf(fout, "<H5> FUCK YOU YOU CUNT </H5>\n");
  printf("%d\n", matches);
  //if(matches==0) goto SKIP;
  if(!matches) fprintf( fout, "<h4> Sorry...No results found.</h4>\n");
  for ( int i = 0, j = 0; i < listCount; i++ ) {
    //if(!matches) { fprintf( fout, "<h3> Sorry...No results found.</h3>\n");break;}
    if(!list[i]) { continue;} //So we can match two or more words - I made this null earlier.
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", j+1, list[i]->_url, list[i]->_url );
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", list[i]->_description );
    j++;
  }
  SKIP:
  // Add search form at the end
  fprintf(fout, "<HR><H2>\n");
  fprintf(fout, "<FORM ACTION=\"search\">\n");
  fprintf(fout, "Search:\n");
  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
  fprintf(fout, "</H2>\n");
  fprintf(fout, "</FORM>\n");
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | avl | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }

  // Get port
  int port;
  sscanf( argv[1], "%d", &port);

  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
  }
  else if (!strcmp(dictType, "avl")) {
    dictionaryType = AVLDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }
  
  SearchEngine httpd(port, dictionaryType);
  
  httpd.run();

  return 0;
}
