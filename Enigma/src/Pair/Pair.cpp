#include "Pair.h"

#define CHECK pairs[i].pair1 == pairs[j].pair1 || pairs[i].pair1 == pairs[j].pair2 || pairs[i].pair2 == pairs[j].pair1 || pairs[i].pair2 == pairs[j].pair2

namespace Enigma
{
	std::ostream& operator<<(std::ostream& os, const s_Pairs& pair)
	{
		return std::cout << "(" << pair.pair1 << ", " << pair.pair2 << ")" << std::endl;
	}

	Pair::Pair()
	{
		for (ushort_t i = 0; i < 26; i++)
			m_Connections[i] = i;

		for (ushort_t i = 0, j = 25; i < 13; i++, j--)
		{
			m_Pairs[i].pair1 = alphabet[i];
			m_Pairs[i].pair2 = alphabet[j];
		}
	}

	Pair::Pair(s_Pairs pairs[13])
	{
		for (ushort_t i = 0; i < 26; i++)
			m_Connections[i] = i;
		
		for (ushort_t i = 0; i < 13; i++)
		{
			m_Pairs[i].pair1 = pairs[i].pair1;
			m_Pairs[i].pair2 = pairs[i].pair2;
		}

		if (CheckDuplicates(pairs))
			throw std::logic_error("Duplicate letters in pairs!");
	}

	char Pair::PairOut(char letter)
	{
		for (ushort_t i = 0; i < 13; i++)
		{
			if (letter == m_Pairs[i].pair1)
			{
				return m_Pairs[i].pair2;
			}
			
			if (letter == m_Pairs[i].pair2)
			{
				return m_Pairs[i].pair1;
			}
		}
	}

	bool Pair::CheckDuplicates(s_Pairs pairs[13]) const
	{
		for (ushort_t i = 0; i < 12; i++)
		{
			if (pairs[i].pair1 == pairs[i].pair2)
				return true;

			for (ushort_t j = i + 1; j < 13; j++)
			{
				if (CHECK)
					return true;
			}
		}
		return false;
	}

#if DEBUG_CODE_ACTIVE
	void Pair::DEBUG_PrintPairs() const
	{
		for (ushort_t i = 0; i < 13; i++)
			std::cout << m_Pairs[i];
	}
#endif
}
