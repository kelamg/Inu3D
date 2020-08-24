#pragma once

#include "Common.h"

class Random
{
public:
	static void SeedRand(int seed);
	static double Rand();
	static int RandInt(int modulo);
};

