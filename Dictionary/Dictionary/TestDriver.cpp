// Driver that tests all of the functions
// the Dictionary has to make sure they all work properly

#include <cstdlib>
#include <iostream>
#include <string>

#define ENUM
#include "Dictionary.h"

int main()
{
	Dictionary dic;
	string word;
	string definition;
	wordType type;

	// First we will add a word with no definition or type
	word = "puppy";

	if (dic.addEntry(word))
		cout << "Test 01: SUCCESS" << endl;
	else
		cout << "Test 01: FAILED" << endl;

	cout << dic.printDictionary;

	system("pause");
	return 0;
}