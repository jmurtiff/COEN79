//
//  counter.cpp
//  Lab #1
//
//  Created by jordan murtiff on 9/21/18.
//  Copyright © 2018 SCU. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//Function: This function counts the number of alphanumeric (letters and numbers) as well as 
//non-alphanumeric characters in any amount of given words that the user enters.
//
//Efficiency: O(n) where n is the number of characters in a string inputted by the user.
//
//Return type: An integer, in this case, the value of 0.
//
//Precondition: None
//
//Postcondition: The number of alphanumeric and non-alphanumeric characters are printed
//to the user.
int main()
{
	int alphaNumeric = 0;
	int nonAlphaNumeric = 0;

	string phrase;

	cout << "Please type in something: \n";

	getline (cin, phrase);

	int length = phrase.length();

	for(int i = 0; i < length; i++)
	{
		if (phrase.at(i) == ' ')
		{
			continue;
		}
		if(isalnum(phrase.at(i)) == 0)
		{
			nonAlphaNumeric++;
		}
		else
		{
			alphaNumeric++;
		}
	}
	cout << phrase << " has " << alphaNumeric << " alphanumeric characters and " << nonAlphaNumeric << " non-alphanumeric characters." << endl;
	return EXIT_SUCCESS;	
}
