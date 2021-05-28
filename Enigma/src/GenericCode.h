#pragma once

#ifndef GENERIC_CODE_H_
#define GENERIC_CODE_H_

typedef unsigned short int ushort_t;
typedef unsigned long long uint64_t;
typedef unsigned char uchar_t;

#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

namespace Enigma
{
	struct s_EnigmaTimer
	{
		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::duration<float> duration;

		s_EnigmaTimer()
		{
			start = std::chrono::high_resolution_clock::now();
		}

		~s_EnigmaTimer()
		{
			end = std::chrono::high_resolution_clock::now();
			duration = end - start;

			float ms = duration.count() * 1000.f;
			std::cout << "Timer took " << ms << "ms" << std::endl;
		}

	};

	class Log
	{
		Log() {}
		static uint64_t count;
		std::ofstream file;
		static std::string fileName;
		void WriteLogInternal(std::string& message)
		{
			file.open(fileName, std::ios::app);
			std::string temp = *(std::string*)count + " - " + message;
			file << message;
			file << std::endl;
			file.close();
		}

		static Log& Get()
		{
			static Log instance;
			return instance;
		}

	public:
		Log(const Log& obj) = delete;	

		static void SetFileName(std::string name)
		{
			Log::Get().fileName = name;
		}

		static void WriteLog(std::string message)
		{
			++count;
			Log::Get().WriteLogInternal(message);
		}
	};

	const char alphabet[26]{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' }; // Constant array containing characters in the alphabet in alphabetical order

	uint64_t Log::count = 0;
	std::string Log::fileName = "Logs/Enigma.log";
}

#endif
