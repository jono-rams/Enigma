#pragma once
#include "GenericCode.h"
#include "../Pair/Pair.h"
#include "../Rotor/Rotor.h"

#include <string>

#ifndef CORE_H_
#define CORE_H_

namespace Enigma
{
	class Core
	{
		// Member variables for Pair module and Three Rotor modules as pointers
		Pair* m_PairModule;
		Rotor* m_RotorF;
		Rotor* m_RotorS;
		Rotor* m_RotorT;

		std::string* m_RotPath;

		char InternalEncrypt(char letter) const; // Function to encrypt character. This contains the actual encryption logic
	public:
		Core(); // Default constructor

		void GenNewPairModule(); // Generate Pair Module with default pairs
		void GenNewPairModule(s_Pairs pairs[13]); // Generate Pair Module with user set pairs

		void SetRotorDataPath(std::string path);
		void GenNewRotorsModules(ushort_t Rot1, ushort_t Rot2, ushort_t Rot3); // Generates Rotors using 3 different seed values
		void SwitchRotorModule(ushort_t RotModuleNo, ushort_t Rot); // Switches a specific rotor with a new one with a user determined seed

		void Encrypt(const std::string &word, std::string &output) const; // Encryption code for a string that takes a reference to a user string to write the output to
		std::string Encrypt(const std::string& word) const; // Encryption code for a string that returns a string
		~Core(); // Destructor
	};
}
#endif