#pragma once

#include <iostream>

#ifndef PAIR_H_
#define PAIR_H_

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
		int m_Connections[26]{ };
	public:
		Pair();
		Pair(s_Pairs pairs[13]);
		void SetPairs(s_Pairs pairs[13]);

		void PrintPairs() const;
	};
}
#endif