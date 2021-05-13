#pragma once
#include "../GenericCode.h"
#include "../Pair/Pair.h"
#include "../Rotor/Rotor.h"

#include <string>

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

		char InternalEncrypt(char letter) const;
	public:
		Core();
		
		void GenNewPairModule();
		void GenNewPairModule(s_Pairs pairs[13]);

#ifdef DEBUG_CODE_ACTIVE
		const Pair* GetPairModule() const { return m_PairModule; }
#endif

		void GenNewRotorsModules(ushort_t Rot1, ushort_t Rot2, ushort_t Rot3);
		void SwitchRotorModule(ushort_t RotModuleNo, ushort_t Rot);

		void Encrypt(const std::string &word, std::string &output) const;
		std::string Encrypt(const std::string& word) const;
		~Core();
	};
}
#endif