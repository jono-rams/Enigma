#pragma once

#include <stdlib.h>
#include <vector>

#ifndef PAIR_H_
#define PAIR_H_

namespace Enigma
{
	struct s_Pairs
	{
		char pair1[13];
		char pair2[13];
	};

	class Pair
	{
		s_Pairs m_Pairs{ };
		int m_Connections[26]{ };
	public:
		Pair();
		Pair(s_Pairs pairs);
		void SetPairs(s_Pairs pairs);
	};
}
#endif