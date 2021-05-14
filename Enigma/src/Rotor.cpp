#include "../../include/Rotor/Rotor.h"

#include <vector>
#include <fstream>

namespace Enigma
{
	void Rotor::Rotate()
	{
		char* temp = new char(m_Rotator[0]); // Sets a temporary char to the first value in array

		// Sets the the first value in array to the second value and so on (except the last value)
		for (int i = 0; i < 25; i++)
			m_Rotator[i] = m_Rotator[i + 1];

		// Sets the last value in array to the first value which was stored in the temp variable
		m_Rotator[25] = *temp;
		delete temp; // Deallocates memory for temp variable
	}

	Rotor::Rotor(uchar_t rotModuleNum, ushort_t seed, std::string ROTOR_FILE_PATH)
		: m_RotNum(new uchar_t), m_SeedNo(new ushort_t) // Allocates memory for m_RotNum and m_SeedNo
	{
		*m_SeedNo = seed; // Sets seed value
		*m_RotNum = rotModuleNum; // Sets rotor slot value

		if (*m_RotNum == 1) // Checks if the rotor is in the first slot
		{
			delete m_Count; // Deallocates memory for m_Count as it is not needed for rotor in first slot
			m_Count = nullptr; // Points m_Count to nullptr to avoid errors when destructor tries to deallocate its memory again
		}
		
		std::vector<ushort_t> temp; // Vector to hold all values from .rot data files, these files contain how the rotor connects from one letter to the next
		ushort_t *x = new ushort_t{}; // Temporary variable to hold data from .rot data files before adding it to vector
		std::ifstream *in = new std::ifstream; // Temporary ifstream object to open and read from .rot data files

		// Reads from specific .rot data file depending on seed and adds all values to temp vector
		if (seed == 1)
		{
			ROTOR_FILE_PATH += "/Module1.rot";
			in->open(ROTOR_FILE_PATH.c_str(), std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 2)
		{
			ROTOR_FILE_PATH += "/Module2.rot";
			in->open(ROTOR_FILE_PATH.c_str(), std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 3)
		{
			ROTOR_FILE_PATH += "/Module3.rot";
			in->open(ROTOR_FILE_PATH.c_str(), std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 4)
		{
			ROTOR_FILE_PATH += "/Module4.rot";
			in->open(ROTOR_FILE_PATH.c_str(), std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}
		else
		{
			ROTOR_FILE_PATH += "/Module5.rot";
			in->open(ROTOR_FILE_PATH.c_str(), std::ios::in);
			while ((*in) >> *x)
			{
				temp.push_back(*x);
			}
		}

		in->close(); // Closes file
		delete in; // Deallocates memory for ifstream object
		delete x; // Deallocates memory for x

		// Sets the m_Rotator values to those from .rot files via the vector
		for (ushort_t i = 0; i < 26; i++)
			m_Rotator[i] = alphabet[temp[i]];

		temp.clear(); // Deletes all values from vector
		temp.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory
	}

	void Rotor::In(char& c) const
	{
		ushort_t *temp = new ushort_t{}; // Allocates memory for a temp unsigned short
		
		// Checks to see which letter was passed and sets temp to the location in alphabet
		for (ushort_t i = 0; i < 26; i++)
		{
			if (c == alphabet[i])
			{
				*temp = i;
				break;
			}
		}

		c = m_Rotator[*temp]; // Sets character to new letter determined by m_Rotator
		delete temp; // Deallocates memory for temp
	}

	void Rotor::Out(char& c)
	{
		// Does reverse logic of In function
		for (ushort_t i = 0; i < 26; i++)
		{
			if (c == m_Rotator[i])
			{
				c = alphabet[i];
				break;
			}
		}

		// Logic to determine when to rotate
		if (*m_RotNum != 1)
			(*m_Count)++;
		else
		{
			Rotate();
			return;
		}

		if (*m_Count >= 26 && *m_RotNum == 2)
			Rotate();
		else if (*m_Count >= 52)
			Rotate();
	}

	Rotor::~Rotor()
	{
		// Deallocates memory for all member variables
		delete[] m_Rotator;
		delete m_Count;
		delete m_RotNum;
		delete m_SeedNo;
	}
}