#include "Pair.h"
#include "../Alphabet.h"

namespace Enigma
{
	Pair::Pair()
	{
		for (int i = 0; i < 26; i++)
			m_Connections[i] = i;

		for (int i = 0, j = 25; i < 13; i++, j--)
		{
			m_Pairs.pair1[i] = alphabet[i];
			m_Pairs.pair2[i] = alphabet[j];
		}
	}

	Pair::Pair(s_Pairs pairs)
		: m_Pairs(pairs)
	{
		for (int i = 0; i < 26; i++)
			m_Connections[i] = i;
	}

	void Pair::SetPairs(s_Pairs pairs)
	{
		m_Pairs = pairs;
	}
}