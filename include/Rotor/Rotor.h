#pragma once
#include "../Core/GenericCode.h"

#include <string>

#ifndef ROTOR_H_
#define ROTOR_H_

namespace Enigma
{
	class Rotor
	{
		char *m_Rotator = new char[26]; // Pointer with memory allocated for 26 characters, this contains the random assortment of characters

		uchar_t *m_RotNum = nullptr; // Pointer with memory allocated for an unsigned char that determines which slot the rotor is located in (This determines when the rotor has to rotate)
		ushort_t *m_Count = new ushort_t{ 0 }; // Pointer with memory allocated for an unsigned short that is used as a counter to determine when the rotor has to rotate

		ushort_t *m_SeedNo = nullptr; // Pointer with memory allocated for an unsigned short that stores the seed number

		void Rotate();
	public:
		Rotor() = delete; // Deletes the default constructor so that it can't be used
		~Rotor(); // Deconstructor
		
		Rotor(uchar_t rotModuleNum, ushort_t seed, std::string ROTOR_FILE_PATH); // Constructor that takes in what slot the rotor is in and it's seed value
		void In(char& c) const; // Encryption logic for the letter entered by the user going TO the pair module
		void Out(char& c); // Encryption logic for the letter entered by the user coming FROM the pair module

		ushort_t GetSeed() const { return *m_SeedNo; } // Function that returns the seed number
	};
}

#endif