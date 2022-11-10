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
		bool connected = false;
		Plug* connectedLetter;
	};

	class PlugBoard
	{
		std::array<Plug, 26> Plugs;
		int NumOfConnections;

	public:
		PlugBoard();
		~PlugBoard() = default;

		EnigmaError MakeConnection(Enigma_Char a, Enigma_Char b);
		void PlugBoardOut(char& letter);

		// TODO: Function to remove connection
		void RemoveConnection(Enigma_Char letter);
	};
}

#endif