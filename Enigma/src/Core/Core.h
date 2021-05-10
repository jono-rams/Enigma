#pragma once
#include "../Alphabet.h"
#include "../Pair/Pair.h"

namespace Enigma
{
	class Core
	{
		Pair* m_PairModule;
	public:
		Core();
		
		void GenPairModule();
		void GenPairModule(s_Pairs pairs[13]);
		Pair* GetPairModule() const { return m_PairModule; }

		~Core();
	};
}