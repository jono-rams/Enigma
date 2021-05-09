#include "Pair.h"

void Enigma::Pair::SetPairs(s_Pair pairs[13])
{
	for (int i = 0; i < 13; i++)
	{
		pairA[i] = pairs[i].pair1;
		pairB[i] = pairs[i].pair2;
	}
}
