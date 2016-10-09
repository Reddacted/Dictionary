// Driver that tests all of the functions
// the Dictionary has to make sure they all work properly

#include <cstdlib>
#include <iostream>
#include <string>

#define ENUM
#include "Dictionary.h"

/*int main()
{
	Dictionary dic;
	string word;
	wordType type;
	string definition;
	int defNum;

	// First we will add a word with no definition or type
	word = "puppy";

	if (dic.addEntry(word))
		cout << "Test 01: SUCCESS" << endl;
	else
		cout << "Test 01: FAILED" << endl;

	cout << "------------------------------------" << endl;

	// Expect:
	// puppy  FAIL 0
	cout << dic.printDictionary() << endl;
	cout << "------------------------------------" << endl;

	// Second we will add a word with a definition and type
	word = "cat";
	type = wordType::NOUN;
	definition = "A feline";

	if (dic.addEntry(word, type, definition))
		cout << "Test 02: SUCCESS" << endl;
	else
		cout << "Test 02: FAILED" << endl;

	cout << "------------------------------------" << endl;

	// Expect:
	// cat  n A feline
	// puppy  FAIL 0
	cout << dic.printDictionary() << endl;
	cout << "------------------------------------" << endl;


	// Now fix "puppy" by adding its definition and type
	word = "puppy";
	type = wordType::NOUN;
	definition = "Cute little pet";

	if (dic.addDefinition(word, type, definition))
		cout << "Test 03: SUCCESS" << endl;
	else
		cout << "Test 03: FAILED" << endl;

	cout << "------------------------------------" << endl;

	// Expect:
	// cat  n A Feline
	// puppy  n Cute little pet
	cout << dic.printDictionary() << endl;
	cout << "------------------------------------" << endl;


	// Perhaps the definition for "puppy" was too subjective
	// So let's try changing it to a more objective one
	word = "puppy";
	type = wordType::NOUN;
	definition = "A canine";
	defNum = 0; // We know it's the first definition right now

	if (dic.changeDefinition(word, type, definition, defNum))
		cout << "Test 04: SUCCESS" << endl;
	else
		cout << "Test 04: FAILED" << endl;

	cout << "------------------------------------" << endl;

	// Expect:
	// cat  n A feline
	// puppy  n A canine
	cout << dic.printDictionary() << endl;
	cout << "------------------------------------" << endl;


	system("pause");
	return 0;
} */