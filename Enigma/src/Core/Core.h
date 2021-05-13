#pragma once
#include "../GenericCode.h"
#include "../Pair/Pair.h"
#include "../Rotor/Rotor.h"

#ifndef CORE_H_
#define CORE_H_

namespace Enigma
{
	class Core
	{
		Pair* m_PairModule;
		Rotor* m_RotorF;
		Rotor* m_RotorS;
		Rotor* m_RotorT;

		ushort_t seeds[3]{};
	public:
		Core();
		
		void GenNewPairModule();
		void GenNewPairModule(s_Pairs pairs[13]);
		const Pair* GetPairModule() const { return m_PairModule; }

		void GenNewRotorsModules(ushort_t Rot1, ushort_t Rot2, ushort_t Rot3);
		void SwitchRotorModule(ushort_t RotModuleNo, ushort_t Rot);

		char Encrypt(char letter) const;
		~Core();
	};
}
#endif