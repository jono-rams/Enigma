#pragma once

#include <iostream>

#ifndef PAIR_H_
#define PAIR_H_

typedef unsigned short int ushort_t;

namespace Enigma
{
	struct s_Pairs
	{
		char pair1;
		char pair2;

		friend std::ostream& operator<<(std::ostream& os, const s_Pairs& pair);
	};

	class Pair
	{
		s_Pairs m_Pairs[13];
		ushort_t m_Connections[26]{ };

		bool CheckDuplicates(s_Pairs pairs[13]) const;
	public:
		Pair();
		Pair(s_Pairs pairs[13]);

		void DEBUG_PrintPairs() const;
	};
}
#endif