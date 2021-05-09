#pragma once

#include <stdlib.h>
#include <vector>

#ifndef PAIR_H_
#define PAIR_H_

namespace Enigma
{
	struct s_Pair
	{
		char pair1, pair2;
	};

	class Pair
	{
		char pairA[13]{ };
		char pairB[13]{ };
	public:
		void SetPairs(s_Pair pairs[13]);
	};
}
#endif