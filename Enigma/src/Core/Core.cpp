#include "Core.h"

static_assert(sizeof(void*) != 4, "Compile in 64-bit mode only");

namespace Enigma
{
	char Core::InternalEncrypt(char letter) const
	{
		bool *invalid = new bool{ true };
		for (ushort_t i = 0; i < 26; i++)
		{
			if (letter == alphabet[i])
			{
				*invalid = false;
				break;
			}
		}

		if (*invalid)
		{
			delete invalid;
			throw std::logic_error("Invalid character\n");
		}

		m_RotorF->In(letter);
		m_RotorS->In(letter);
		m_RotorT->In(letter);
		m_PairModule->PairOut(letter);
		m_RotorT->Out(letter);
		m_RotorS->Out(letter);
		m_RotorF->Out(letter);

		delete invalid;
		return letter;
	}

	Core::Core()
		: m_PairModule(nullptr), m_RotorF(nullptr), m_RotorS(nullptr), m_RotorT(nullptr)
	{
	}

	void Core::GenNewPairModule()
	{
		if (m_PairModule != nullptr)
		{
			delete m_PairModule;
			m_PairModule = nullptr;
		}
		m_PairModule = new Pair{};
	}

	void Core::GenNewPairModule(s_Pairs pairs[13])
	{
		if (m_PairModule != nullptr)
		{
			delete m_PairModule;
			m_PairModule = nullptr;
		}
		try
		{
			m_PairModule = new Pair{ pairs };
		}
		catch (std::logic_error err)
		{
			std::cout << err.what() << std::endl;
			delete m_PairModule;
			m_PairModule = nullptr;
			throw std::logic_error("Pair could not be generated!");
		}
	}

	void Core::GenNewRotorsModules(ushort_t Rot1, ushort_t Rot2, ushort_t Rot3)
	{
		if (Rot1 > 5 || Rot2 > 5 || Rot3 > 5)
			throw std::logic_error("Invalid Rotor Number!");

		if (m_RotorF != nullptr)
		{
			delete m_RotorF;
			delete m_RotorS;
			delete m_RotorT;

			m_RotorF = nullptr;
			m_RotorS = nullptr;
			m_RotorT = nullptr;
		}

		m_RotorF = new Rotor(1, Rot1);
		m_RotorS = new Rotor(2, Rot2);
		m_RotorT = new Rotor(3, Rot3);
	}

	void Core::SwitchRotorModule(ushort_t RotModuleNo, ushort_t Rot)
	{
		if (RotModuleNo == 1)
		{
			if (Rot == m_RotorS->GetSeed() || Rot == m_RotorT->GetSeed())
				throw std::logic_error("Rotor already in use in another module!");
			
			if (Rot == m_RotorF->GetSeed())
				return;
			
			if (Rot > 5)
				throw std::logic_error("Invalid Rotor Number!");

			delete m_RotorF;
			m_RotorF = nullptr;
			m_RotorF = new Rotor(1, Rot);
		}
		else if (RotModuleNo == 2)
		{
			if (Rot == m_RotorF->GetSeed() || Rot == m_RotorT->GetSeed())
				throw std::logic_error("Rotor already in use in another module!");
			
			if (Rot == m_RotorS->GetSeed())
				return;
			
			if (Rot > 5)
				throw std::logic_error("Invalid Rotor Number!");

			delete m_RotorS;
			m_RotorS = nullptr;
			m_RotorS = new Rotor(2, Rot);
		}
		else if (RotModuleNo == 3)
		{
			if (Rot == m_RotorS->GetSeed() || Rot == m_RotorF->GetSeed())			
				throw std::logic_error("Rotor already in use in another module!");
			
			if (Rot == m_RotorT->GetSeed())
				return;
			
			if (Rot > 5)
				throw std::logic_error("Invalid Rotor Number!");

			delete m_RotorT;
			m_RotorT = nullptr;
			m_RotorT = new Rotor(3, Rot);
		}
		else
		{
			throw std::logic_error("Only THREE(3) Rotor Modules");
		}
	}

	void Core::Encrypt(const std::string &word, std::string &output) const
	{
		std::vector<char> wordV;
		std::copy(word.begin(), word.end(), std::back_inserter(wordV));

		char *temp = new char;
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			try 
			{
				*temp = InternalEncrypt(wordV[i]);
			}
			catch (std::logic_error err)
			{
				throw err;
			}
			output.push_back(*temp);
		}
		wordV.clear();
		wordV.shrink_to_fit();
		delete temp;
	}

	std::string Core::Encrypt(const std::string& word) const
	{
		std::string output;
		std::vector<char> wordV;
		std::copy(word.begin(), word.end(), std::back_inserter(wordV));

		char* temp = new char;
		for (uint64_t i = 0; i < wordV.size(); i++)
		{
			try
			{
				*temp = InternalEncrypt(wordV[i]);
			}
			catch (std::logic_error err)
			{
				throw err;
			}
			output.push_back(*temp);
		}
		wordV.clear();
		wordV.shrink_to_fit();
		delete temp;

		return output;
	}

	Core::~Core()
	{
		delete m_PairModule;
		delete m_RotorF;
		delete m_RotorS;
		delete m_RotorT;
	}
}