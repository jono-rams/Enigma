#include "Rotor.h"

namespace Enigma
{
	void Rotor::Rotate()
	{
		char temp = m_Rotator[0];

		for (int i = 0; i < 25; i++)
			m_Rotator[i] = m_Rotator[i + 1];

		m_Rotator[25] = temp;
	}

	Rotor::Rotor(bool FirstRotor, ushort_t seed)
		: m_FirstRotor(FirstRotor), m_SeedNo(seed), m_Seed(new std::mt19937(seed * 23))
	{
		for (ushort_t i = 0; i < 26; i++)
		{
			m_Rotator[i] = alphabet[25 - i]; // To make in constant random order (at first)
		}
	}

	void Rotor::In(char& c)
	{
		ushort_t temp{};
		for (ushort_t i = 0; i < 26; i++)
		{
			if (c == alphabet[i])
			{
				temp = i;
				break;
			}
		}

		c = m_Rotator[temp];
	}

	void Rotor::Out(char& c)
	{
		for (ushort_t i = 0; i < 26; i++)
		{
			if (c == m_Rotator[i])
			{
				c = alphabet[i];
				break;
			}
		}

		if (!m_FirstRotor)
			m_Count++;
		else
			Rotate();

		if (m_Count >= 26)
			Rotate();
	}
}