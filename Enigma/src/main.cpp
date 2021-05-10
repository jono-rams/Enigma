#include "Core/Core.h"
#include "Pair/Pair.h"
#include "Alphabet.h"


using namespace Enigma;
int main()
{
	Core machine{};
	machine.GenPairModule();
	machine.GetPairModule().PrintPairs();
	return 0;
}