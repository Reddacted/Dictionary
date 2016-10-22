// Driver that tests all of the functions
// the Dictionary has to make sure they all work properly

#include <cstdlib>
#include <iostream>
#include <string>

#include "Dictionary.h"

static int test()
{
	Dictionary dic;
	std::string word;
	wordType type;
	std::string definition;
	int defNum;

	// First we will add a word with no definition or type
	word = "puppy";

	if (dic.addEntry(word))
		std::cout << "Test 01: SUCCESS" << std::endl;
	else
		std::cout << "Test 01: FAILED" << std::endl;

	std::cout << "------------------------------------" << std::endl;

	// Expect:
	// puppy  FAIL 0
	std::cout << dic.printDictionary() << std::endl;
	std::cout << "------------------------------------" << std::endl;

	// Second we will add a word with a definition and type
	word = "cat";
	type = wordType::NOUN;
	definition = "A feline";

	if (dic.addEntry(word, type, definition))
		std::cout << "Test 02: SUCCESS" << std::endl;
	else
		std::cout << "Test 02: FAILED" << std::endl;

	std::cout << "------------------------------------" << std::endl;

	// Expect:
	// cat  n A feline
	// puppy  FAIL 0
	std::cout << dic.printDictionary() << std::endl;
	std::cout << "------------------------------------" << std::endl;


	// Now fix "puppy" by adding its definition and type
	word = "puppy";
	type = wordType::NOUN;
	definition = "Cute little pet";

	if (dic.addDefinition(word, type, definition))
		std::cout << "Test 03: SUCCESS" << std::endl;
	else
		std::cout << "Test 03: FAILED" << std::endl;

	std::cout << "------------------------------------" << std::endl;

	// Expect:
	// cat  n A Feline
	// puppy  n Cute little pet
	std::cout << dic.printDictionary() << std::endl;
	std::cout << "------------------------------------" << std::endl;


	// Perhaps the definition for "puppy" was too subjective
	// So let's try changing it to a more objective one
	word = "puppy";
	type = wordType::NOUN;
	definition = "A canine";
	defNum = 0; // We know it's the first definition right now

	if (dic.changeDefinition(word, type, definition, defNum))
		std::cout << "Test 04: SUCCESS" << std::endl;
	else
		std::cout << "Test 04: FAILED" << std::endl;

	std::cout << "------------------------------------" << std::endl;

	// Expect:
	// cat  n A feline
	// puppy  n A canine
	std::cout << dic.printDictionary() << std::endl;
	std::cout << "------------------------------------" << std::endl;


	system("pause");
	return 0;
}