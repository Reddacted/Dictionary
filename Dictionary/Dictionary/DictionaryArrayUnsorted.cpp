// Dictionary.cpp
// Authors: Vince Cefalu & Matt Neis
//
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <locale>

#include "DictionaryArrayUnsorted.h"


// -----------
// Dictionary
// -----------
// Constructor for the Dictionary object
DictionaryArrayUnsorted::DictionaryArrayUnsorted()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		// Initialization
		jisho[i] = new entry;
		jisho[i]->word = "0";
		jisho[i]->definition = new definition;
		jisho[i]->definition->type = wordType::UNKNOWN;
		jisho[i]->definition->def = "n/a";
		jisho[i]->definition->next = NULL;
	} // End for

	entries = 0;
} // End constructor


  //
  //
  //
std::string DictionaryArrayUnsorted::toLowercase(std::string word)
{
	std::locale loc;
	for (int i = 0; i < word.length(); i++)
	{
		word[i] = tolower(word[i], loc);
	}

	return word;
}


  // ---------
  // addEntry
  // ---------
  // Adds an entry to the dictionary
  // --------------------------------
  // string word			The word
  //
  // return bool			Returns true if the word was successfully
  //						added
bool DictionaryArrayUnsorted::addEntry(std::string word)
{
	word = toLowercase(word);

	jisho[entries]->word = word;
	entries++;

	return true;
} // End addItem


  // ---------
  // addEntry
  // ---------
  // Adds an entry to the dictionary
  // --------------------------------
  // string word			The word
  // wordType type		The type of word
  // string definition	The definition of the word
  //
  // return bool			Returns true if the word was successfully
  //						added
bool DictionaryArrayUnsorted::addEntry(std::string word, wordType type, std::string definition)
{
	word = toLowercase(word);

	jisho[entries]->word = word;
	jisho[entries]->definition->type = type;
	jisho[entries]->definition->def = definition;

	entries++;
	return true;
} // End addItem


int DictionaryArrayUnsorted::findWord(std::string word)
{
	for (int i = 0; i < entries; i++)
	{
		if (jisho[i]->word.compare(word) == 0)
			return i;
	}

	return -1;
}


  // --------
  // getType
  // --------
  // Gets the type of the specified word
  // (Now that I think about it, this is pointless...
  // -------------------------------------------------
  // string word			The word
  //
  // return wordType		Returns the word's type as the wordType enum
wordType DictionaryArrayUnsorted::getType(std::string word)
{
	word = toLowercase(word);
	int index = findWord(word);

	if (index > -1)
		return jisho[index]->definition->type;

	return wordType::UNKNOWN;
} // End getType


  // --------------
  // getDefinition
  // --------------
  // Finds a specific word's definition
  // -----------------------------------
  // string word				The word
  //
  // return definition		Returns the definition struct
std::string DictionaryArrayUnsorted::getDefinition(std::string word)
{
	word = toLowercase(word);
	int index = findWord(word);

	if (index > -1)
		return jisho[index]->definition->def;

	return "FAILED";
} // End getDefinition


  // --------
  // getSize
  // --------
  // Gets the size of the dictionary ( how many entries it has)
  // -----------------------------------------------------------
  // return unsigned int		Returns an unsigned integer representing
  //							the total amount of entries
unsigned int DictionaryArrayUnsorted::getSize()
{
	return entries;
} // End getSize