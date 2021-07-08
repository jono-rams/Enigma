#include "Core.h"
#include "../Log/Log.h"

static_assert(sizeof(void*) != 4, "Compile in 64-bit mode only");

namespace Enigma
{
	char Core::InternalEncrypt(char letter) const
	{
		Log::WriteLog("Attempting to encrypt a character");
		bool* invalid = new bool{ true }; // Allocates memory for a bool that states whether an invalid character was entered

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
			Log::WriteLog("ERROR: Core.cpp - Invalid character entered for encryption");
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
		
		Log::WriteLog("Encrypted a character");
		return letter; // Returns encrypted letter
	}

	Core::Core()
		: m_PairModule(nullptr), m_RotorF(nullptr), m_RotorS(nullptr), m_RotorT(nullptr), m_RotPath(nullptr) // Sets all member variable pointers to nullptr
	{
		Log::WriteLog("Attempting to create Core class with default Constructor");
		Log::WriteLog("Core class created with default Constructor");
	}

	Core::Core(Core& obj)
	{
		Log::WriteLog("Attempting to create Core class with Copy Constructor");
		this->GenNewPairModule(obj.m_PairModule->GetPairs());

		this->SetRotorDataPath(*obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF->GetSeed(),
			obj.m_RotorS->GetSeed(),
			obj.m_RotorT->GetSeed()
		);

		Log::WriteLog("Core class created with Copy Constructor");
	}

	Core& Core::operator=(const Core& obj)
	{
		Log::WriteLog("Attempting to create Core class with Copy Assignment Operator");
		if (this == &obj) // Checks to see if the two objects are the same
		{
			return *this;
		}

		this->GenNewPairModule(obj.m_PairModule->GetPairs());

		this->SetRotorDataPath(*obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF->GetSeed(),
			obj.m_RotorS->GetSeed(),
			obj.m_RotorT->GetSeed()
		);

		Log::WriteLog("Core class created with Copy Assignment Operator");
		return *this;
	}

	Core::Core(Core&& obj) noexcept
	{
		Log::WriteLog("Attempting to create Core class with Move Constructor");
		this->GenNewPairModule(obj.m_PairModule->GetPairs());

		this->SetRotorDataPath(*obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF->GetSeed(),
			obj.m_RotorS->GetSeed(),
			obj.m_RotorT->GetSeed()
		);

		obj.m_PairModule = nullptr;
		obj.m_RotorF = nullptr;
		obj.m_RotorS = nullptr;
		obj.m_RotorT = nullptr;
		obj.m_RotPath = nullptr;

		Log::WriteLog("Core class created with Move Constructor");
	}

	Core& Core::operator=(Core&& obj) noexcept
	{
		Log::WriteLog("Attempting to create Core class with Move Assignment Operator");
		if (this == &obj) // Checks to see if the two objects are the same
		{
			return *this;
		}

		this->GenNewPairModule(obj.m_PairModule->GetPairs());

		this->SetRotorDataPath(*obj.m_RotPath);

		this->GenNewRotorsModules(
			obj.m_RotorF->GetSeed(),
			obj.m_RotorS->GetSeed(),
			obj.m_RotorT->GetSeed()
		);

		obj.m_PairModule = nullptr;
		obj.m_RotorF = nullptr;
		obj.m_RotorS = nullptr;
		obj.m_RotorT = nullptr;
		obj.m_RotPath = nullptr;

		Log::WriteLog("Core class created with Move Assignment Operator");

		return *this;
	}

	void Core::GenNewPairModule()
	{
		Log::WriteLog("Generating default pair modules");
		// Checks to see if a pair module was already created
		if (m_PairModule != nullptr)
		{
			// Deallocates memory for pair module and sets to nullptr
			delete m_PairModule;
			m_PairModule = nullptr;
		}

		m_PairModule = new Pair{}; // Allocates memory for a new Pair created with the default constructor

		Log::WriteLog("Default Pair Modules generated for Core class");
	}

	void Core::GenNewPairModule(s_Pairs pairs[13])
	{
		Log::WriteLog("Generating custom pair modules");
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
			Log::WriteLog("ERROR: Core.cpp - Pair could not be generated!");
			throw std::logic_error("Pair could not be generated!"); // Throws a logic error to be caught when calling the function
		}

		Log::WriteLog("Custom Pair Modules generated for Core class");
	}

	void Core::SetRotorDataPath(std::string path)
	{
		Log::WriteLog("Setting Rotor Data Path");
		if (m_RotPath != nullptr)
		{
			delete m_RotPath;
			m_RotPath = nullptr;
		}
		m_RotPath = new std::string(path);
		
		Log::WriteLog("Rotor Data Path set");
	}

	void Core::GenNewRotorsModules(ushort_t Rot1, ushort_t Rot2, ushort_t Rot3)
	{
		Log::WriteLog("Generating Rotor Modules");
		// Check to make sure none of the seed values are greater than 5
		if (Rot1 > 5 || Rot2 > 5 || Rot3 > 5)
		{
			Log::WriteLog("ERROR: Core.cpp - Rotor Modules not generated because of Invalid Rotor Number!");
			throw std::logic_error("Invalid Rotor Number!"); // Throws a logic error to be caught when calling the function
		} 

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

		Log::WriteLog("Rotor Modules generated");
	}

	void Core::SwitchRotorModule(ushort_t RotModuleNo, ushort_t Rot)
	{
		std::string rm = "Rotor Module " + RotModuleNo;
		std::string temp = "Switching " + rm;
		Log::WriteLog(temp);
		s_EnigmaTimer t;
		if (Rot > 5 || Rot <= 0)
		{
			Log::WriteLog("ERROR: Core.cpp - Rotor Modules not generated because of Invalid Rotor Number!");
			throw std::logic_error("Invalid Rotor Number!"); // Throws a logic error to be caught when calling the function
		}

		// Checks which rotor module is being switched
		if (RotModuleNo == 1)
		{
			// Checks to make sure seed value is not being used in another rotor module
			if (Rot == m_RotorS->GetSeed() || Rot == m_RotorT->GetSeed())
			{
				std::string temp = "Rotor " + Rot;
				temp += " already in use in another module (" + RotModuleNo;
				temp += +")";
				Log::WriteLog(temp);
				throw std::logic_error("Rotor already in use in another module!"); // Throws a logic error to be caught when calling the function
			}
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
			{
				std::string temp = "Rotor " + Rot;
				temp += " already in use in another module (" + RotModuleNo;
				temp += +")";
				Log::WriteLog(temp);
				throw std::logic_error("Rotor already in use in another module!"); // Throws a logic error to be caught when calling the function
			}

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
			{
				std::string temp = "Rotor " + Rot;
				temp += " already in use in another module (" + RotModuleNo;
				temp += +")";
				Log::WriteLog(temp);
				throw std::logic_error("Rotor already in use in another module!"); // Throws a logic error to be caught when calling the function
			}

			if (Rot == m_RotorT->GetSeed()) // Checks to see if Rotor module is the same as current one
				return;

			// Deallocates memory for rotor module and sets to nullptr, then creates and allocates memory for Rotor module
			delete m_RotorT;
			m_RotorT = nullptr;
			m_RotorT = new Rotor(3, Rot, *m_RotPath);
		}
		else // If user is trying to set to a rotor module that does not exist
		{
			Log::WriteLog("ERROR: Core.cpp - Invalid Rotor Module was selected to be switched.");
			throw std::logic_error("Only THREE(3) Rotor Modules"); // Throws a logic error to be caught when calling the function
		}
		temp = "Switched " + rm;
	}

	void Core::OffsetRotor(uint64_t offset)
	{
		Log::WriteLog("Offseting Rotor modules");
		std::string temp;
		for (uint64_t i = 0; i < offset; i++)
		{
			temp.push_back('a');
		}
		temp = Encrypt(temp);

		temp = "Rotor modules offset";

		Log::WriteLog(temp);
	}

	void Core::Encrypt(const std::string& word, std::string& output) const
	{
		Log::WriteLog("Started Encrypting using void (string, string) Encrypt function");

		std::vector<char> wordV; // Vector to hold all values from word
		std::copy(word.begin(), word.end(), std::back_inserter(wordV)); // Copies characters from string to vector

		char temp{}; // Temporary variable to hold encrypted character

		// Loop that runs through all characters in vector
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			// Error Handling
			try
			{
				temp = InternalEncrypt(wordV[i]); // Calls internal Encryption for letter
			}
			catch (std::logic_error err)
			{
				output.clear(); // Deletes output data since error was found
				throw err; // Throws caught logic error to be caught when calling the function
			}
			output.push_back(temp); // Adds letter to output string
		}
		wordV.clear(); // Deletes all values from vector
		wordV.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory

		Log::WriteLog("Encrypted using void (string, string) Encrypt function");
	}

	void Core::Encrypt(const std::string& word, std::fstream& output) const
	{
		Log::WriteLog("Started Encrypting using void (string, fstream) Encrypt function");

		// Makes sure file is open else throws a runtime error
		if (!output.is_open())
		{
			Log::WriteLog("ERROR: Core.cpp - File was not opened!");
			throw std::runtime_error("Please open file before calling this function!");
		}

		std::vector<char> wordV; // Vector to hold all values from word
		std::copy(word.begin(), word.end(), std::back_inserter(wordV)); // Copies characters from string to vector

		char temp{}; // Temporary variable to hold encrypted character

		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			// Error Handling
			try
			{
				temp = InternalEncrypt(wordV[i]); // Calls internal Encryption for letter
			}
			catch (std::logic_error err)
			{
				throw err; // Throws caught logic error to be caught when calling the function
			}
			output << temp;
		}
		wordV.clear(); // Deletes all values from vector
		wordV.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory

		Log::WriteLog("Encrypted using void (string, fstream) Encrypt function");
	}

	std::string Core::Encrypt(const std::string& word) const
	{
		Log::WriteLog("Started Encrypting using string (string) Encrypt function");

		std::string output; // Temporary string to return
		std::vector<char> wordV; // Vector to hold all values from word
		std::copy(word.begin(), word.end(), std::back_inserter(wordV)); // Copies characters from string to vector

		char temp{}; // Temporary variable to hold encrypted character

		// Loop that runs through all characters in vector
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			// Error Handling
			try
			{
				temp = InternalEncrypt(wordV[i]); // Calls internal Encryption for letter
			}
			catch (std::logic_error err)
			{
				throw err; // Throws caught logic error to be caught when calling the function
			}
			output.push_back(temp); // Adds letter to output string
		}
		wordV.clear(); // Deletes all values from vector
		wordV.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory

		Log::WriteLog("Encrypted using string (string) Encrypt function");

		return std::move(output); // Returns output string
	}
	
	void Core::Encrypt(std::fstream &word, std::string &output) const
	{	
		// Makes sure file is open else throws a runtime error
		if (!word.is_open())
		{
			Log::WriteLog("ERROR: Core.cpp - File was not opened!");
			throw std::runtime_error("Please open file before calling this function!");
		}
		
		// Reads word from file and puts it in a char vector
		std::vector<char> wordV; // Vector to hold all values from word
		char temp{}; // Temporary variable to hold encrypted character
		while(word >> temp)
		{
			wordV.push_back(temp);
		}
		
		// Loop that runs through all characters in vector
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			// Error Handling
			try
			{
				temp = InternalEncrypt(wordV[i]); // Calls internal Encryption for letter
			}
			catch (std::logic_error err)
			{
				output.clear(); // Deletes output data since error was found
				throw err; // Throws caught logic error to be caught when calling the function
			}
			output.push_back(temp); // Adds letter to output string
		}
		wordV.clear(); // Deletes all values from vector
		wordV.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory

		Log::WriteLog("Encrypted using void (fstream, string) Encrypt function");
	}
	
	void Core::Encrypt(std::fstream &word, std::fstream &output) const
	{	
		// Makes sure file is open else throws a runtime error
		if (!word.is_open())
		{
			Log::WriteLog("ERROR: Core.cpp - File was not opened!");
			throw std::runtime_error("Please open file before calling this function!");
		}
		if (!output.is_open())
		{
			Log::WriteLog("ERROR: Core.cpp - File was not opened!");
			throw std::runtime_error("Please open file before calling this function!");
		}
		
		// Reads word from file and puts it in a char vector
		std::vector<char> wordV; // Vector to hold all values from word
		char temp{}; // Temporary variable to hold encrypted character
		while(word >> temp)
		{
			wordV.push_back(temp);
		}

		// Loop that runs through all characters in vector
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			// Error Handling
			try
			{
				temp = InternalEncrypt(wordV[i]); // Calls internal Encryption for letter
			}
			catch (std::logic_error err)
			{
				output.clear(); // Deletes output data since error was found
				throw err; // Throws caught logic error to be caught when calling the function
			}
			output.push_back(temp); // Adds letter to output string
		}
		wordV.clear(); // Deletes all values from vector
		wordV.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory
		
		Log::WriteLog("Encrypted using void (fstream, fstream) Encrypt function");
	}

	std::string Encrypt(std::fstream &word) const
	{
		// Makes sure file is open else throws a runtime error
		if (!word.is_open())
		{
			Log::WriteLog("ERROR: Core.cpp - File was not opened!");
			throw std::runtime_error("Please open file before calling this function!");
		}
		
		// Reads word from file and puts it in a char vector
		std::vector<char> wordV; // Vector to hold all values from word
		char temp{}; // Temporary variable to hold encrypted character
		while(word >> temp)
		{
			wordV.push_back(temp);
		}
		
		// Loop that runs through all characters in vector
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			// Error Handling
			try
			{
				temp = InternalEncrypt(wordV[i]); // Calls internal Encryption for letter
			}
			catch (std::logic_error err)
			{
				throw err; // Throws caught logic error to be caught when calling the function
			}
			output.push_back(temp); // Adds letter to output string
		}
		wordV.clear(); // Deletes all values from vector
		wordV.shrink_to_fit(); // Shrinks the vector to 0 to deallocate memory

		Log::WriteLog("Encrypted using string (fstream) Encrypt function");

		return std::move(output); // Returns output string
	}
	
	Core::~Core()
	{
		Log::WriteLog("Deleting Core class");
		// Deallocates memory for all member variables
		delete m_PairModule;
		delete m_RotorF;
		delete m_RotorS;
		delete m_RotorT;
		delete m_RotPath;

		Log::WriteLog("Deleted Core class");
	}
}
