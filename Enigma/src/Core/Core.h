#pragma once
#include "../GenericCode.h"
#include "../Pair/Pair.h"
#include "../Rotor/Rotor.h"

#include <string>
#include <fstream>

#ifndef CORE_H_
#define CORE_H_

#define ENIGMA_LOGGING_ENABLED

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
		Core(Core &obj); // Overloaded Copy Constructor
		Core & operator=(const Core &obj); // Overloaded Copy Assignment
		Core(Core&& obj) noexcept; // Overloaded Move Constructor
		Core & operator=(Core&& obj) noexcept;// Overloaded Move Assignment

		void GenNewPairModule(); // Generate Pair Module with default pairs
		void GenNewPairModule(s_Pairs pairs[13]); // Generate Pair Module with user set pairs

		void SetRotorDataPath(std::string path);
		void GenNewRotorsModules(ushort_t Rot1, ushort_t Rot2, ushort_t Rot3); // Generates Rotors using 3 different seed values
		void SwitchRotorModule(ushort_t RotModuleNo, ushort_t Rot); // Switches a specific rotor with a new one with a user determined seed
		void OffsetRotor(uint64_t offset);

		// Encryption code where input is a string
		void Encrypt(const std::string &word, std::string &output) const; 
		void Encrypt(const std::string &word, std::fstream &output) const;
		void Encrypt(const std::string &word, char* output) const;
		std::string Encrypt(const std::string &word) const;
		
		// Encryption code where input is a fstream object
		void Encrypt(std::fstream &word, std::string &output) const;
		void Encrypt(std::fstream &word, std::fstream &output) const;
		void Encrypt(std::fstream &word, char* output) const;
		std::string Encrypt(std::fstream &word) const;

		void Encrypt(const char* word, std::string &output) const;
		void Encrypt(const char* word, std::fstream &output) const;
		void Encrypt(const char* word, char* output) const;
		std::string Encrypt(const char* word) const;

		~Core(); // Destructor
	};
}
#endif