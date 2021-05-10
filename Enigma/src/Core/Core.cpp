#include "Core.h"

Enigma::Core::Core()
{

}

void Enigma::Core::GenPairModule()
{
	Pair temp{};
	m_PairModule = temp;
}

void Enigma::Core::GenPairModule(s_Pairs pairs[13])
{
	Pair temp{ pairs };
	m_PairModule = temp;
}

Enigma::Core::~Core()
{
	
}
