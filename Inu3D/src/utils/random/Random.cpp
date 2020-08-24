#include "Random.h"

double Random::Rand()
{
	int x = rand();
	double f = (double)x / RAND_MAX;
	return f;
}

int Random::RandInt(int modulo)
{
	int x = rand() % modulo;
	return x;
}

void Random::SeedRand(int seed)
{
	srand((unsigned int)seed);
}
