#include "Pair.h"
#include "../Alphabet.h"

namespace Enigma
{
	std::ostream& operator<<(std::ostream& os, const s_Pairs& pair)
	{
		return std::cout << "(" << pair.pair1 << ", " << pair.pair2 << ")" << std::endl;
	}

	Pair::Pair()
	{
		for (int i = 0; i < 26; i++)
			m_Connections[i] = i;

		for (int i = 0, j = 25; i < 13; i++, j--)
		{
			m_Pairs[i].pair1 = alphabet[i];
			m_Pairs[i].pair2 = alphabet[j];
		}
	}

	Pair::Pair(s_Pairs pairs[13])
	{
		for (int i = 0; i < 26; i++)
			m_Connections[i] = i;
		
		for (int i = 0; i < 13; i++)
		{
			m_Pairs[i].pair1 = pairs[i].pair1;
			m_Pairs[i].pair2 = pairs[i].pair2;
		}

		if (CheckDuplicates())
			throw std::logic_error("Duplicate letters in pairs!");
	}

	bool Pair::CheckDuplicates() const
	{
		return false;
	}

	void Pair::DEBUG_PrintPairs() const
	{
		for (int i = 0; i < 13; i++)
			std::cout << m_Pairs[i];
	}
}
