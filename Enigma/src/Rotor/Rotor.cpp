#include "Rotor.h"

#include <vector>
#include <fstream>
#include <string>

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
		: m_FirstRotor(FirstRotor), m_SeedNo(seed)
	{
		std::vector<ushort_t> temp;
		ushort_t x{};
		bool y{ false };

		if (seed == 1)
		{
			std::ifstream in("data1.txt", std::ios::in);
			while (in >> x)
			{
				temp.push_back(x);
			}
		}
		else if (seed == 2)
		{
			std::ifstream in("data2.txt", std::ios::in);
			while (in >> x)
			{
				temp.push_back(x);
			}
		}
		else if (seed == 3)
		{
			std::ifstream in("data3.txt", std::ios::in);
			while (in >> x)
			{
				temp.push_back(x);
			}
		}
		else if (seed == 4)
		{
			std::ifstream in("data4.txt", std::ios::in);
			while (in >> x)
			{
				temp.push_back(x);
			}
		}
		else
		{
			std::ifstream in("data5.txt", std::ios::in);
			while (in >> x)
			{
				temp.push_back(x);
			}
		}

		for (ushort_t i = 0; i < 26; i++)
			m_Rotator[i] = alphabet[temp[i]];
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
	
#if DEBUG_CODE_ACTIVE
	void Rotor::DEBUG_CacheSeedVals()
	{
		std::vector<ushort_t> temp;
		std::string fileN = "data1.txt";
		std::ofstream file(fileN, std::ios::out);
		ushort_t x{};
		bool y{ false };

		while (1)
		{
			x = (*m_Seed)() % 26;
			for (ushort_t j = 0; j < temp.size(); j++)
			{
				if (x == temp[j])
				{
					y = true;
					break;
				}
			}
			if (y)
				continue;
			temp.push_back(x);
			file << x << std::endl;
			if (temp.size() > 26)
				break;
		}
		file.close();
	}
#endif
}