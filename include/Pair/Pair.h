#include <Core/GenericInclude.h>

#include <iostream>
#include <array>

#ifndef PAIR_H_
#define PAIR_H_

namespace Enigma
{
	struct s_Pairs // Struct containing the two characters in a pair
	{
		char pair1, pair2;

		friend std::ostream& operator<<(std::ostream& os, const s_Pairs& pair); // Overloaded ostream operator for s_Pairs struct
	};

	class Pair
	{
		std::array<s_Pairs, 13> m_Pairs;

		bool CheckDuplicates() const;
		bool CheckInvalidChar(s_Pairs pair) const;
	public:
		void SetPairs();
		void SetPairs(std::array<s_Pairs, 13> pairs);

		std::array<s_Pairs, 13> GetPairs() const { return m_Pairs; }

		void PairOut(char& letter) const;
	};
}

#endif
