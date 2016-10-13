// Dictionary.cpp
// Authors: Vince Cefalu & Matt Neis
//
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <locale>

#include "Dictionary.h"


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
		jisho[i]->definition = new definition;
		jisho[i]->definition->type = wordType::UNKNOWN;
		jisho[i]->definition->def = "n/a";
		jisho[i]->definition->next = NULL;
		jisho[i]->next = NULL;
	} // End for

	entries = 0;
} // End constructor


// ------------
// toLowercase
// ------------
// Changes a word to all lowercase letters
// Obviously ignores characters that have no lowercase,
// or characters that are not from the Roman Alphabet
// ---------------------------------------------------
// string word		The string
// 
// return string	Returns the string in all lowercase letters
std::string Dictionary::toLowercase(std::string word)
{
	std::locale loc;
	for (int i = 0; i < word.length(); i++)
	{
		word[i] = tolower(word[i], loc);
	}

	return word;
}


// -----
// hash
// -----
// Calculates the hash value used to calculate the index
// of the word
// ------------
// string word			The word
// wordType type		The type
uint Dictionary::hash(std::string word)
{
	uint hash = 0; // The hash value for the word
	uint index; // Where the word is stored in the array
	uint minVal = 97; // 97 is an 'a' in ASCII
	uint value; // Temporary storage of values used in hash calc

	// Make the word lowercase
	word = toLowercase(word);

	// Complex weight system based on gathered data
	for (int i = 0; i < word.length(); i++)
	{
		value = static_cast<uint>(word[i]);

		uint weightIndex = value - minVal;
		if (weightIndex >= 0 || weightIndex < 26)
		{
			value = value * weights[value - minVal];
		}

		hash += value;
	} // End for

	hash += word.length();

	// Calculate the index using modulo operation
	index = hash % TABLE_SIZE;

	return index;
} // End hash


/*
// ------------------------------------------------------------------
// After this comment, these are all the different attempts
// we had tried for a proper hash function.
// ------------------------------------------------------------------
int Dictionary::hash(string word, wordType type)
{
	// Make the word lowercase
	toLowercase(word);

	unsigned int hash = 0; // The hash value for the word
	int index; // Where the word is stored

	// Simple use of ASCII values to calculate hash
	for (int i = 0; i < word.length(); i++)
	{
		hash += static_cast<int>(word[i]);
	}

	cout << "Hash = " << hash << endl;

	// Calculate the index using modulo operation
	index = hash % TABLE_SIZE;

	return index;
}
*/


/*
// ------------------------------------------------------------------
int Dictionary::hash(string word, wordType type)
{
	// Make the word lowercase
	toLowercase(word);

	unsigned int hash = 0; // The hash value for the word
	int index; // Where the word is stored

	// Use of ASCII values taken to various powers of 2
	for (int i = 0; i < word.length(); i++)
	{
		hash += static_cast<int>(word[i]) * (pow(2, i));
	}

	cout << "Hash = " << hash << endl;

	// Calculate the index using modulo operation
	index = hash % TABLE_SIZE;

	return index;
}
*/


/*
// ------------------------------------------------------------------
int Dictionary::hash(string word, wordType type)
{
	// Make the word lowercase
	toLowercase(word);

	unsigned int hash = 0; // The hash value for the word
	int index; // Where the word is stored

	// A simple weighting system of ASCII values
	for (int i = 0; i < word.length(); i++)
	{
		int value = static_cast<int>(word[i]);

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
	}

	cout << "Hash = " << hash << endl;

	// Calculate the index using modulo operation
	index = hash % TABLE_SIZE;

	return index;
}
*/


/*
// ------------------------------------------------------------------
int Dictionary::hash(string word, wordType type)
{
	// Make the word lowercase
	toLowercase(word);

	unsigned int hash = 0; // The hash value for the word
	int index; // Where the word is stored in the array

	// More complex weight system using gathered data
	for (int i = 0; i < word.length(); i++)
	{
		int charVal = static_cast<int>(word[i]);

		if (charVal == 106 || charVal == 113 || charVal == 120 || charVal == 122
			|| charVal == 119 || charVal == 107) // group 0
		{
			hash += charVal * 1009;
		}
		else if (charVal == 118 || charVal == 102
			|| charVal == 121
			|| charVal == 98) // group 1
		{
			hash += charVal * 998;
		}
		else if (charVal == 104
			|| charVal == 109
			|| charVal == 112
			|| charVal == 103) // group 2
		{
			hash += charVal * 887;
		}
		else if (charVal == 117
			|| charVal == 100
			|| charVal == 99) // group 3
		{
			hash += charVal * 776;
		}
		else if (charVal == 108
			|| charVal == 111) // group 5
		{
			hash += charVal * 665;
		}
		else if (charVal == 116) // group 6
		{
			hash += charVal * 554;
		}
		else if (charVal == 114
			|| charVal == 110
			|| charVal == 97) // group 7
		{
			hash += charVal * 443;
		}
		else if (charVal == 105) // group 8
		{
			hash += charVal * 332;
		}
		else if (charVal == 115) // group 9
		{
			hash += charVal * 221;
		}
		else if (charVal == 101) // group 11
		{
			hash += charVal * 110;
		}
		else
		{
			// Basically do nothing with odd characters
			//cout << charVal << endl;
		}
	} // End for


	cout << "Hash = " << hash << endl;

	// Calculate the index using modulo operation
	index = hash % TABLE_SIZE;

	return index;
} // End hash
// ------------------------------------------------------------------
// End of hash functions
// ------------------------------------------------------------------
*/


// ---------
// addEntry
// ---------
// Adds an entry to the dictionary
// --------------------------------
// string word			The word
//
// return bool			Returns true if the word was successfully
//						added
bool Dictionary::addEntry(std::string word)
{
	uint index = hash(word);

	if (jisho[index]->word == "0")
	{
		jisho[index]->word = word;
		jisho[index]->definition->type = wordType::UNKNOWN;
		jisho[index]->definition->def = "n/a";
	} // End if
	else if (jisho[index]->word.compare(word) == 0) // If the words are exactly the same
	{
		// Entry add failed
		return false;
	}
	else
	{
		entry* ptr = jisho[index];

		// Move through the linked list until there is an empty spot
		while (ptr->next != NULL)
		{
			// Again, if the words are the same, fail the add operation
			if (ptr->word.compare(word) == 0)
			{
				return false;
			}
			ptr = ptr->next;
		} // End while

		  // Found a spot, so create the new entry
		entry* n = new entry;
		n->definition = new Dictionary::definition;

		n->word = word;
		n->definition->type = wordType::UNKNOWN;
		n->definition->def = "n/a";
		n->next = NULL;

		ptr->next = n;
	} // End else

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
bool Dictionary::addEntry(std::string word, wordType type, std::string definition)
{
	uint index = hash(word);

	if (jisho[index]->word == "0")
	{
		jisho[index]->word = word;
		jisho[index]->definition->type = type;
		jisho[index]->definition->def = definition;
	} // End if
	else if (jisho[index]->word.compare(word) == 0) // If the words are exactly the same
	{
		// Entry add failed
		return false;
	}
	else
	{
		entry* ptr = jisho[index];

		// Move through the linked list until there is an empty spot
		while (ptr->next != NULL)
		{
			// Again, if the words are the same, fail the add operation
			if (ptr->word.compare(word) == 0)
			{
				return false;
			}
			ptr = ptr->next;
		} // End while

		// Found a spot, so create the new entry
		entry* n = new entry;
		n->definition = new Dictionary::definition;

		n->word = word;
		n->definition->type = type;
		n->definition->def = definition;
		n->next = NULL;

		ptr->next = n;
	} // End else

	entries++;
	return true;
} // End addItem


// --------------
// addDefinition
// --------------
// Adds a definition to an existing entry
// ---------------------------------------
// string word		The word
// wordType type	The word's type
// string def		The word's definition
//
// return bool		Returns true if the add operation succeeded
bool Dictionary::addDefinition(std::string word, wordType type, std::string def)
{
	uint index = hash(word);

	// Attempt to find the specified word
	entry* ptr = jisho[index];
	bool notFound = true;
	bool first = true;
	while (notFound)
	{
		if (ptr->word.compare(word) == 0)
			notFound = false;
		else if (ptr->next != NULL)
			ptr = ptr->next;
		else
			break;
	}

	// If the word entry doesn't exist, fail the operation
	if (notFound)
		return false;

	// Find the last definition
	definition* defptr = ptr->definition;
	while (defptr->next != NULL)
	{
		defptr = defptr->next;
		first = false;
	}

	// Now add the new definition
	if (first)
	{
		defptr->type = type;
		defptr->def = def;
	}
	else
	{
		defptr->next = new Dictionary::definition;
		defptr = defptr->next;
		defptr->type = type;
		defptr->def = def;
	}

	return true;

} // End addDefinition


// -----------------
// changeDefinition
// -----------------
// Changes the selected definition of the selected word
// WARNING: Currently has zero catches for OOB indexes
// ----------------------------------------------------
// string word		The word
// string def		The new definition
// wordType type	The type associated with the definition
// int index		The index of the definition (0-inf)
//
// return bool		Returns true if it succeeds in changing the definition
bool Dictionary::changeDefinition(std::string word, wordType type, std::string def, int defIndex)
{
	uint index = hash(word);

	// Attempt to find the specified word
	entry* ptr = jisho[index];
	bool notFound = true;
	while (notFound)
	{
		if (ptr->word.compare(word) == 0)
			notFound = false;
		else if (ptr->next != NULL)
			ptr = ptr->next;
		else
			break;
	}

	// If the word entry doesn't exist, fail the operation
	if (notFound)
		return false;

	// Attempt to find the specified definition entry
	definition* defptr = ptr->definition;
	for (int i = 0; i < defIndex; i++)
	{
		if (defptr->next != NULL)
			defptr = defptr->next;
		else
			return false; // No definition at the specified index
	}

	// Found it, now change the definition
	defptr->def = def;
	defptr->type = type;

	return true;
} // End changeDefinition


// --------
// getType
// --------
// Gets the type of the specified word
// (Now that I think about it, this is pointless...
// -------------------------------------------------
// string word			The word
//
// return wordType		Returns the word's type as the wordType enum
wordType Dictionary::getType(std::string word)
{
	uint index = hash(word);

	// Find the specific word if there are multiple at
	// this index
	entry* ptr = jisho[index];
	while (ptr->next != NULL)
	{
		if (ptr->word.compare(word) == 0)
			return ptr->definition->type;
		else
			ptr = ptr->next;
	} // End while

	  // If the entry was the last in the linked list,
	  // then the loop skips it
	if (ptr->word.compare(word) == 0)
	{
		return ptr->definition->type;
	}

	// If we fail, then return the unkown type
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
std::string Dictionary::getDefinition(std::string word)
{
	uint index = hash(word);

	// Find the specific word if there are multiple at
	// this index
	entry* ptr = jisho[index];
	while (ptr->next != NULL)
	{
		if (ptr->word.compare(word) == 0)
		{
			return ptr->definition->def;
		}
		else
			ptr = ptr->next;
	} // End while

	// If the entry was the last in the linked list,
	// then the loop skips it
	if (ptr->word.compare(word) == 0)
	{
		return ptr->definition->def;
	}

	// If for some reason we fail, then return
	// a failure string
	return "FAILED";
} // End getDefinition


// --------
// getSize
// --------
// Gets the size of the dictionary ( how many entries it has)
// -----------------------------------------------------------
// return unsigned int		Returns an unsigned integer representing
//							the total amount of entries
uint Dictionary::getSize()
{
	return entries;
} // End getSize


// -----------
// printTable
// -----------
// Prints a string representation of the dictionary
// array for use in assessing distribution of data within Excel
// ------------------------------------------------
// return string		Returns a string representation
//						of the dictionary
std::string Dictionary::printTable()
{
	std::string out = "";
	uint rowCount;
	entry* entry;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		rowCount = 0;
		entry = jisho[i];

		if (jisho[i]->word != "0")
		{
			rowCount++;
			while (entry->next != NULL)
			{
				entry = entry->next;
				rowCount++;
			} // End while

			if (jisho[i]->word != "0")
			{
				rowCount++;
			}

		} // End else

		out += std::to_string(rowCount) + "\n";
	} // End for

	return out;
} // End printTable


// ----------------
// printDictionary
// ----------------
// Prints the dictionary to a file that is formatted
// so that it can be reused and rewritten to whenever
// the program is run
// -------------------
// return string		The dictionary as a string (can be huge so consider changing this later)
std::string Dictionary::printDictionary()
{
	entry* entry;
	std::string type;
	std::string def;
	std::string out = "";

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		entry = jisho[i];

		while (entry->word != "0")
		{
			switch (entry->definition->type)
			{
			case wordType::NOUN:
			{
				type = "n";
				break;
			}
			case wordType::VERB:
			{
				type = "v";
				break;
			}
			case wordType::ADJECTIVE:
			{
				type = "adj";
				break;
			}
			case wordType::ADVERB:
			{
				type = "adv";
				break;
			}
			case wordType::PRONOUN:
			{
				type = "pro";
				break;
			}
			case wordType::PREPOSITION:
			{
				type = "prep";
				break;
			}
			case wordType::CONJUNCTION:
			{
				type = "c";
				break;
			}
			case wordType::DETERMINER:
			{
				type = "d";
				break;
			}
			case wordType::EXCLAMATION:
			{
				type = "e";
				break;
			}
			case wordType::PREFIX:
			{
				type = "pref";
				break;
			}
			case wordType::SUFFIX:
			{
				type = "s";
				break;
			}
			default:
			{
				type = "UNKNOWN";
			}
			} // End switch

			def = entry->definition->def;
			out += entry->word + "  " + type + "  " + def + "\n";

			if (entry->next != NULL)
				entry = entry->next;
			else
				break;
		} // End while

	} // End for

	return out;
}