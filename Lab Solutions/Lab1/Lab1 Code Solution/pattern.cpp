//
//  pattern.cpp
//  Lab 1
//
//  Created by jordan murtiff on 9/21/18.
//  Copyright © 2018 SCU. All rights reserved.
//


#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Function: This function prints out a certain pattern of strings using the "setw" function
//to change the number of spaces between each string that is used in the pattern. Each line
//has its own unique pattern of spaces for the strings used in the program.
//
//Efficiency: O(1) since the "for" loop is limited in its number of operations and is not 
//dependent on anything the user gives.
//
//Return type: An integer, in this case, the value of 0.
//
//Precondition: None
//
//Postcondition: The specificed pattern relating the strings "012345678" and "9876543210"
//is printed to the screen.
int main()
{
    string forward = "0123456789";
    string backward = "9876543210";

	cout << forward << endl;

	for(int i = 11; i < 20; i=i+2)
		{
			cout << setw(i);
			cout << backward; 
			if(i != 19)
			{
				cout << setw(i+4);
				cout << forward << endl;
			}
		}
	cout << endl; 
	return(EXIT_SUCCESS);
}
