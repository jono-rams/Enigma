#pragma once
#ifndef PLUGBOARD_H_
#define PLUGBOARD_H_

#include <Core/GenericInclude.h>

#include <array>

namespace Enigma
{
	struct Plug
	{
		Enigma_Char letter;
		bool connected;
		Plug* connectedLetter;

		Plug() : letter('0'), connected(false), connectedLetter(nullptr) {}
		~Plug() = default;
	};

	class PlugBoard
	{
		std::array<Plug, 26> Plugs;
		int NumOfConnections;

		inline static Enigma_Short MaxNumberOfConnections = 10;

	public:
		PlugBoard();
		~PlugBoard() = default;

		static void SetMaxNumberOfConnections(Enigma_Short NewValue);

		EnigmaError MakeConnection(Enigma_Char a, Enigma_Char b);
		void RemoveConnection(Enigma_Char letter);
		void PlugBoardOut(char& letter);
	};
}

#endif