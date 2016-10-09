/*
Driver that creates a gui in the console that displays the various functions the program can do currently.
Will more than likely be used for the first presentation for this project
*/

#include <iostream>
#include <string>
#include <fstream> 

#define ENUM
#include "Dictionary.h"

using namespace std;

string displayMenu()
{
	string message = 
		"-----Choose the function you would like to do-----\n"
		"1. Add word \n"
		"2. Add word with definition and type \n"
		"3. Display number of entries \n"
		"4. Save Dictionary \n"  
		"5. Exit \n";

	return message;
}

int main()
{
	// variables and objects
	Dictionary dic;
	wordType type = wordType::UNKNOWN;
	ifstream infile;
	ofstream outfile;
	string delimiter = "  ";

	int choice;
	string line = "";
	string inWord[3];
	string word = "";
	bool done = false;

	// load base dictionary (later)
//	infile.open("109583 Words.txt");
	infile.open("Dictionary.txt");

	std::cout << "Loading dictionary... \n";
	while (!infile.eof())
	{
		// Reset the little array
		inWord[0] = "";
		inWord[1] = "";
		inWord[2] = "";

		getline(infile, line);

		// If there is not 
		// Split the line into the two parts
		// From stackOverflow
		size_t pos = 0;
		int i = 0;
		while ((pos = line.find(delimiter)) != string::npos)
		{
			inWord[i] = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			i++;
		} // End while

		if (i < 3)
			inWord[i] = line;

		// Get the actual type from the enum
		if (inWord[1].compare("n") == 0)
		{
			type = wordType::NOUN;
		}
		else if (inWord[1].compare("v") == 0)
		{
			type = wordType::VERB;
		}
		else if (inWord[1].compare("adj") == 0)
		{
			type = wordType::ADJECTIVE;
		}
		else if (inWord[1].compare("adv") == 0)
		{
			type = wordType::ADVERB;
		}
		else if (inWord[1].compare("pro") == 0)
		{
			type = wordType::PRONOUN;
		}
		else if (inWord[1].compare("prep") == 0)
		{
			type = wordType::PREPOSITION;
		}
		else if (inWord[1].compare("c") == 0)
		{
			type = wordType::CONJUNCTION;
		}
		else if (inWord[1].compare("d") == 0)
		{
			type = wordType::DETERMINER;
		}
		else if (inWord[1].compare("e") == 0)
		{
			type = wordType::EXCLAMATION;
		}
		else if (inWord[1].compare("pref") == 0)
		{
			type = wordType::PREFIX;
		}
		else if (inWord[1].compare("s") == 0)
		{
			type = wordType::SUFFIX;
		}
		else
		{
			type = wordType::UNKNOWN;
		}

		if (!inWord[0].empty())
		{
			if (inWord[2].empty())
				dic.addEntry(inWord[0]);
			else
				dic.addEntry(inWord[0], type, inWord[2]);
		}
	} // End while

	infile.close();

	std::cout << "Done. \n\n";

	while (!done)
	{

		// display menu
		std::cout << displayMenu();
		std::cout << "Enter choice: "; std::cin >> choice;
		std::cout << "\n";

		// switch based on choice
		switch (choice)
		{
			case 1: // add word (completed)
			{
				word = "";
				std::cout << "Enter a word to enter into the dictionary: "; std::cin >> word;

				// enter it into the dictionary
				if (dic.addEntry(word))
				{
					std::cout << "Successfully added into the dictionary. \n";

				}
				else
					std::cout << "Entry is already in the dictionary. \n";

				break;
			}
			case 2: // Add word with definition and type (not completed)
			{
				word = "";
				string definition;
				int typeChoice;

				std::cout << "Enter a word to enter into the dictionary: "; std::cin >> word;
				std::cout << "Enter a definition for the word: "; std::cin.ignore(); getline(std::cin, definition);

				string typeMenu =
					"1.  Noun \n"
					"2.  Verb \n"
					"3.  Adjective \n"
					"4.  Adverb \n"
					"5.  Pronoun \n"
					"6.  Preposition \n"
					"7.  Conjunction \n"
					"8.  Determiner \n"
					"9.  Exclamation \n"
					"10. Prefix \n"
					"11. Suffix \n";

				std::cout << typeMenu;
				std::cout << "Enter a word type: "; std::cin >> typeChoice;

				switch (typeChoice)
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
				case 10:
					type = wordType::PREFIX;
					break;
				case 11:
					type = wordType::SUFFIX;
					break;
				default:
					type = wordType::UNKNOWN;
				} // end type switch

				if (dic.addEntry(word, type, definition))
					std::cout << "Word added successfully to the dictionary. \n";
				else
					std::cout << "Word is already in the dictionary. \n";

				break;

			}
			case 3: // display the number of entries (completed)
			{
				std::cout << "Number of entries: " << dic.getSize() << endl;
				break;
			}
			case 4: // save to dictionary.txt
			{
				outfile.open("Dictionary.txt");
				outfile << dic.printDictionary();
				outfile.close();
				std::cout << "Save successful. \n\n";

				break;
			}
			case 5:
			{
				done = true;
			}
			} // end switch
		} // end while

	std::cout << "Exited successfully. \n";
	std::system("pause");
	return 0;
}