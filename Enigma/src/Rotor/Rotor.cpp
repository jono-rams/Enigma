#include "Rotor.h"

#include <vector>
#include <fstream>

namespace Enigma
{
	void Rotor::Rotate()
	{
		char temp = m_Rotator[0];

		for (int i = 0; i < 25; i++)
			m_Rotator[i] = m_Rotator[i + 1];

		m_Rotator[25] = temp;
	}

	Rotor::Rotor(uchar_t rotModuleNum, ushort_t seed)
		: m_RotNum(new uchar_t), m_SeedNo(new ushort_t)
	{
		*m_SeedNo = seed;
		*m_RotNum = rotModuleNum;
		
		std::vector<ushort_t> temp;
		ushort_t *x = new ushort_t{};
		std::ifstream *in;

		if (seed == 1)
		{
			in->open("RotorModules/Module1.rot", std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 2)
		{
			in->open("RotorModules/Module2.rot", std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 3)
		{
			in->open("RotorModules/Module3.rot", std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 4)
		{
			in->open("RotorModules/Module4.rot", std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}
		else
		{
			in->open("RotorModules/Module5.rot", std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back((*x);
			}
		}

		in->close();
		delete in;
		delete x;

		for (ushort_t i = 0; i < 26; i++)
			m_Rotator[i] = alphabet[temp[i]];

		temp.clear();
		temp.shrink_to_fit();
	}

	void Rotor::In(char& c) const
	{
		ushort_t *temp = new ushort_t{};
		for (ushort_t i = 0; i < 26; i++)
		{
			if (c == alphabet[i])
			{
				*temp = i;
				break;
			}
		}

		c = m_Rotator[*temp];
		delete temp;
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

		if (*m_RotNum != 1)
			(*m_Count)++;
		else
			Rotate();

		if (*m_Count >= 26 && *m_RotNum != 3)
			Rotate();
		else if (*m_Count >= 52)
			Rotate();
	}

	Rotor::~Rotor()
	{
		delete[] m_Rotator;
		delete m_Count;
		delete m_RotNum;
		delete m_SeedNo;
	}
}