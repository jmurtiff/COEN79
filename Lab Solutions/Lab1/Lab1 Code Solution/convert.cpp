//
//  convert.cpp
//  Lab 1
//
//  Created by jordan murtiff on 9/21/18.
//  Copyright © 2018 SCU. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

//Function: This function goes through a text file given as a command line argument and with each 
//word it removes all the punctuation within the word. Then, the program checks to see if the word is 
//greater than or equal to 10 characters. Once a word has been found with that number of characters,
//all its letters are made capital. Finally, the word is printed out to the screen and the program 
//continues searching through the text file until another word is found that is greater than or equal to 
//10 characters and the process repeats itself. Once the entire file has been read, the program ends.
//
//Efficiency: O(n) where n is the number of words in a given text file.
//
//Return type: An integer, in this case, the value of 0.
//
//Precondition: A text file must exist that can be read through. With no text file, the program
//cannot be run.
//
//Postcondition: The words in a given file that are greater than or equal to 10 characters 
//will be printed out to the screen with each word being changed to all caps and having all
//puncuation and spaces removed from the words. Each word printed out will have its own line.
int main(int argc, char *argv[])
{
	assert(argc > 1);
	
	string phrase;
	ifstream file;
	file.open(argv[1]);

	while (file >> phrase)
	{
		for(int i = 0; i < phrase.length(); i++)
		{
			if(isalnum(phrase.at(i)) == 0)
			{
				phrase.erase(i,1);
			}
		}
		if(phrase.length() < 10)
		{
			continue;
		}
		for(int i = 0; i < phrase.length(); i++)
		{
			phrase.at(i) = toupper(phrase.at(i));
		}
		cout << phrase << endl;
	}
	file.close();
	return(EXIT_SUCCESS);
}
