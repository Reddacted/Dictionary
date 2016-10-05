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
	string line;
	string type;
	string delimiter = "  ";
	wordType wordType;

	inFile.open("Words With Type.txt");
	while (!inFile.eof()) // To get you all the lines
	{
		getline(inFile, line); // Saves the line in word
		
		// Split the line into the two parts
		size_t pos = 0;
		while ((pos = line.find(delimiter)) != string::npos)
		{
			word = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			type = line;
		}


		// Get the actual type from the enum
		if (type.compare("n") == 0)
		{
			wordType = wordType::NOUN;
		}
		else if (type.compare("v") == 0)
		{
			wordType = wordType::VERB;
		}
		else if (type.compare("adj") == 0)
		{
			wordType = wordType::ADJECTIVE;
		}
		else if (type.compare("adv") == 0)
		{
			wordType = wordType::ADVERB;
		}
		else if (type.compare("pro") == 0)
		{
			wordType = wordType::PRONOUN;
		}
		else if (type.compare("pre") == 0)
		{
			wordType = wordType::PREPOSITION;
		}
		else if (type.compare("c") == 0)
		{
			wordType = wordType::CONJUNCTION;
		}
		else if (type.compare("d") == 0)
		{
			wordType = wordType::DETERMINER;
		}
		else if (type.compare("e") == 0)
		{
			wordType = wordType::EXCLAMATION;
		}
		else
		{
			wordType = wordType::NOUN;
		}
		

		// Put the two parts into the function, still with
		// a generic definition
		dic.addItem(word, wordType, "A DEFINITION");

	} // End while

	inFile.close();

//	addWord(); // calls the function for user input

//	dic.printTable();
	dic.printDictionary();

	/*cout << "Hash value = " << dict.hash(cat, wordType::NOUN) << endl;
	dict.addItem(cat, wordType::NOUN, "kitty");
	dict.printTable(); */
	system("pause");

	return 0;
}