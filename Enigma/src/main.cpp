#include "Core/Core.h"
#include "Pair/Pair.h"
#include "Rotor/Rotor.h"
#include "GenericCode.h"

#include <vector>
#include <string>

using namespace Enigma;

bool CheckInvalidChar(s_Pairs pair)
{
	ushort_t count{ 0 };
	for (ushort_t i = 0; i < 26; i++)
	{
		if (pair.pair1 == alphabet[i])
			count++;
		if (pair.pair2 == alphabet[i])
			count++;

		if (count > 1)
			return false;
	}
	return true;
}

int main()
{
#if DEBUG_CODE_ACTIVE
	Rotor rot(1);
	rot.DEBUG_CacheSeedVals();

	return 0;
#endif

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
		if (CheckInvalidChar(pairs[i]))
		{
			std::cout << "Invalid character entered! Switching to default pairs!\n";
			delete[] pairs;
			pairs = nullptr;
			break;
		}
	}

	Core machine{};

	if (pairs == nullptr)
		machine.GenNewPairModule();
	else
		machine.GenNewPairModule(pairs);
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

	std::vector<char> inp;
	std::string* temp = new std::string;	
	std::cout << "Input the letters you would like to encrypt/decrypt: ";
	std::cin >> *temp;
	std::copy((*temp).begin(), (*temp).end(), std::back_inserter(inp));
	delete temp;

	char* out = new char;
	for (uint64_t i = 0; i < inp.size(); i++)
	{
		try
		{
			*out = machine.Encrypt(inp[i]);
		}
		catch (std::logic_error err)
		{
			std::cout << err.what() << std::endl;
			delete out;
			out = nullptr;
			break;
		}
		std::cout << *out;
	}
	delete out;
	std::cout << std::endl;

	return 0;
}