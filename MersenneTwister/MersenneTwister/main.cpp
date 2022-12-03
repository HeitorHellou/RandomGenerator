#include <iostream>

#include "MersenneTwister.h"

int main()
{
	MT rand{};

	for (int i{0}; i < 50; ++i)
		std::cout << rand.Random(1, 10) << "\n";

	return 0;
}