//
//
//
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <locale>

#include "Dictionary.h"


using namespace std;


// -----------
// Dictionary
// -----------
// Constructor for the Dictionary object
Dictionary::Dictionary()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		// Initialization
		jisho[i] = new entry;
		jisho[i]->word = "0";
		jisho[i]->wordType = wordType::NOUN;
		jisho[i]->definition = "0";
		jisho[i]->next = NULL;
	} // End for
} // End constructor


// -----
// hash
// -----
// Calculates the hash value used to calculate the index
// of the word
// ------------
// string word			The word
// wordType type		The type

int Dictionary::hash(string word, wordType type)
{
	unsigned int hash = 0; // The hash value for the word
	int index; // Where the word is stored

			   // Various methods for calculating the hash value
	for (int i = 0; i < word.length(); i++)
	{
		int value = static_cast<int>(word[i]);
//		hash += static_cast<int>(word[i]);
//		hash += static_cast<int>(word[i]) * (pow(2, i));
//		hash += pow(static_cast<int>(word[i]), 5);

		// Value range = [97-122]
		if (value <= 102)
			hash += value * 1;
		else if (value <= 107)
			hash += value * 2;
		else if (value <= 112)
			hash += value * 3;
		else if (value <= 117)
			hash += value * 4;
		else
			hash += value * 5;
	} // End for

//	cout << "Hash = " << hash << endl;

	// Calculate the index using modulo operation
	index = hash % TABLE_SIZE;

	return index;
} // End hash


// --------
// addItem
// --------
// Adds an entry to the dictionary
// --------------------------------
// string word			The word
// wordType type		The type of word
// string definition	The definition of the word
//
// return bool			Returns true if the word was successfully
//						added
bool Dictionary::addItem(string word, wordType type, string definition)
{
	// Make the word lowercase
	locale loc;
	for (int i = 0; i < word.length(); i++)
	{
		word[i] = tolower(word[i], loc);
	}

	int index = hash(word, type);

	if (jisho[index]->word == "0")
	{
		jisho[index]->word = word;
		jisho[index]->wordType = type;
		jisho[index]->definition = definition;
	} // End if
	else
	{
		entry* ptr = jisho[index];
		entry* n = new entry;

		n->word = word;
		n->wordType = type;
		n->definition = definition;
		n->next = NULL;

		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		} // End while

		ptr->next = n;
	} // End else

	return true;
} // End addItem


// -----------
// printTable
// -----------
// Prints a string representation of the dictionary
// array for use in assessing distribution of data
// ------------------------------------------------
// return string		Returns a string representation
//						of the dictionary
string Dictionary::printTable()
{
	string out = "";
	entry* entry;

	// creates txt file for saving the output of the table
	ofstream file;
	file.open("Attempt 05.txt");


	for (int i = 0; i < TABLE_SIZE; i++)
	{
		entry = jisho[i];
		out += "[";

		if (jisho[i]->word == "0")
		{
			out += " ";
		} // End if
		else
		{
			out += "X";
		} // End else

		out += "]";

		while (entry->next != NULL)
		{
			entry = entry->next;
			out += "->[X]";
		} // End while

		out += "\n";
	} // End for

	file << out;
	file.close();

	return out;
} // End printTable