#include "Core/Core.h"

#include <vector>
#include <string>

// This is an example of how to use the code, this file contains none of the code logic.

using namespace Enigma;

int main()
{
	s_Pairs* pairs = new s_Pairs[13];

	for (ushort_t i = 0; i < 13; i++)
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
	{
		try
		{
			machine.GenNewPairModule(pairs);
		}
		catch (std::logic_error err)
		{
			std::cout << err.what() << std::endl;
		}
	}
	delete[] pairs;

	ushort_t r1, r2, r3;
	std::cout << "Enter 3 of 5 rotors in any order: ";
	std::cin >> r1 >> r2 >> r3;
	
	try 
	{
		machine.GenNewRotorsModules(r1, r2, r3);
	}
	catch (std::logic_error err)
	{
		std::cout << err.what() << std::endl;
	}

#if DEBUG_CODE_ACTIVE	
		if (machine.GetPairModule() != nullptr)
			machine.GetPairModule()->DEBUG_PrintPairs();
#endif

	std::string* inp = new std::string;
	std::string out{};
	std::cout << "Input the letters you would like to encrypt/decrypt: ";
	std::cin >> *inp;
	
	try
	{
		machine.Encrypt(*inp, out);
		delete inp;
		inp = nullptr;
	}
	catch (std::logic_error err)
	{
		std::cout << err.what() << std::endl;
	}
	std::cout << out << std::endl;

	return 0;
}