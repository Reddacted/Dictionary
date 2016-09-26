// Driver for hash table

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#include "Dictionary.h"

using namespace std;

int main()
{
	Dictionary dic;
	int index;

	// Input words from a txt file list (one word per line)
	// Also assume (for now) that all words are nouns and
	// there is a generic definition for each

	ifstream inFile;
	string word;
	inFile.open("2of12.txt");
	while (!inFile.eof()) // To get you all the lines
	{
		getline(inFile, word); // Saves the line in word
		dic.addItem(word, wordType::NOUN, "A DEFINITION");

	} // End while

	inFile.close();

	dic.printTable();

	system("pause");

	return 0;
}