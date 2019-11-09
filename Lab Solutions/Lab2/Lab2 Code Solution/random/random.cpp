// See random.h for documentation of all functions.

#include "random.h"
#include <iostream>

using namespace std;

namespace coen79_lab2
{
	rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus)
	{
		this->seed = seed;
		this->multiplier = multiplier;
		this->increment = increment;
		this->modulus = modulus;
	}

	void rand_gen::set_seed(int newSeed)
	{
		seed = newSeed;
	}

	int rand_gen::next()
	{
		seed = (multiplier * seed + increment) % modulus;
		return seed;
	}

	void rand_gen::print_info()
	{
		cout << "Seed: " << seed << endl;
		cout << "Multiplier: " << multiplier << endl;
		cout << "Increment: " << increment << endl;
		cout << "Modulus: " << modulus << endl;
	}
}
