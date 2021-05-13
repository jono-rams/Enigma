#pragma once
#include "../GenericCode.h"

#include <random>

#ifndef ROTOR_H_
#define ROTOR_H_

namespace Enigma
{
	class Rotor
	{
		char *m_Rotator = new char[26];

		uchar_t *m_RotNum = nullptr;
		ushort_t *m_Count = new ushort_t{ 0 };

		ushort_t *m_SeedNo = nullptr;

		void Rotate();
	public:
		Rotor() = delete;
		~Rotor();
		
		Rotor(uchar_t rotModuleNum, ushort_t seed);
		void In(char& c) const;
		void Out(char& c);

		ushort_t GetSeed() const { return *m_SeedNo; }
	};
}

#endif