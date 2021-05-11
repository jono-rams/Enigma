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

Enigma::Core::~Core()
{
	delete m_PairModule;
}
