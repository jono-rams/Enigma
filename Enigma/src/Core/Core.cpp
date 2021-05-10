#include "Core.h"

Enigma::Core::Core()
	: m_PairModule(nullptr)
{
}

void Enigma::Core::GenPairModule()
{
	if (m_PairModule != nullptr)
	{
		delete m_PairModule;
		m_PairModule = nullptr;
	}
	m_PairModule = new Pair{};
}

void Enigma::Core::GenPairModule(s_Pairs pairs[13])
{
	if (m_PairModule != nullptr)
	{
		delete m_PairModule;
		m_PairModule = nullptr;
	}
	m_PairModule = new Pair{ pairs };
}

Enigma::Core::~Core()
{
	delete m_PairModule;
}
