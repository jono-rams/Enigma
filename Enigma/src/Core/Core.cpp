#include "Core.h"

namespace Enigma
{
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
			std::cout << "Pair could not be generated!\n";
			delete m_PairModule;
			m_PairModule = nullptr;
		}
	}

	void Core::GenNewRotorsModules(ushort_t Rot1, ushort_t Rot2, ushort_t Rot3)
	{
		if (Rot1 > 5 || Rot2 > 5 || Rot3 > 5)
			throw std::logic_error("Invalid Rotor Number!");

		seeds[0] = Rot1;
		seeds[1] = Rot2;
		seeds[2] = Rot3;

		m_RotorF = new Rotor(true, Rot1);
		m_RotorS = new Rotor(false, Rot2);
		m_RotorT = new Rotor(false, Rot3);
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
			m_RotorF = new Rotor(true, Rot);
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
			m_RotorS = new Rotor(false, Rot);
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
			m_RotorT = new Rotor(false, Rot);
		}
		else
		{
			throw std::logic_error("Only THREE(3) Rotor Modules");
		}
	}

	char Core::Encrypt(char letter) const
	{
		bool invalid{ true };
		for (ushort_t i = 0; i < 26; i++)
		{
			if (letter == alphabet[i])
			{
				invalid = false;
				break;
			}
		}

		if (invalid)
			throw std::logic_error("Invalid character\n");

		m_RotorF->In(letter);
		m_RotorS->In(letter);
		m_RotorT->In(letter);
		m_PairModule->PairOut(letter);
		m_RotorT->Out(letter);
		m_RotorS->Out(letter);
		m_RotorF->Out(letter);

		return letter;
	}

	Core::~Core()
	{
		delete m_PairModule;
	}
}