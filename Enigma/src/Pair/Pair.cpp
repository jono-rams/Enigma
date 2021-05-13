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
		for (ushort_t i = 0, j = 25; i < 13; i++, j--)
		{
			m_Pairs[i].pair1 = alphabet[i];
			m_Pairs[i].pair2 = alphabet[j];
		}
	}

	Pair::Pair(s_Pairs pairs[13])
	{
	
		for (ushort_t i = 0; i < 13; i++)
		{
			m_Pairs[i].pair1 = pairs[i].pair1;
			m_Pairs[i].pair2 = pairs[i].pair2;

			if (CheckInvalidChar(m_Pairs[i]))
			{
				delete[] m_Pairs;
				throw std::logic_error("Invalid character entered in Pair!");
			}
		}

		if (CheckDuplicates(pairs))
		{
			delete[] m_Pairs;
			throw std::logic_error("Duplicate letters in pairs!");
		}
	}

	void Pair::PairOut(char &letter) const
	{
		for (ushort_t i = 0; i < 13; i++)
		{
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

	bool Pair::CheckInvalidChar(s_Pairs pair) const
	{
		ushort_t *count = new ushort_t{ 0 };
		for (ushort_t i = 0; i < 26; i++)
		{
			if (pair.pair1 == alphabet[i])
				(*count)++;
			if (pair.pair2 == alphabet[i])
				(*count)++;

			if (*count > 1)
			{
				delete count;
				return false;
			}
		}
		delete count;
		return true;
	}

#if DEBUG_CODE_ACTIVE
	void Pair::DEBUG_PrintPairs() const
	{
		for (ushort_t i = 0; i < 13; i++)
			std::cout << m_Pairs[i];
	}
#endif
}
