// Dictionary.h
// Authors: Vince Cefalu & Matt Neis
//
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <locale>	// Used in lowercase function

#ifndef DICTIONARYARRAYUNSORTED_H
#define DICTIONARYARRAYUNSORTED_H
#define ENUM

// The types that words can have along with an UNKNOWN identifier when
// attempting to find the type and you are unsuccessful
enum class wordType {
	NOUN = 1, VERB, ADJECTIVE, ADVERB, PRONOUN, PREPOSITION,
	CONJUNCTION, DETERMINER, EXCLAMATION, PREFIX, SUFFIX, ABBREVIATION, UNKNOWN
};
class DictionaryArrayUnsorted
{

private:
	static const int TABLE_SIZE = 200000; // The size of the array. Affects hash calculation when changed
	unsigned int entries; // Counter for the total amount of entries added

						  // Structure that represents individual definitions
	struct definition
	{
		wordType type;			// The type of the word for this definition
		std::string def;		// The definition of the word
		definition* next;		// The pointer to the next definition if it exists
	};

	// The item structure that represents a dictionary entry
	struct entry
	{
		std::string word;			// The word stored in English (for the moment)
		definition* definition;		// The definitions of the word
	};

	entry* jisho[TABLE_SIZE];	// Array of pointers to entry (the dictionary array itself)

	std::string toLowercase(std::string word);

public:
	DictionaryArrayUnsorted();
	bool addEntry(std::string word);
	bool addEntry(std::string word, wordType type, std::string definition);
	int findWord(std::string word);
	wordType getType(std::string word);
	std::string getDefinition(std::string word);
	unsigned int getSize();
};

#endif