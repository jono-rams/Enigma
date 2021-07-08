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
#include "Log/Log.h"

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

	

	const char alphabet[26]{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' }; // Constant array containing characters in the alphabet in alphabetical order

	
}

#endif
