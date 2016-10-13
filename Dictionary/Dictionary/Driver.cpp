// Driver for hash table that now
// generates text files for Excel analysis
// by using all the different versions of
// the hash function we've created

#include <iostream>
#include <string>
#include <fstream> 
#include <iomanip>

#define ENUM
#include "Dictionary.h"


wordType stringToType(const std::string typeAsString)
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
	else
	{
		type = wordType::UNKNOWN;
	}

	return type;
}


int main()
{
	// variables and objects
	//	DictionaryArrayUnsorted dic;
	Dictionary dic;
	wordType type = wordType::UNKNOWN;
	std::ifstream infile;
	std::ofstream outfile;
	std::string delimiter = "  ";

	std::string line = "";
	std::string inWord[3];
	std::string word = "";

	// load base dictionary
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

	std::cout << dic.getSize();

	// Now that we have the words, output to a file

	outfile.open("To Excel.txt");

	outfile << dic.printTable();

	std::cout << "Fin" << std::endl;
	system("pause");

	return 0;
}