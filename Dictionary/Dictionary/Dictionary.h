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

	enum class wordType {
		NOUN = 1, VERB, ADJECTIVE, ADVERB, PRONOUN,
		PREPOSITION, CONJUNCTION, DETERMINER, EXCLAMATION };
class Dictionary
{

private:
	static const int TABLE_SIZE = 20000; // The size of the array. Affects hash calculation when changed

									   // The item structure that represents a dictionary entry
	struct entry
	{
		string word;		// The word stored in English (for the moment)
		wordType wordType;	// The type of word (i.e. noun, adjective, etc.)
		string definition;	// The definition(s) of the word (might change to a pointer)
		entry* next;		// Linked list pointer, connects list items to one another)
	};

	entry* jisho[TABLE_SIZE];	// Array of pointers to entry (the dictionary array itself)

public:
	Dictionary();
	int hash(string word, wordType type);
	bool addItem(string word, wordType type, string definition);
	string printTable();
};

#endif