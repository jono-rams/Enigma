#include "../../include/Core/Core.h"

#include <vector>

static_assert(sizeof(void*) != 4, "Compile in 64-bit mode only");

namespace Enigma
{
	char Core::InternalEncrypt(char letter) const
	{
		bool *invalid = new bool{ true }; // Allocates memory for a bool that states whether an invalid character was entered
		
		// Checks to see if letter is in the alphabet (a valid character)
		for (ushort_t i = 0; i < 26; i++)
		{
			if (letter == alphabet[i])
			{
				*invalid = false;
				break;
			}
		}

		// Checks to see if an invalid character was entered
		if (*invalid)
		{
			delete invalid; // Deallocates memory for invalid
			throw std::logic_error("Invalid character\n"); // Throws a logic error to be caught when calling the function
		}
		delete invalid; // Deallocates memory for invalid

		// Encryption logic
		m_RotorF->In(letter);
		m_RotorS->In(letter);
		m_RotorT->In(letter);
		m_PairModule->PairOut(letter);
		m_RotorT->Out(letter);
		m_RotorS->Out(letter);
		m_RotorF->Out(letter);

		return letter; // Returns encrypted letter
	}

	Core::Core()
		: m_PairModule(nullptr), m_RotorF(nullptr), m_RotorS(nullptr), m_RotorT(nullptr), m_RotPath(nullptr) // Sets all member variable pointers to nullptr
	{
	}

	void Core::GenNewPairModule()
	{
		// Checks to see if a pair module was already created
		if (m_PairModule != nullptr)
		{
			// Deallocates memory for pair module and sets to nullptr
			delete m_PairModule;
			m_PairModule = nullptr;
		}

		m_PairModule = new Pair{}; // Allocates memory for a new Pair created with the default constructor
	}

	void Core::GenNewPairModule(s_Pairs pairs[13])
	{
		// Checks to see if a pair module was already created
		if (m_PairModule != nullptr)
		{
			// Deallocates memory for pair module and sets to nullptr
			delete m_PairModule;
			m_PairModule = nullptr;
		}

		// Error Handling
		try
		{
			m_PairModule = new Pair{ pairs }; // Allocates memory for a new Pair created with the default constructor
		}
		catch (std::logic_error err)
		{
			std::cout << err.what() << std::endl;
			delete m_PairModule;
			m_PairModule = nullptr;
			throw std::logic_error("Pair could not be generated!"); // Throws a logic error to be caught when calling the function
		}
	}

	void Core::SetRotorDataPath(std::string path)
	{
		if (m_RotPath != nullptr)
		{
			delete m_RotPath;
			m_RotPath = nullptr;
		}
		m_RotPath = new std::string(path);
	}

	void Core::GenNewRotorsModules(ushort_t Rot1, ushort_t Rot2, ushort_t Rot3)
	{
		// Check to make sure none of the seed values are greater than 5
		if (Rot1 > 5 || Rot2 > 5 || Rot3 > 5)
			throw std::logic_error("Invalid Rotor Number!"); // Throws a logic error to be caught when calling the function

		// Checks to see if rotor modules were already created
		if (m_RotorF != nullptr)
		{
			// Deallocates memory for rotor modules and sets to nullptr
			delete m_RotorF;
			delete m_RotorS;
			delete m_RotorT;

			m_RotorF = nullptr;
			m_RotorS = nullptr;
			m_RotorT = nullptr;
		}

		// Creates and allocates memory for Rotor modules in order
		m_RotorF = new Rotor(1, Rot1, *m_RotPath);
		m_RotorS = new Rotor(2, Rot2, *m_RotPath);
		m_RotorT = new Rotor(3, Rot3, *m_RotPath);
	}

	void Core::SwitchRotorModule(ushort_t RotModuleNo, ushort_t Rot)
	{
		if (Rot > 5)
			throw std::logic_error("Invalid Rotor Number!"); // Throws a logic error to be caught when calling the function

		// Checks which rotor module is being switched
		if (RotModuleNo == 1)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorS->GetSeed() || Rot == m_RotorT->GetSeed())
				throw std::logic_error("Rotor already in use in another module!"); // Throws a logic error to be caught when calling the function
			
			if (Rot == m_RotorF->GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			// Deallocates memory for rotor module and sets to nullptr, then creates and allocates memory for Rotor module
			delete m_RotorF;
			m_RotorF = nullptr;
			m_RotorF = new Rotor(1, Rot, *m_RotPath);
		}
		else if (RotModuleNo == 2)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorF->GetSeed() || Rot == m_RotorT->GetSeed())
				throw std::logic_error("Rotor already in use in another module!"); // Throws a logic error to be caught when calling the function
			
			if (Rot == m_RotorS->GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			// Deallocates memory for rotor module and sets to nullptr, then creates and allocates memory for Rotor module
			delete m_RotorS;
			m_RotorS = nullptr;
			m_RotorS = new Rotor(2, Rot, *m_RotPath);
		}
		else if (RotModuleNo == 3)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorS->GetSeed() || Rot == m_RotorF->GetSeed())			
				throw std::logic_error("Rotor already in use in another module!"); // Throws a logic error to be caught when calling the function
			
			if (Rot == m_RotorT->GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			// Deallocates memory for rotor module and sets to nullptr, then creates and allocates memory for Rotor module
			delete m_RotorT;
			m_RotorT = nullptr;
			m_RotorT = new Rotor(3, Rot, *m_RotPath);
		}
		else // If user is trying to set to a rotor module that does not exist
		{
			throw std::logic_error("Only THREE(3) Rotor Modules"); // Throws a logic error to be caught when calling the function
		}
	}

	void Core::Encrypt(const std::string &word, std::string &output) const
	{
		std::vector<char> wordV; // Vector to hold all values from word
		std::copy(word.begin(), word.end(), std::back_inserter(wordV)); // Copies characters from string to vector

		char *temp = new char; // Temporary variable to hold encrypted character
		
		// Loop that runs through all characters in vector
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			// Error Handling
			try 
			{
				*temp = InternalEncrypt(wordV[i]); // Calls internal Encryption for letter
			}
			catch (std::logic_error err)
			{
				output.clear(); // Deletes output data since error was found
				throw err; // Throws caught logic error to be caught when calling the function
			}
			output.push_back(*temp); // Adds letter to output string
		}
		wordV.clear(); // Deletes all values from vector
		wordV.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory
		delete temp; // Deallocates memory for temp
	}

	std::string Core::Encrypt(const std::string& word) const
	{
		std::string output; // Temporary string to return
		std::vector<char> wordV; // Vector to hold all values from word
		std::copy(word.begin(), word.end(), std::back_inserter(wordV)); // Copies characters from string to vector

		char* temp = new char;// Temporary variable to hold encrypted character

		// Loop that runs through all characters in vector
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			// Error Handling
			try
			{
				*temp = InternalEncrypt(wordV[i]); // Calls internal Encryption for letter
			}
			catch (std::logic_error err)
			{
				throw err; // Throws caught logic error to be caught when calling the function
			}
			output.push_back(*temp); // Adds letter to output string
		}
		wordV.clear(); // Deletes all values from vector
		wordV.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory
		delete temp; // Deallocates memory for temp

		return std::move(output); // Returns output string
	}

	Core::~Core()
	{
		// Deallocates memory for all member variables
		delete m_PairModule;
		delete m_RotorF;
		delete m_RotorS;
		delete m_RotorT;
		delete m_RotPath;
	}
}