#pragma once
#ifndef PAIR_H_
#define PAIR_H_

#include <iostream>
#include <array>

namespace Enigma
{
#ifndef ENIGMA_USE_STD_PAIR
	struct Enigma_Pairs // Struct containing the two characters in a pair
	{
		char first, second;

		friend std::ostream& operator<<(std::ostream& os, const Enigma_Pairs& pair); // Overloaded ostream operator for s_Pairs struct
	};
#endif

	class Reflector
	{
		bool CheckDuplicates() const;

#ifdef ENIGMA_USE_STD_PAIR
		std::array<std::pair<char, char>, 13> m_Pairs;
		bool CheckInvalidChar(std::pair<char, char> pair) const;
#else
		std::array<Enigma_Pairs, 13> m_Pairs;
		bool CheckInvalidChar(Enigma_Pairs pair) const;
#endif

	public:
		Reflector() = default;

		void SetPairs();

#ifdef ENIGMA_USE_STD_PAIR
		EnigmaError SetPairs(std::array<std::pair<char, char>, 13> pairs);
#else
		EnigmaError SetPairs(std::array<Enigma_Pairs, 13> pairs);
#endif

		
#ifdef ENIGMA_USE_STD_PAIR
		std::array<std::pair<char, char>, 13> GetPairs() const { return m_StdPairs; }
#else
		std::array<Enigma_Pairs, 13> GetPairs() const { return m_Pairs; }
#endif

		void ReflectorOut(char& letter) const;
	};
}

#endif
