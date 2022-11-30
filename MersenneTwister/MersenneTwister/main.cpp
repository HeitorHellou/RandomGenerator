#include <iostream>

#include "MersenneTwister.h"

int main()
{
	MersenneTwister rand{};

	for (int i{0}; i < 100; ++i)
		std::cout << rand.Random(10, 15) << "\n";

	return 0;
}