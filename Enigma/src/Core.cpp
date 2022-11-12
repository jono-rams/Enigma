#include <Core/Core.h>

#include <vector>

namespace Enigma
{
	Core::Core()
		: m_PairModule(), m_RotorF(), m_RotorS(), m_RotorT(), m_PlugBoard(),
		m_RotPath("RotorModules")
	{

	}

	Core::Core(Core& obj)
	{
		this->GenNewReflector(obj.m_PairModule.GetPairs());

		this->SetRotorDataPath(obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF.GetSeed(),
			obj.m_RotorS.GetSeed(),
			obj.m_RotorT.GetSeed()
		);

		this->m_PlugBoard = m_PlugBoard;
	}

	Core& Core::operator=(const Core& obj)
	{
		if (this == &obj) // Checks to see if the two objects are the same
		{
			return *this;
		}

		this->GenNewReflector(obj.m_PairModule.GetPairs());

		this->SetRotorDataPath(obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF.GetSeed(),
			obj.m_RotorS.GetSeed(),
			obj.m_RotorT.GetSeed()
		);

		this->m_PlugBoard = m_PlugBoard;

		return *this;
	}

	Core::Core(Core&& obj) noexcept
	{
		this->GenNewReflector(obj.m_PairModule.GetPairs());

		this->SetRotorDataPath(obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF.GetSeed(),
			obj.m_RotorS.GetSeed(),
			obj.m_RotorT.GetSeed()
		);

		this->m_PlugBoard = m_PlugBoard;
	}

	Core& Core::operator=(Core&& obj) noexcept
	{
		if (this == &obj) // Checks to see if the two objects are the same
		{
			return *this;
		}

		this->GenNewReflector(obj.m_PairModule.GetPairs());

		this->SetRotorDataPath(obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF.GetSeed(),
			obj.m_RotorS.GetSeed(),
			obj.m_RotorT.GetSeed()
		);

		this->m_PlugBoard = m_PlugBoard;

		return *this;
	}

	EnigmaError Core::InternalEncrypt(char& letter)
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
			return EnigmaError::E03_00; // Throws a logic error to be caught when calling the function
		}

		// Encryption logic
		m_PlugBoard.PlugBoardOut(letter);
		m_RotorF.In(letter);
		m_RotorS.In(letter);
		m_RotorT.In(letter);
		m_PairModule.ReflectorOut(letter);
		m_RotorT.Out(letter);
		m_RotorS.Out(letter);
		m_RotorF.Out(letter);
		m_PlugBoard.PlugBoardOut(letter);

		return EnigmaError::NO_ERROR;
	}

	void Core::GenNewReflector()
	{
		m_PairModule.SetPairs();
	}

#ifdef ENIGMA_USE_STD_PAIR
	EnigmaError Core::GenNewReflector(std::array<std::pair<char, char>, 13> pairs)
	{
		// Error Handling
		try
		{
			m_PairModule.SetPairs(pairs);
		}
		catch (std::logic_error& err)
		{
			std::cout << err.what() << std::endl;
			return EnigmaError::E16_00; // Throws a logic error to be caught when calling the function
		}

		return EnigmaError::NO_ERROR;
	}
#else
	EnigmaError Core::GenNewReflector(std::array<Enigma_Pairs, 13> pairs)
	{
		// Error Handling
		try
		{
			m_PairModule.SetPairs(pairs);
		}
		catch (std::logic_error& err)
		{
			std::cout << err.what() << std::endl;
			return EnigmaError::E16_00; // Throws a logic error to be caught when calling the function
		}

		return EnigmaError::NO_ERROR;
	}
#endif

	EnigmaError Core::GenNewRotorsModules(Enigma_64 Rot1, Enigma_64 Rot2, Enigma_64 Rot3)
	{
		const auto NumberOfModules = Rotor::GetNumberOfModules();
		// Check to make sure none of the seed values are greater than 5
		if (Rot1 > NumberOfModules || Rot2 > NumberOfModules || Rot3 > NumberOfModules)
			return EnigmaError::E18_00A; // Throws a logic error to be caught when calling the function

		// Creates and allocates memory for Rotor modules in order
		auto res = m_RotorF.SetRotor(1, Rot1, m_RotPath);

		if (res != EnigmaError::NO_ERROR)
		{
			std::cout << res << std::endl;
			return EnigmaError::E18_03A; // Throws a logic error to be caught when calling the function
		}

		res = m_RotorF.SetRotor(2, Rot2, m_RotPath);

		if (res != EnigmaError::NO_ERROR)
		{
			std::cout << res << std::endl;
			return EnigmaError::E18_03A; // Throws a logic error to be caught when calling the function
		}

		res = m_RotorF.SetRotor(1, Rot1, m_RotPath);

		if (res != EnigmaError::NO_ERROR)
		{
			std::cout << res << std::endl;
			return EnigmaError::E18_03A; // Throws a logic error to be caught when calling the function
		}

		return EnigmaError::NO_ERROR;
	}

	EnigmaError Core::SwitchRotorModule(Enigma_Short RotModuleNo, Enigma_64 Rot)
	{
		if (Rot > Rotor::GetNumberOfModules())
			return EnigmaError::E18_00B; // Throws a logic error to be caught when calling the function

		// Checks which rotor module is being switched
		if (RotModuleNo == 1)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorS.GetSeed() || Rot == m_RotorT.GetSeed())
				return EnigmaError::E18_01; // Throws a logic error to be caught when calling the function

			if (Rot == m_RotorF.GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			auto res = m_RotorF.SetRotor(1, Rot, m_RotPath);

			if (res != EnigmaError::NO_ERROR)
			{
				std::cout << res << std::endl;
				return EnigmaError::E18_03B; // Throws a logic error to be caught when calling the function
			}

		}
		else if (RotModuleNo == 2)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorF.GetSeed() || Rot == m_RotorT.GetSeed())
				return EnigmaError::E18_01; // Throws a logic error to be caught when calling the function

			if (Rot == m_RotorS.GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			auto res = m_RotorF.SetRotor(2, Rot, m_RotPath);

			if (res != EnigmaError::NO_ERROR)
			{
				std::cout << res << std::endl;
				return EnigmaError::E18_03B; // Throws a logic error to be caught when calling the function
			}
		}
		else if (RotModuleNo == 3)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorS.GetSeed() || Rot == m_RotorF.GetSeed())
				return EnigmaError::E18_01; // Throws a logic error to be caught when calling the function

			if (Rot == m_RotorT.GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			auto res = m_RotorF.SetRotor(3, Rot, m_RotPath);

			if (res != EnigmaError::NO_ERROR)
			{
				std::cout << res << std::endl;
				return EnigmaError::E18_03B; // Throws a logic error to be caught when calling the function
			}
		}
		else // If user is trying to set to a rotor module that does not exist
		{
			return EnigmaError::E18_02; // Throws a logic error to be caught when calling the function
		}

		return EnigmaError::NO_ERROR;
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

			auto res = InternalEncrypt(*temp); // Calls internal Encryption for letter
			if (res != EnigmaError::NO_ERROR)
				throw Errors[res]; // Throws caught logic error to be caught when calling the function

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