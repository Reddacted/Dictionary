//
//
//
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <locale>

using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

	// The types that words can have along with a FAIL identifier when
	// attempting to find the type and you are unsuccessful
	enum class wordType {
		NOUN = 1, VERB, ADJECTIVE, ADVERB, PRONOUN, PREPOSITION,
		CONJUNCTION, DETERMINER, EXCLAMATION, PREFIX, SUFFIX, UNKNOWN };
class Dictionary
{

private:
	static const int TABLE_SIZE = 1000; // The size of the array. Affects hash calculation when changed
	unsigned int entries; // Counter for the total amount of entries added

	// Structure that represents individual definitions
	struct definition
	{
		wordType type;			// The type of the word for this definition
		string def;				// The definition of the word
		definition* next;		// The pointer to the next definition if it exists
	};

	// The item structure that represents a dictionary entry
	struct entry
	{
		string word;				// The word stored in English (for the moment)
		definition* definition;		// The definitions of the word
		entry* next;				// Linked list pointer, connects list items to one another)
	};

	entry* jisho[TABLE_SIZE];	// Array of pointers to entry (the dictionary array itself)

	// The weight values for all letters for use in hash calculations
	unsigned int weights[26] = { 81523, 18479, 43560, 32256, 108336, 11558, 23915, 25792, 88799,
								1512, 7638, 55945, 29805, 72211, 72089, 32512, 1698, 70945, 73182,
								66797, 37748, 9680, 6577, 3015, 20259, 4154};

public:
	Dictionary();
	int hash(string word);
	bool addEntry(string word);
	bool addEntry(string word, wordType type, string definition);
	bool addDefinition(string word, string def, wordType type);
	bool changeDefinition(string word, string def, wordType type, int defIndex);
	wordType getType(string word);
	string getDefinition(string word);
	unsigned int getSize();
	string printTable();
	string printDictionary();
};

#endif