#include "Core/Core.h"
#include "Pair/Pair.h"
#include "Alphabet.h"


using namespace Enigma;
int main()
{
	s_Pairs* pairs = new s_Pairs[13];

	for (int i = 0; i < 13; i++)
	{
		std::cout << "Enter a pair of letters or enter '00' to use default pairs: ";
		std::cin >> pairs[i].pair1 >> pairs[i].pair2;
		if (i == 0)
		{
			if (pairs[i].pair1 == '0')
			{
				delete[] pairs;
				pairs = nullptr;
				break;
			}
		}
	}

	Core machine{};

	if (pairs == nullptr)
		machine.GenNewPairModule();
	else
		machine.GenNewPairModule(pairs);
	delete[] pairs;

	if(machine.GetPairModule() != nullptr)
		machine.GetPairModule()->DEBUG_PrintPairs();

	return 0;
}