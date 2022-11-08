#include <Pair/Pair.h>
#include "../include/Core/GenericInclude.h"

#define CHECK m_Pairs[i].first == m_Pairs[j].first || m_Pairs[i].first == m_Pairs[j].second || m_Pairs[i].second == m_Pairs[j].first || m_Pairs[i].second == m_Pairs[j].second

namespace Enigma
{
#ifndef ENIGMA_USE_STD_PAIR
	std::ostream& operator<<(std::ostream& os, const s_Pairs& pair)
	{
		return std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl; // returns Pair in form (pair1, pair2) e.g (a, p)
	}
#endif // !1

	bool Pair::CheckDuplicates() const
	{
		// Checks the first 12 pairs against itself and all the pairs that come after it to see if a letter is duplicated
		for (Enigma_Short i = 0; i < 12; i++)
		{
			if (m_Pairs[i].first == m_Pairs[i].second)
				return true;

			for (Enigma_Short j = i + 1; j < 13; j++)
			{
				if (CHECK) // The logic for the check is located at line 3
					return true;
			}
		}
		return false;
	}

#ifdef ENIGMA_USE_STD_PAIR
	bool Pair::CheckInvalidChar(std::pair<char, char> pair) const
	{
		Enigma_Short* count = new Enigma_Short{ 0 };
		for (Enigma_Short i = 0; i < 26; i++)
		{
			// Checks the two pair characters to see if they are equal to any of the valid characters in alphabet array
			if (pair.first == alphabet[i])
				(*count)++;
			if (pair.second == alphabet[i])
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
#else
	bool Pair::CheckInvalidChar(s_Pairs pair) const
	{
		Enigma_Short* count = new Enigma_Short{ 0 };
		for (Enigma_Short i = 0; i < 26; i++)
		{
			// Checks the two pair characters to see if they are equal to any of the valid characters in alphabet array
			if (pair.first == alphabet[i])
				(*count)++;
			if (pair.second == alphabet[i])
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
#endif

	void Pair::SetPairs()
	{
		for (Enigma_Short i = 0, j = 25; i < 13; i++, j--) // For loop with two iterators i starts at alphabet[0] (a) and j starts at alphabet[25] (z)
		{
			m_Pairs[i].first = alphabet[i]; // Sets the 13 pair1 values to the first 13 letters in the alphabet
			m_Pairs[i].second = alphabet[j]; // Sets the 13 pair2 values to the last 13 letters in the alphabet
		}
	}

#ifdef ENIGMA_USE_STD_PAIR
	void Pair::SetPairs(std::array<std::pair<char, char>, 13> pairs)
	{
		for (Enigma_Short i = 0; i < 13; i++)
		{
			// Sets m_StdPairs member variable values to the values of pairs passed by the user when setting 
			m_StdPairs[i].first = pairs[i].first;
			m_StdPairs[i].second = pairs[i].second;

			if (CheckInvalidChar(m_StdPairs[i]))
				throw std::logic_error("ERROR 16-10: Invalid character entered in pair!"); // Throws a logic error to be caught when calling the function
		}

		if (CheckDuplicates())
			throw std::logic_error("ERROR 16-11: Duplicate letters in pairs!"); // Throws a logic error to be caught when calling the function
	}
#else
	void Pair::SetPairs(std::array<s_Pairs, 13> pairs)
	{
		for (Enigma_Short i = 0; i < 13; i++)
		{
			// Sets m_Pairs member variable values to the values of pairs passed by the user when setting 
			m_Pairs[i].first = pairs[i].first;
			m_Pairs[i].second = pairs[i].second;

			if (CheckInvalidChar(m_Pairs[i]))
				throw std::logic_error("ERROR 16-10: Invalid character entered in pair!"); // Throws a logic error to be caught when calling the function
		}

		if (CheckDuplicates())
			throw std::logic_error("ERROR 16-11: Duplicate letters in pairs!"); // Throws a logic error to be caught when calling the function
	}
#endif

	void Pair::PairOut(char& letter) const
	{
		for (Enigma_Short i = 0; i < 13; i++)
		{
			// Checks which pair the letter is located in and sets it to the other letter in the pair
			if (letter == m_Pairs[i].first)
			{
				letter = m_Pairs[i].second;
				return;
			}
			if (letter == m_Pairs[i].second)
			{
				letter = m_Pairs[i].first;
				return;
			}
		}
	}
}