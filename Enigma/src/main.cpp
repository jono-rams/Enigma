#include "Core/Core.h"
#include "Pair/Pair.h"
#include "Alphabet.h"


using namespace Enigma;
int main()
{
	Core machine{};
	machine.GenNewPairModule();
	machine.GetPairModule()->DEBUG_PrintPairs();
	return 0;
}