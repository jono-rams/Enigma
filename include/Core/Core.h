#pragma once
#ifndef CORE_H_
#define CORE_H_

#include <Core/GenericInclude.h>
#include <Reflector/Reflector.h>
#include <Rotor/Rotor.h>
#include <PlugBoard/PlugBoard.h>

#include <string>

namespace Enigma
{
	class Core
	{
		Reflector m_Reflector;
		Rotor m_RotorF, m_RotorS, m_RotorT;
		PlugBoard m_PlugBoard;

		std::string m_RotPath;

		EnigmaError InternalEncrypt(char& letter);
		bool CheckIfValidLetter(char letter);
		bool ConvertToLowerCaseIfUpper(char& letter);
		void ConvertToUpperCase(char& letter);
	public:
		Core();
		Core(Core& obj);
		Core& operator=(const Core& obj);
		Core(Core&& obj) noexcept;
		Core& operator=(Core&& obj) noexcept;
		~Core() = default;

		void GenNewReflector();
#ifdef ENIGMA_USE_STD_PAIR
		EnigmaError GenNewReflector(std::array<std::pair<char, char>, 13> pairs);
#else
		EnigmaError GenNewReflector(std::array<Enigma_Pairs, 13> pairs);
#endif

		inline void SetRotorDataPath(std::string path) { m_RotPath = path; }
		inline void SetNumberOfRotorModules(Enigma_64 NumberOfModules) const { Rotor::SetNumberOfModules(NumberOfModules); }
		EnigmaError GenNewRotorsModules(Enigma_64 Rot1, Enigma_64 Rot2, Enigma_64 Rot3);
		EnigmaError SwitchRotorModule(Enigma_Short RotModuleNo, Enigma_64 Rot);
		void OffsetRotor(uint64_t offset);

		inline void SetMaxNumberOfPlugBoardConnections(Enigma_Short NewValue) const { PlugBoard::SetMaxNumberOfConnections(NewValue); }
		EnigmaError MakePlugBoardConnection(Enigma_Char a, Enigma_Char b);
		void RemovePlugBoardConnection(Enigma_Char letter);

		std::string Encrypt(const std::string& word);
		void Encrypt(const std::string& word, std::string& output);

		char* Encrypt(const char* word);
	};
}

#endif
