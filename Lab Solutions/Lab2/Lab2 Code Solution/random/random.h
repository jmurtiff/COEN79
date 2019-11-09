/*
*  random.h
*  Lab2
*
*  Created by jordan murtiff on 9/28/18.
*  Copyright © 2018 SCU. All rights reserved.
*
*
* FILE: random.h
* CLASS PROVIDED: rand_gen (a class that generates pseudorandom numbers)
*
* CONSTRUCTOR for the rand_gen class:
*	rand_gen( );
*		Postcondition: The object has been initialized, and is ready to generate 
*		pseudorandom numbers.
*
* MODIFICATION MEMBER FUNCTIONS for the rand_gen class
*	int next()
*		Function: Calculates the pseudorandom number given a seed and then sets
*		the new seed to be the given pseudorandom number.
*		Efficiency: O(1)
*       Precondition: A rand_gen object exists.
*		Postcondition: The return value is the next random integer, and the return 
*		value is set as the new seed.
*		Return value: The new seed to generate the next psuedorandom number.
*	void set_seed(int newSeed);
*		Function: Sets the seed to be the given input newSeed for the psuedorandom 
*		number generator.
*		Efficiency: O(1)
*       Precondition: A rand_gen object exists.
*		Postcondition: The input newSeed is set to the seed of the generator.
*		Return value: None
*
* CONSTANT MEMBER FUNCTIONS for the rand_gen class
*	void print_info();
*		Function: Prints out all the available information regarding a rand_gen 
*		object (seed, multiplier, increment, and modulus values).
*		Efficiency: O(1)
*       Precondition: A rand_gen object exists.
*		Postcondition: The seed number, the multiplier, the increment, and the modulus
*		value is printed neatly to the screen.
*		Return value: None
*/

#ifndef random_h
#define random_h

namespace coen79_lab2
{
	class rand_gen
	{
		public:
			rand_gen(int seed, int multiplier, int increment, int modulus);
			int next();
			void set_seed(int newSeed);
			void print_info();
		private:
		int multiplier; 
		int seed;
		int increment;
		int modulus;
	};
}

#endif /* random_h */
