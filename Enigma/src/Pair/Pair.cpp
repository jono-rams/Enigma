#include "Pair.h"
#include "../Log/Log.h"

#define CHECK m_Pairs[i].pair1 == m_Pairs[j].pair1 || m_Pairs[i].pair1 == m_Pairs[j].pair2 || m_Pairs[i].pair2 == m_Pairs[j].pair1 || m_Pairs[i].pair2 == m_Pairs[j].pair2

namespace Enigma
{
	s_Pairs::s_Pairs(s_Pairs& obj) noexcept
	{
		pair1 = obj.pair1;
		pair2 = obj.pair2;
	}

	s_Pairs& s_Pairs::operator=(const s_Pairs& obj) noexcept
	{
		if (this == &obj) // Checks to see if s_Pairs are the same object
		{
			return *this;
		}

		pair1 = obj.pair1;
		pair2 = obj.pair2;
		return *this;
	}

	s_Pairs::s_Pairs(s_Pairs&& obj) noexcept
	{
		pair1 = obj.pair1;
		pair2 = obj.pair2;
	}

	s_Pairs& s_Pairs::operator=(const s_Pairs&& obj) noexcept
	{
		if (this == &obj) // Checks to see if s_Pairs are the same object
		{
			return *this;
		}
		
		pair1 = obj.pair1;
		pair2 = obj.pair2;
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const s_Pairs& pair)
	{
		return std::cout << "(" << pair.pair1 << ", " << pair.pair2 << ")" << std::endl; // returns Pair in form (pair1, pair2) e.g (a, p)
	}

	Pair::Pair()
	{
		Log::WriteLog("Attempting to create Pair class with default Constructor");
		for (ushort_t i = 0, j = 25; i < 13; i++, j--) // For loop with two iterators i starts at alphabet[0] (a) and j starts at alphabet[25] (z)
		{
			m_Pairs[i].pair1 = alphabet[i]; // Sets the 13 pair1 values to the first 13 letters in the alphabet
			m_Pairs[i].pair2 = alphabet[j]; // Sets the 13 pair2 values to the last 13 letters in the alphabet
		}
		Log::WriteLog("Created Pair class with default Constructor");
	}

	Pair::Pair(s_Pairs pairs[13])
	{
		Log::WriteLog("Attempting to create Pair class with custom values Constructor");
		for (ushort_t i = 0; i < 13; i++)
		{
			// Sets m_Pairs member variable values to the values of pairs passed by the user when setting 
			m_Pairs[i] = pairs[i];
			m_Pairs[i] = pairs[i];

			if (CheckInvalidChar(m_Pairs[i])) // Checks if the characters set in m_Pairs are valid
			{
				delete[] m_Pairs; // Deallocates memory used to store member variable m_Pairs
				Log::WriteLog("ERROR: Pair.cpp - Invalid character entered in Pair");
				throw std::logic_error("Invalid character entered in Pair!"); // Throws a logic error to be caught when calling the function
			}
		}

		if (CheckDuplicates()) // Checks for duplicate letters in entered pairs
		{
			delete[] m_Pairs; // Deallocates memory used to store member variable m_Pairs
			Log::WriteLog("ERROR: Pair.cpp - Duplicate letters in pairs");
			throw std::logic_error("Duplicate letters in pairs!"); // Throws a logic error to be caught when calling the function
		}
		Log::WriteLog("Created Pair class with custom values Constructor");
	}

	void Pair::PairOut(char &letter) const
	{
		for (ushort_t i = 0; i < 13; i++)
		{
			// Checks which pair the letter is located in and sets it to the other letter in the pair
			if (letter == m_Pairs[i].pair1)
			{
				letter = m_Pairs[i].pair2;
				return;
			}			
			if (letter == m_Pairs[i].pair2)
			{
				letter = m_Pairs[i].pair1;
				return;
			}
		}
	}

	bool Pair::CheckDuplicates() const
	{
		// Checks the first 12 pairs against itself and all the pairs that come after it to see if a letter is duplicated
		for (ushort_t i = 0; i < 12; i++)
		{
			if (m_Pairs[i].pair1 == m_Pairs[i].pair2)
				return true;

			for (ushort_t j = i + 1; j < 13; j++)
			{
				if (CHECK) // The logic for the check is located at line 3
					return true;
			}
		}
		return false;
	}

	bool Pair::CheckInvalidChar(s_Pairs pair) const
	{
		ushort_t *count = new ushort_t{ 0 };
		for (ushort_t i = 0; i < 26; i++)
		{
			// Checks the two pair characters to see if they are equal to any of the valid characters in alphabet array
			if (pair.pair1 == alphabet[i])
				(*count)++;
			if (pair.pair2 == alphabet[i])
				(*count)++;

			if (*count > 1) // If count is > 1 that means that both characters in the pair were found in the alphabet
			{
				delete count;
				return false;
			}
		}
		delete count;
		return true;
	}
}
