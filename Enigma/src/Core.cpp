#include <Core/Core.h>

#include <vector>

namespace Enigma
{

	Core::Core(Core& obj)
	{
		this->GenNewPairModule(obj.m_PairModule.GetPairs());

		this->SetRotorDataPath(obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF.GetSeed(),
			obj.m_RotorS.GetSeed(),
			obj.m_RotorT.GetSeed()
		);
	}

	Core& Core::operator=(const Core& obj)
	{
		if (this == &obj) // Checks to see if the two objects are the same
		{
			return *this;
		}

		this->GenNewPairModule(obj.m_PairModule.GetPairs());

		this->SetRotorDataPath(obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF.GetSeed(),
			obj.m_RotorS.GetSeed(),
			obj.m_RotorT.GetSeed()
		);

		return *this;
	}

	Core::Core(Core&& obj) noexcept
	{
		this->GenNewPairModule(obj.m_PairModule.GetPairs());

		this->SetRotorDataPath(obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF.GetSeed(),
			obj.m_RotorS.GetSeed(),
			obj.m_RotorT.GetSeed()
		);
	}

	Core& Core::operator=(Core&& obj) noexcept
	{
		if (this == &obj) // Checks to see if the two objects are the same
		{
			return *this;
		}

		this->GenNewPairModule(obj.m_PairModule.GetPairs());

		this->SetRotorDataPath(obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF.GetSeed(),
			obj.m_RotorS.GetSeed(),
			obj.m_RotorT.GetSeed()
		);
		return *this;
	}

	void Core::InternalEncrypt(char& letter)
	{
		bool invalid{ true }; // A bool that states whether an invalid character was entered

		// Checks to see if letter is in the alphabet (a valid character)
		for (Enigma_Short i = 0; i < 26; i++)
		{
			if (letter == alphabet[i])
			{
				invalid = false;
				break;
			}
		}

		// Checks to see if an invalid character was entered
		if (invalid)
		{
			throw std::logic_error("ERROR 03-00: Invalid character\n"); // Throws a logic error to be caught when calling the function
		}

		// Encryption logic
		m_RotorF.In(letter);
		m_RotorS.In(letter);
		m_RotorT.In(letter);
		m_PairModule.PairOut(letter);
		m_RotorT.Out(letter);
		m_RotorS.Out(letter);
		m_RotorF.Out(letter);
	}

	void Core::GenNewPairModule()
	{
		m_PairModule.SetPairs();
	}

#ifdef ENIGMA_USE_STD_PAIR
	void Core::GenNewPairModule(std::array<std::pair<char, char>, 13> pairs)
	{
		// Error Handling
		try
		{
			m_PairModule.SetPairs(pairs);
		}
		catch (std::logic_error& err)
		{
			std::cout << err.what() << std::endl;
			throw std::logic_error("ERROR 16-00 - Pair could not be generated!"); // Throws a logic error to be caught when calling the function
		}
	}
#else
	void Core::GenNewPairModule(std::array<s_Pairs, 13> pairs)
	{
		// Error Handling
		try
		{
			m_PairModule.SetPairs(pairs);
		}
		catch (std::logic_error& err)
		{
			std::cout << err.what() << std::endl;
			throw std::logic_error("ERROR 16-00 - Pair could not be generated!"); // Throws a logic error to be caught when calling the function
		}
	}
#endif

	void Core::GenNewRotorsModules(Enigma_Short Rot1, Enigma_Short Rot2, Enigma_Short Rot3)
	{
		// Check to make sure none of the seed values are greater than 5
		if (Rot1 > 5 || Rot2 > 5 || Rot3 > 5)
			throw std::logic_error("ERROR 18-00A: Invalid Rotor Number!"); // Throws a logic error to be caught when calling the function

		// Creates and allocates memory for Rotor modules in order
		try
		{
			m_RotorF.SetRotor(1, Rot1, m_RotPath);
		}
		catch (std::logic_error& err)
		{
			std::cout << err.what() << std::endl;
			throw std::logic_error("ERROR 18-03A: Rotor 1 could not be generated!"); // Throws a logic error to be caught when calling the function
		}

		try
		{
			m_RotorS.SetRotor(2, Rot2, m_RotPath);
		}
		catch (std::logic_error& err)
		{
			std::cout << err.what() << std::endl;
			throw std::logic_error("ERROR 18-03A: Rotor 2 could not be generated!"); // Throws a logic error to be caught when calling the function
		}

		try
		{
			m_RotorT.SetRotor(3, Rot1, m_RotPath);
		}
		catch (std::logic_error& err)
		{
			std::cout << err.what() << std::endl;
			throw std::logic_error("ERROR 18-03A: Rotor 3 could not be generated!"); // Throws a logic error to be caught when calling the function
		}
	}

	void Core::SwitchRotorModule(Enigma_Short RotModuleNo, Enigma_Short Rot)
	{
		if (Rot > 5)
			throw std::logic_error("ERROR 18-00B: Invalid Rotor Number!"); // Throws a logic error to be caught when calling the function

		// Checks which rotor module is being switched
		if (RotModuleNo == 1)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorS.GetSeed() || Rot == m_RotorT.GetSeed())
				throw std::logic_error("ERROR 18-01: Rotor already in use in another sub-module!"); // Throws a logic error to be caught when calling the function

			if (Rot == m_RotorF.GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			try
			{
				m_RotorF.SetRotor(1, Rot, m_RotPath);
			}
			catch (std::logic_error& err)
			{
				std::cout << err.what() << std::endl;
				throw std::logic_error("ERROR 18-03B: Rotor 1 could not be generated!"); // Throws a logic error to be caught when calling the function
			}
		}
		else if (RotModuleNo == 2)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorF.GetSeed() || Rot == m_RotorT.GetSeed())
				throw std::logic_error("ERROR 18-01: Rotor already in use in another sub-module!"); // Throws a logic error to be caught when calling the function

			if (Rot == m_RotorS.GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			try
			{
				m_RotorS.SetRotor(2, Rot, m_RotPath);
			}
			catch (std::logic_error& err)
			{
				std::cout << err.what() << std::endl;
				throw std::logic_error("ERROR 18-03B: Rotor 2 could not be generated!"); // Throws a logic error to be caught when calling the function
			}
		}
		else if (RotModuleNo == 3)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorS.GetSeed() || Rot == m_RotorF.GetSeed())
				throw std::logic_error("ERROR 18-01: Rotor already in use in sub-another module!"); // Throws a logic error to be caught when calling the function

			if (Rot == m_RotorT.GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			try
			{
				m_RotorF.SetRotor(3, Rot, m_RotPath);
			}
			catch (std::logic_error& err)
			{
				std::cout << err.what() << std::endl;
				throw std::logic_error("ERROR 18-03B: Rotor 3 could not be generated!"); // Throws a logic error to be caught when calling the function
			}
		}
		else // If user is trying to set to a rotor module that does not exist
		{
			throw std::logic_error("ERROR 18-02: Trying to change Rotor Sub-Module that does NOT exist!"); // Throws a logic error to be caught when calling the function
		}
	}

	void Core::OffsetRotor(uint64_t offset)
	{
		std::string temp;
		for (uint64_t i = 0; i < offset; i++)
		{
			temp.push_back('a');
		}
		Encrypt(temp);
	}

	std::string Core::Encrypt(const std::string& word)
	{
		std::string output; // Temporary string to return
		std::vector<char> wordV; // Vector to hold all values from word
		std::copy(word.begin(), word.end(), std::back_inserter(wordV)); // Copies characters from string to vector

		char* temp = new char;// Temporary variable to hold encrypted character

		// Loop that runs through all characters in vector
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			*temp = wordV[i];
			// Error Handling
			try
			{
				InternalEncrypt(*temp); // Calls internal Encryption for letter
			}
			catch (std::logic_error& err)
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

	void Core::Encrypt(const std::string& word, std::string& output)
	{
		output = Encrypt(word);
	}

	char* Core::Encrypt(const char* word)
	{
		std::string str{ word };
		str = Encrypt(str);

		auto size = str.length();
		char* out = new char[size];
		
		for (int i = 0; i < size; i++)
			out[i] = str[i];

		return out;
	}
}