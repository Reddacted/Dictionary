/*
Driver that creates a gui in the console that displays the various functions the program can do currently.
Will more than likely be used for the first presentation for this project
*/

#include <iostream>
#include <string>
#include <fstream> 
#include <time.h>
#include <chrono>
#include <ctime>
#include <iomanip>


#include "Dictionary.h"
//#include "DictionaryArrayUnsorted.h"


// Clears the screen to keep things neat
static void screenClear(int numLines)
{
	// Clears the screen by simply sending a bunch of newlines
	for (int i = 0; i < numLines; i++) std::cout << std::endl;
}

// This is for console display only since the saved file stores
// the types as shorthand strings (i.e. "Noun" is "n")
static std::string typeToString(wordType type)
{
	std::string typeAsString;
	switch (type)
	{
	case wordType::NOUN:
	{
		typeAsString = "Noun";
		break;
	}
	case wordType::VERB:
	{
		typeAsString = "Verb";
		break;
	}
	case wordType::ADJECTIVE:
	{
		typeAsString = "Adjective";
		break;
	}
	case wordType::ADVERB:
	{
		typeAsString = "Adverb";
		break;
	}
	case wordType::PRONOUN:
	{
		typeAsString = "Pronoun";
		break;
	}
	case wordType::PREPOSITION:
	{
		typeAsString = "Preposition";
		break;
	}
	case wordType::CONJUNCTION:
	{
		typeAsString = "Conjunction";
		break;
	}
	case wordType::DETERMINER:
	{
		typeAsString = "Determiner";
		break;
	}
	case wordType::EXCLAMATION:
	{
		typeAsString = "Exclamation";
		break;
	}
	case wordType::PREFIX:
	{
		typeAsString = "Prefix";
		break;
	}
	case wordType::SUFFIX:
	{
		typeAsString = "Suffix";
		break;
	}
	case wordType::ABBREVIATION:
	{
		typeAsString = "Abbreviation";
		break;
	}
	default:
	{
		typeAsString = "UNKNOWN";
	}
	} // End switch

	return typeAsString;
}


static wordType stringToType(std::string typeAsString)
{
	wordType type;
	// Get the actual type from the enum
	if (typeAsString.compare("n") == 0)
	{
		type = wordType::NOUN;
	}
	else if (typeAsString.compare("v") == 0)
	{
		type = wordType::VERB;
	}
	else if (typeAsString.compare("adj") == 0)
	{
		type = wordType::ADJECTIVE;
	}
	else if (typeAsString.compare("adv") == 0)
	{
		type = wordType::ADVERB;
	}
	else if (typeAsString.compare("pro") == 0)
	{
		type = wordType::PRONOUN;
	}
	else if (typeAsString.compare("prep") == 0)
	{
		type = wordType::PREPOSITION;
	}
	else if (typeAsString.compare("c") == 0)
	{
		type = wordType::CONJUNCTION;
	}
	else if (typeAsString.compare("d") == 0)
	{
		type = wordType::DETERMINER;
	}
	else if (typeAsString.compare("e") == 0)
	{
		type = wordType::EXCLAMATION;
	}
	else if (typeAsString.compare("pref") == 0)
	{
		type = wordType::PREFIX;
	}
	else if (typeAsString.compare("s") == 0)
	{
		type = wordType::SUFFIX;
	}
	else if (typeAsString.compare("abbr") == 0)
	{
		type = wordType::ABBREVIATION;
	}
	else
	{
		type = wordType::UNKNOWN;
	}

	return type;
}


static wordType chooseType()
{
	std::string typeMenu =
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
		"11. Suffix \n"
		"12. Abbreviation \n";

	int choice;
	std::cout << typeMenu;
	std::cout << "Enter a word type: "; std::cin >> choice;

	wordType type;

	switch (choice)
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
	case 12:
		type = wordType::ABBREVIATION;
		break;
	default:
		type = wordType::UNKNOWN;
	} // end type switch

	return type;
}

// Displays the menu for the program
static std::string displayMenu()
{
	std::string message =
		"-----Choose the function you would like to do-----\n"
		"1. Add word \n"
		"2. Add word with definition and type \n"
		"3. Change a definition \n"
		"4. Find word \n"
		"5. Display number of entries \n"
		"6. Save Dictionary \n"  
		"7. Exit \n";

	return message;
}


static int consoleGUI()
{
	// variables and objects
//	DictionaryArrayUnsorted dic;
	Dictionary dic;
	wordType type = wordType::UNKNOWN;
	std::ifstream infile;
	std::ofstream outfile;
	std::string delimiter = "  ";
	const int SCREEN_HEIGHT = 25;

	int choice;
	std::string line = "";
	std::string inWord[3];
	std::string word = "";

	// load base dictionary
//	infile.open("109583 Words.txt");
	infile.open("Dictionary.txt");

	// records current time 
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now(); 

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
		while ((pos = line.find(delimiter)) != std::string::npos)
		{
			inWord[i] = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			i++;
		} // End while


		// When the last loop ends, this will grab the last part
		if (i < 3)
			inWord[i] = line;

		// Convert the string type to wordType
		type = stringToType(inWord[1]);

		if (!inWord[0].empty())
		{
			if (inWord[2].empty())
				dic.addEntry(inWord[0]);
			else
				dic.addEntry(inWord[0], type, inWord[2]);
		}
	} // End while

	infile.close();

	// records ending time and calculates how much time has passed since the start 
	end = std::chrono::system_clock::now(); 
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "Done. \n\n";
	std::cout << std::setprecision(3) << std::fixed;
	std::cout << "Time: " << elapsed_seconds.count() << " seconds\n\n";
	screenClear(SCREEN_HEIGHT - 14);

	// displays a looping menu to utilize the various functions 
	bool done = false;
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

				screenClear(SCREEN_HEIGHT - 10);
				break;
			}
			case 2: // Add word with definition and type
			{
				word = "";
				std::string definition;

				std::cout << "Enter a word to enter into the dictionary: "; std::cin >> word;
				std::cout << "Enter a definition for the word: "; std::cin.ignore(); getline(std::cin, definition);
				type = chooseType();

				if (dic.addEntry(word, type, definition))
					std::cout << "Word added successfully to the dictionary.";
				else
					std::cout << "Word is already in the dictionary.";

				screenClear(SCREEN_HEIGHT - 9);
				break;

			}
			case 3:
			{
				word = "";
				std::string definition;

				std::cout << "Enter the word you want to change the definition for: "; std::cin >> word;

				// Find the definition
				std::string wordDef = dic.getDefinition(word);

				if (wordDef.compare("FAILED") == 0)
				{
					std::cout << "Word not in the dictionary.";
					screenClear(SCREEN_HEIGHT - 8);
					break;
				}

				// Find the word type
				type = dic.getType(word);
				std::string stringType;
				stringType = typeToString(type);

				std::cout << "Entry:\n"
					<< "--------------\n"
					<< "Word: " << word << "\n"
					<< "Type: " << stringType << "\n"
					<< "Definition: " << wordDef << "\n\n";

				int defChoice;
				std::cout << "Choose the definition to replace (0-x): "; std::cin >> defChoice;

				std::cout << "Enter a definition for the word: "; std::cin.ignore(); getline(std::cin, definition);
				type = chooseType();

				if (dic.changeDefinition(word, type, definition, defChoice))
					std::cout << "Defininition change successful.";
				else
					std::cout << "Defininition change failed.";

				screenClear(SCREEN_HEIGHT - 9);
				break;
			}
			case 4:
			{
				word = "";

				std::cout << "Enter a word to get its entry: "; std::cin >> word;

				// Start time here
				start = std::chrono::system_clock::now();

				// Find the definition
				std::string wordDef = dic.getDefinition(word);

				if (wordDef.compare("FAILED") == 0)
				{
					std::cout << "Word not in the dictionary.";
					screenClear(SCREEN_HEIGHT - 8);
					break;
				}

				// Find the word type
				type = dic.getType(word);
				std::string stringType;
				stringType = typeToString(type);

				std::cout << "Entry:\n"
					<< "--------------\n"
					<< "Word: " << word << "\n"
					<< "Type: " << stringType << "\n"
					<< "Definition: " << wordDef << "\n\n";

				// End time here
				end = std::chrono::system_clock::now();
				std::chrono::duration<double> elapsed_seconds = end - start;
				end_time = std::chrono::system_clock::to_time_t(end);

				std::cout << std::setprecision(3) << std::fixed;
				std::cout << "Time: " << elapsed_seconds.count() << " seconds.";

				screenClear(SCREEN_HEIGHT - 15);

				break;
			}
			case 5: // display the number of entries (completed)
			{
				std::cout << "Number of entries: " << dic.getSize() << std::endl;
				screenClear(SCREEN_HEIGHT - 10);
				break;
			}
			case 6: // save to dictionary.txt
			{
				outfile.open("Dictionary.txt");
				outfile << dic.printDictionary();
				outfile.close();
				std::cout << "Save successful. \n\n";
				screenClear(SCREEN_HEIGHT - 11);

				break;
			}
			case 7:
			{
				screenClear(SCREEN_HEIGHT);
				done = true;
			}
			} // end switch
		} // end while

	std::cout << "Exited successfully. \n";
	std::system("pause");
	return 0;
}