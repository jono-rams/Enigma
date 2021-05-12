#pragma once
#include "../GenericCode.h"
#include "../Pair/Pair.h"

#ifndef CORE_H_
#define CORE_H_

namespace Enigma
{
	class Core
	{
		Pair* m_PairModule;
	public:
		Core();
		
		void GenNewPairModule();
		void GenNewPairModule(s_Pairs pairs[13]);
		Pair* GetPairModule() const { return m_PairModule; }

		char Encrypt(char letter) const;
		~Core();
	};
}
#endif