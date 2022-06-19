#include <Rotor/Rotor.h>

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

	Rotor::Rotor() :
		m_Count(nullptr), m_RotNum(0), m_SeedNum(0)
	{
		for (Enigma_Short i = 0; i < 26; i++)
		{
			m_Rotator[i] = '0';
		}
	}

	void Rotor::SetRotor(Enigma_Char rotModuleNum, Enigma_Short seed, std::string ROTOR_FILE_PATH)
	{
		m_RotNum = rotModuleNum;
		m_Count = new Enigma_Short{0}; // Allocates memory for m_Count variable
		m_SeedNum = seed;

		if (m_RotNum == 1) // Checks if the rotor is in the first slot
		{
			delete m_Count; // Deallocates memory for m_Count as it is not needed for rotor in first slot
			m_Count = nullptr; // Points m_Count to nullptr to avoid errors when destructor tries to deallocate its memory again
		}

		std::vector<Enigma_Short> temp; // Vector to hold all values from .rot data files, these files contain how the rotor connects from one letter to the next
		Enigma_Short* x = new Enigma_Short{}; // Temporary variable to hold data from .rot data files before adding it to vector
		std::ifstream in; // ifstream object to open and read from .rot data files

		// Reads from specific .rot data file depending on seed and adds all values to temp vector
		if (seed == 1)
		{
			ROTOR_FILE_PATH += "/Module1.rot";
			in.open(ROTOR_FILE_PATH.c_str(), std::ios::in);

			if (!in.is_open())
			{
				delete x;
				throw std::logic_error("ERROR 18-10: Rotor File could not be opened!"); // Throws a logic error to be caught when calling the function
			}

			while (in >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 2)
		{
			ROTOR_FILE_PATH += "/Module2.rot";
			in.open(ROTOR_FILE_PATH.c_str(), std::ios::in);

			if (!in.is_open())
			{
				delete x;
				throw std::logic_error("ERROR 18-10: Rotor File could not be opened!"); // Throws a logic error to be caught when calling the function
			}

			while (in >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 3)
		{
			ROTOR_FILE_PATH += "/Module3.rot";
			in.open(ROTOR_FILE_PATH.c_str(), std::ios::in);

			if (!in.is_open())
			{
				delete x;
				throw std::logic_error("ERROR 18-10: Rotor File could not be opened!"); // Throws a logic error to be caught when calling the function
			}

			while (in >> *x)
			{
				temp.push_back(*x);
			}
		}
		else if (seed == 4)
		{
			ROTOR_FILE_PATH += "/Module4.rot";
			in.open(ROTOR_FILE_PATH.c_str(), std::ios::in);

			if (!in.is_open())
			{
				delete x;
				throw std::logic_error("ERROR 18-10: Rotor File could not be opened!"); // Throws a logic error to be caught when calling the function
			}

			while (in >> *x)
			{
				temp.push_back(*x);
			}
		}
		else
		{
			ROTOR_FILE_PATH += "/Module5.rot";
			in.open(ROTOR_FILE_PATH.c_str(), std::ios::in);

			if (!in.is_open())
			{
				delete x;
				throw std::logic_error("ERROR 18-10: Rotor File could not be opened!"); // Throws a logic error to be caught when calling the function
			}

			while (in >> *x)
			{
				temp.push_back(*x);
			}
		}

		in.close(); // Closes file
		delete x; // Deallocates memory for x

		// Sets the m_Rotator values to those from .rot files via the vector
		for (Enigma_Short i = 0; i < 26; i++)
			m_Rotator[i] = alphabet[temp[i]];

		temp.clear(); // Deletes all values from vector
		temp.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory
	}

	void Rotor::In(char& c) const
	{
		Enigma_Short* temp = new Enigma_Short{}; // Allocates memory for a temp unsigned short

		// Checks to see which letter was passed and sets temp to the location in alphabet
		for (Enigma_Short i = 0; i < 26; i++)
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
		for (Enigma_Short i = 0; i < 26; i++)
		{
			if (c == m_Rotator[i])
			{
				c = alphabet[i];
				break;
			}
		}

		// Logic to determine when to rotate
		if (m_RotNum != 1)
			(*m_Count)++;
		else
		{
			Rotate();
			return;
		}

		if (*m_Count >= 26 && m_RotNum == 2)
		{
			Rotate();
			*m_Count = 0;
		}
		else if (*m_Count >= (26 * 26))
		{
			Rotate();
			*m_Count = 0;
		}
	}
}