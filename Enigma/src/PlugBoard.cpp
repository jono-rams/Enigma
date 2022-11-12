#include <PlugBoard/PlugBoard.h>

namespace Enigma
{
	PlugBoard::PlugBoard() : NumOfConnections(0)
	{
		for (size_t i = 0; i < 26; i++)
		{
			Plugs[i].letter = alphabet[i];
		}
	}

	EnigmaError PlugBoard::MakeConnection(Enigma_Char a, Enigma_Char b)
	{
		if(NumOfConnections >= 10)
			return EnigmaError::E20_10;

		int locA{}, locB{}, count{ 0 };

		for (int i = 0; i < 26; i++)
		{
			if (alphabet[i] == a)
			{
				locA = i;
				count++;
			}
			else if (alphabet[i] == b)
			{
				locB = i;
				count++;
			}
			else
				continue;

			if (count >= 2)
				break;
		}

		if (Plugs[locA].connected || Plugs[locB].connected)
			return EnigmaError::E20_11;

		Plugs[locA].connected = true;
		Plugs[locA].connectedLetter = &Plugs[locB];
		Plugs[locB].connected = true;
		Plugs[locB].connectedLetter = &Plugs[locA];
		++NumOfConnections;

		return EnigmaError::NO_ERROR;
	}

	void PlugBoard::RemoveConnection(Enigma_Char letter)
	{
		int loc{};
		for (int i = 0; i < 26; i++)
		{
			if (alphabet[i] == letter)
			{
				loc = i;
				break;
			}
		}

		if (!(Plugs[loc].connected))
			return;

		Plugs[loc].connectedLetter->connected = false;
		Plugs[loc].connectedLetter->connectedLetter = nullptr;
		Plugs[loc].connected = false;
		Plugs[loc].connectedLetter = nullptr;
	}

	void PlugBoard::PlugBoardOut(char& letter)
	{
		int loc{};
		for (int i = 0; i < 26; i++)
		{
			if (alphabet[i] == letter)
			{
				loc = i;
				break;
			}
		}

		if (!(Plugs[loc].connected))
			return;

		letter = Plugs[loc].connectedLetter->letter;
	}
}