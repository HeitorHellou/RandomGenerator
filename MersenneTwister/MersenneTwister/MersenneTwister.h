#pragma once

#include <iostream>
#include <array>
#include <chrono>
#include <random>

template<typename TypeField, int W, int N, int M, int R, unsigned int A, int U, unsigned int D, int S, unsigned int B, int T, unsigned int C, int L, int F>
class MersenneTwister
{
private:
	std::array<TypeField, N> _mt{};
	int _index = N + 1;
	unsigned long lower_mask{ 0x7FFFFFFF };
	unsigned long upper_mask{ 0x80000000 };
public:
	void Seed(TypeField seed)
	{
		_mt[0] = seed;
		_index = N;
		for (int i{ 1 }; i < N - 1; ++i)
		{
			long temp = (F * (_mt[i - 1] ^ (_mt[i - 1] >> (W - 2))) + i);
			_mt[i] = temp & 0xFFFFFFFF;
		}
	}

	void Twist()
	{
		for (int i{ 0 }; i < N - 1; ++i)
		{
			int x = (_mt[i] & upper_mask) + ((_mt[i + 1 % N]) & lower_mask);
			int xA = x >> 1;
			if (x % 2 != 0)
				xA = xA ^ A;
			_mt[i] = _mt[(i + M) % N] ^ xA;
		}
		_index = 0;
	}

	int ExtractNumber()
	{
		if (_index >= N)
			Twist();

		int y = _mt[_index];
		y = y ^ ((y >> U) & D);
		y = y ^ ((y << S) & B);
		y = y ^ ((y << T) & C);
		y = y ^ ((y >> L));

		_index += 1;
		return y & 0xFFFFFFFF;
	}

	MersenneTwister()
	{
		Seed(std::chrono::steady_clock::now().time_since_epoch().count());
	}

	int Random(int a = 0, int b = 1)
	{
		double rand = ExtractNumber();
		rand /= 4294967296;
		double oldRange = (1 - 0);
		double newRange = (b*2 - a);
		return static_cast<int>(((rand)*newRange) / oldRange) + a;
	}
};

typedef MersenneTwister<int, 32, 624, 397, 31, 0x9908B0DF, 11, 0xFFFFFFFF, 7, 0x9D2C5680, 15, 0xEFC60000, 18, 1812433253> MT;