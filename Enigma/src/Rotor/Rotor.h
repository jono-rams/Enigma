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
		int m_Count{ 0 };

		ushort_t m_SeedNo{};
		std::mt19937* m_Seed;

		void Rotate();
	public:
		Rotor() = delete;
		Rotor(bool FirstRotor, ushort_t seed);
		void In(char& c);
		void Out(char& c);

		ushort_t GetSeed() const { return m_SeedNo; }
	};
}

#endif