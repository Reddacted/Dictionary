// Driver for hash table

// NO ONE CAN REMEMBER DAT SHYT
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <stdio.h>
#include <locale>

#define ENUM
#include "Dictionary.h"

using namespace std;

// Input words from a txt file list (one word per line)
// Also assume (for now) that all words are nouns and
// there is a generic definition for each
Dictionary dic;
ifstream inFile;
string word;

// --------
// addWord
// --------
// Allows for user input to add to the dictionary.
// Not currently used in the final program version right now,
// but can be used when necessary.
// ----------------------------------------------------------
// return		void
static void addWord()
{
	wordType type; // uses the enum wordType to allow users to select the word type
	int choice = 0; // variable used for the case statement
	string def;
	bool done = true;

	std::cout << "Enter word: ";
	std::cin >> word;

	std::cout << "Enter word type: \n" 
			"1. Noun \n"
			"2. Verb \n"
			"3. Adjective \n"
			"4. Adverb \n"
			"5. Pronoun \n"
			"6. Preposition \n"
			"7. Conjunction \n"
			"8. Determiner \n"
			"9. Exclamation \n"
			"Choice: ";
	
	// checks input to see if it's not a number
	while (!(std::cin >> choice)) 
	{
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "Invalid input; please re-enter.\n";
	}

	switch (choice) // determines type of word
	{
		case 1:
			type = wordType::NOUN;
			break;
		case 2:
			type = wordType::VERB;
			break;
		case 3:
			type = wordType::ADJECTIVE;
			break;
		case 4:
			type = wordType::ADVERB;
			break;
		case 5:
			type = wordType::PRONOUN;
			break;
		case 6:
			type = wordType::PREPOSITION;
			break;
		case 7:
			type = wordType::CONJUNCTION;
			break;
		case 8:
			type = wordType::DETERMINER;
			break;
		case 9:
			type = wordType::EXCLAMATION;
			break;
	} // end case

	std::cout << "Enter definition: ";
	std::cin >> def;

	dic.addItem(word, type, def);

	std::cout << choice << word << def << endl;
}

int main()
{
//	Dictionary dict;
//	string cat = "cat";
//	 open up from txt file

	inFile.open("2of12.txt");
	while (!inFile.eof()) // To get you all the lines
	{
		getline(inFile, word); // Saves the line in word
		dic.addItem(word, wordType::NOUN, "A DEFINITION");

	} // End while

	inFile.close();

//	addWord(); // calls the function for user input

	dic.printTable(); 

	/*cout << "Hash value = " << dict.hash(cat, wordType::NOUN) << endl;
	dict.addItem(cat, wordType::NOUN, "kitty");
	dict.printTable(); */
	system("pause");

	return 0;
}