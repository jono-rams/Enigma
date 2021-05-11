#include "Core.h"

Enigma::Core::Core()
	: m_PairModule(nullptr)
{
}

void Enigma::Core::GenNewPairModule()
{
	if (m_PairModule != nullptr)
	{
		delete m_PairModule;
		m_PairModule = nullptr;
	}
	m_PairModule = new Pair{};
}

void Enigma::Core::GenNewPairModule(s_Pairs pairs[13])
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

char Enigma::Core::Encrypt(char letter) const
{
	bool invalid{ true };
	for (int i = 0; i < 26; i++)
	{
		if (letter == alphabet[i])
		{
			invalid = false;
			break;
		}
	}

	if (invalid)
		throw std::logic_error("Invalid character\n");

	return m_PairModule->PairOut(letter);
}

Enigma::Core::~Core()
{
	delete m_PairModule;
}
