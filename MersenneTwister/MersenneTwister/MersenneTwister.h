#pragma once

#include <iostream>
#include <array>

class MersenneTwister
{
private:
	int w{ 32 };
	int n{ 624 };
	int m{ 397 };
	int r{ 31 };
	unsigned int a{ 0x9908B0DF };
	int u{ 11 };
	unsigned int d{ 0xFFFFFFFF };
	int s{ 7 };
	unsigned int b{ 0x9D2C5680 };
	int t{ 15 };
	unsigned int c{ 0xEFC60000 };
	int l{ 18 };
	int f{ 1812433253 };

	std::array<unsigned long, 624> MT{};
	int index = this->n+1;
	unsigned long lower_mask{ 0x7FFFFFFF };
	unsigned long upper_mask{ 0x80000000 };
public:
	void Seed(int seed = 0);
	void Twist();
	int ExtractNumber();
	int Random(int a = 0, int b = 1);
	MersenneTwister(int seed = 0);
};

void MersenneTwister::Seed(int seed)
{
	MT[0] = seed;
	index = n;
	for (int i{ 1 }; i < n - 1; ++i)
	{
		long temp = (f * (MT[i - 1] ^ (MT[i - 1] >> (w - 2))) + i);
		MT[i] = temp & 0xFFFFFFFF;
	}
}

void MersenneTwister::Twist()
{
	for (int i{ 0 }; i < n - 1; ++i)
	{
		int x = (MT[i] & upper_mask) + ((MT[i + 1 % n]) & lower_mask);
		int xA = x >> 1;
		if (x % 2 != 0)
			xA = xA ^ a;
		MT[i] = MT[(i + m) % n] ^ xA;
	}
	index = 0;
}

int MersenneTwister::ExtractNumber()
{
	if (index >= n)
		Twist();

	int y = MT[index];
	y = y ^ ((y >> u) & d);
	y = y ^ ((y << s) & b);
	y = y ^ ((y << t) & c);
	y = y ^ ((y >> l));

	index+=1;
	return y & 0xFFFFFFFF;
}

int MersenneTwister::Random(int a, int b)
{
	double test = ExtractNumber();
	test /= 4294967296;
	double oldRange = (1 - 0);
	double newRange = (b - a);
	return static_cast<int>(((test) * newRange) / oldRange) + a;
}

MersenneTwister::MersenneTwister(int seed)
{
	Seed(seed);
}