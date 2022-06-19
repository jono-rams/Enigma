#include <Core/GenericInclude.h>

#include <string>

#ifndef ROTOR_H_
#define ROTOR_H_

namespace Enigma
{
	class Rotor
	{
		char m_Rotator[26]; // This contains the random assortment of characters

		Enigma_Short m_RotNum;
		Enigma_Short* m_Count;
		Enigma_Short m_SeedNum;

		void Rotate();
	public:
		Rotor();

		void SetRotor(Enigma_Char rotModuleNum, Enigma_Short seed, std::string ROTOR_FILE_PATH); // Constructor that takes in what slot the rotor is in and it's seed value

		void In(char& c) const; // Encryption logic for the letter entered by the user going TO the pair module
		void Out(char& c); // Encryption logic for the letter entered by the user coming FROM the pair module

		Enigma_Short GetSeed() const { return m_SeedNum; } // Function that returns the seed number
	};
}

#endif