// Copyright Jonathan Justin Rampersad 2021

#pragma once
#include "../GenericCode.h"

#include <iostream>

#ifndef PAIR_H_
#define PAIR_H_

namespace Enigma
{
	struct s_Pairs // Struct containing the two characters in a pair
	{
		char pair1{};
		char pair2{};

		s_Pairs() {} // Default Constructor
		s_Pairs(s_Pairs& obj); // Overloaded Copy Constructor
		s_Pairs & operator=(const s_Pairs& obj); // Overloaded Copy Assignment
		friend std::ostream& operator<<(std::ostream& os, const s_Pairs& pair); // Overloaded ostream operator for s_Pairs struct
	};

	class Pair
	{
		s_Pairs *m_Pairs = new s_Pairs[13]; // Pointer with memory allocated for 13 s_Pairs structs since there will be 13 pairs... 26 letters in the alphabet / 2 letters in a pair

		bool CheckDuplicates() const; // Function to check if a letter is repeated in the same pair or in another pair
		bool CheckInvalidChar(s_Pairs pair) const; // Function to check if a pair has any invalid characters
	public:
		Pair(); // Default constructor
		~Pair() { delete[] m_Pairs; } // Destrcutor that deallocates memory used to store member variable m_Pairs
		Pair(s_Pairs pairs[13]); // Constructor that takes an array of 13 s_Pairs

		void PairOut(char &letter) const; // This function does the encryption logic of the Pair module

#ifdef DEBUG_CODE_ACTIVE // Code in this statement is only compiled if DEBUG_CODE_ACTIVE Macro is defined (This can be done in any user CPP File)
		void DEBUG_PrintPairs() const; // This function Prints the pairs out to the screen
#endif

	};
}
#endif