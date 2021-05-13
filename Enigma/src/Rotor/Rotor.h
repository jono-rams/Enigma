#pragma once
#include "../GenericCode.h"

#include <random>

#ifndef ROTOR_H_
#define ROTOR_H_

namespace Enigma
{
	class Rotor
	{
		char m_Rotator[26]{};

		bool m_FirstRotor{ false };
		bool m_ThirdRotor{ false };
		int m_Count{ 0 };

		ushort_t m_SeedNo{};

		void Rotate();
	public:
		Rotor() = delete;
		
		Rotor(bool FirstRotor, ushort_t seed, bool ThirdRotor = false);
		void In(char& c);
		void Out(char& c);

#if DEBUG_CODE_ACTIVE
		Rotor(ushort_t seed) : m_SeedNo(seed), m_Seed(new std::mt19937(seed)) {}
		void DEBUG_CacheSeedVals();
	private:
		std::mt19937* m_Seed;
#endif

		ushort_t GetSeed() const { return m_SeedNo; }
	};
}

#endif