#pragma once
#ifndef GENERIC_INCLUDE_H_
#define GENERIC_INCLUDE_H_

#include <map>
#include <ostream>
#include <string>

namespace Enigma
{
	typedef unsigned short int Enigma_Short;
	typedef unsigned long long Enigma_64;
	typedef unsigned char Enigma_Char;

	const char alphabet[26]{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' }; // Constant array containing characters in the alphabet in alphabetical order
	const char alphabetUC[26]{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	enum class EnigmaError
	{
		NO_ERROR,
		E03_00A,
		E03_00B,
		E16_00,
		E16_10,
		E16_11,
		E18_00A,
		E18_00B,
		E18_01,
		E18_02,
		E18_03A,
		E18_03B,
		E18_10,
		E20_00,
		E20_10,
		E20_11
	};

	static std::map<EnigmaError, std::string> Errors
	{
		std::make_pair(EnigmaError::NO_ERROR, std::string("NO ERROR")),
		std::make_pair(EnigmaError::E03_00A, std::string("ERROR 03-00A: Invalid character")),
		std::make_pair(EnigmaError::E03_00B, std::string("ERROR 03-00B: Invalid character")),
		std::make_pair(EnigmaError::E16_00, std::string("ERROR 16-00 - Reflector could not be generated!")),
		std::make_pair(EnigmaError::E16_10, std::string("ERROR 16-10: Invalid character entered in pair!")),
		std::make_pair(EnigmaError::E16_11, std::string("ERROR 16-11: Duplicate letters in pairs!")),
		std::make_pair(EnigmaError::E18_00A, std::string("ERROR 18-00A: Invalid Rotor Number!")),
		std::make_pair(EnigmaError::E18_00B, std::string("ERROR 18-00B: Invalid Rotor Number!")),
		std::make_pair(EnigmaError::E18_01, std::string("ERROR 18-01: Rotor already in use in another sub-module!")),
		std::make_pair(EnigmaError::E18_02, std::string("ERROR 18-02: Trying to change Rotor Sub-Module that does NOT exist!")),
		std::make_pair(EnigmaError::E18_03A, std::string("ERROR 18-03A: Rotor 3 could not be generated!")),
		std::make_pair(EnigmaError::E18_03B, std::string("ERROR 18-03B: Rotor 1 could not be generated!")),
		std::make_pair(EnigmaError::E18_10, std::string("ERROR 18-10: Rotor File could not be opened!")),
		std::make_pair(EnigmaError::E20_00, std::string("ERROR 20-00: PlugBoard could not be generated!")),
		std::make_pair(EnigmaError::E20_10, std::string("ERROR 20-10: Max number of Connections made!")),
		std::make_pair(EnigmaError::E20_11, std::string("ERROR 20-11: Plug already connected!"))
	};

	static std::ostream& operator<< (std::ostream& out, const EnigmaError& e)
	{
		out << Errors[e];
		return out;
	}
}

#endif