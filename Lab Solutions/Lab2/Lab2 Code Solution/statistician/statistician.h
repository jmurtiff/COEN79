/*
* FILE: statistician.h
* CLASS PROVIDED: statistician (a class that can take in numbers and form
* statistics about the set of numbers given)
*
* CONSTRUCTOR for the statistician class
* 	statistician()
*		Function: To construct/create objects of the statistician class.
*		Efficiency: O(1)
*       Precondition: None
* 		Postcondition: A statistician with no values has been initialized.
* 		The length and sum are set to 0, and the minimum and maximum 
* 		values will be initialized after the first number is added.
* 		The statistician object is ready to accept values.
*		Return Value: None
*
* MODIFICATION MEMBER FUNCTIONS for the statistician class
* 	void next (double input)
*		Function: To add a new double into a statistician object and
*		update the object's length, sum, mean, and possibly maximum
*		and minimum (if the given value is less than the current minimum
*		or greater than the current maximum).
*		Efficiency: O(1)
*       Precondition: None
*  		Postcondition: The input is added to a statistician object.
*  		If the length of the object is 0, the input is initialized as
*  		the object's minimum and maximum value. Otherwise, the minimum
*  		and maximum values are updated if input is smaller or greater
*  		than either the minimum or maximum. No matter the length of the
*  		object, the sum of the statistician object is changed by the
*  		value of input.
*		Return Value: None
*	void reset()
*		Function: To reset a statistician object by changing its 
*		length and sum values to 0.
*		Efficiency: O(1)
*       Precondition: None
*		Postcondition: The statistician object is cleared. Both the 
*		sum and length is reset to 0. Once a new number is added to
*		the statistician object (through the next() function) the mean,
*		minimum, and maximum are set accordingly to the new number added.
*		Return Value: None
*	
* CONSTANT MEMBER FUNCTIONS for the statistician class
*	int length() const
*		Function: To get the length of a statistician object. The length
*		is constant because we are only getting the value, we are not changing
*		its value.
*		Efficiency: O(1)
*		Precondition: None
*		Postcondition: The return value is the length of the sequence
*		that has been given to the statistician (i.e., the number of 
*		times that the next(input) function has been called).
*		Return Value: The length of a statistician object as an int.
*	double sum() const
*		Function: To get the sum of a statistician object. The sum
*		is constant because we are only getting the value, we are not 
*		changing its value.
*		Efficiency: O(1)
*		Precondition: None
*		Postcondition: The return value is the sum of all the numbers
*		in the statistician's sequence.
*		Return Value: The sum of a statistician object as a double.
*	double mean() const
*		Function: To get the mean of a statistician object. The mean
*		is constant because we are only getting the value, we are not 
*		changing its value.
*		Efficiency: O(1)
*		Precondition: The length of the statistician object is > 0.
*		So length() > 0.
*		Postcondition: The return value is the arithmetic mean of 
*		all the numbers in a statistician object, dividing the total
*		sum of the sequence by the length of the sequence
*		sum()/length().
*		Return Value: The mean of a statistician object as a double.
*	double minimum() const
*		Function: To get the minimum number of a statistician object. 
*		The minimum	is constant because we are only getting the value, 
*		we are not changing its value.
*		Efficiency: O(1)
*       Precondition: The length of the statistician object is > 0.
*		So length() > 0.
*		Postcondition: The return value is the smallest number in the
*       statistician's sequence.
*		Return Value: The minimum number of a statistician object as a double.
*   double maximum() const
*		Function: To get the maximum number of a statistician object. 
*		The maximum is constant because we are only getting the value, 
*		we are not changing its value.
*		Efficiency: O(1)
*       Precondition: The length of the statistician object is > 0.
*		So length() > 0.
*       Postcondition: The return value is the largest number in the
*       statistician's sequence.
*		Return Value: The maximum number of a statistician object as a double.
*       
* NON-MEMBER functions for the statistician class:
*   statistician operator +(const statistician& s1, const statistician& s2)
*		Function: To add two statistician objects together into one statistician 
*		object. This function overloads the normal addition operator.
*		Efficiency: O(1)
*       Precondition: Two statistician objects must exist.
*     	Postcondition: The statistician that is returned contains all the
*     	numbers of the sequences of s1 and s2.
*		Return Value: A statistician object that is a combination of s1 and s2.
*   statistician operator *(double scale, const statistician& s)
*		Function: To multiply each private member variable of a statistician
*		object by a given scale. This function overloads the normal 
*		multiplication operator.
*		Efficiency: O(1)
*       Precondition: Two statistician objects must exist.
*     	Postcondition: The statistician that is returned contains the same
*     	numbers that s does, but each number has been multiplied by the
*     	scale number.
*		Return Value: The statistician object s that has each private member 
*		variable multiplied by the given scale.
*   bool operator ==(const statistician& s1, const statistician& s2)
*		Function: To compare two statistician objects together to see whether
*		or not the two objects are the same or not. This function overloads the
*		normal comparison operator.
*		Efficiency: O(1)
*       Precondition: Two statistician objects must exist.
*     	Postcondition: The return value is true if s1 and s2 have the zero
*     	length. Also, if the length is greater than zero, then s1 and s2 must
*     	have the same length, the same  mean, the same minimum, 
*     	the same maximum, and the same sum.
*		Return Value: True, if both s1 and s2 are the same, or false, if s1 and
*		s2 are not the same.
*
* VALUE SEMANTICS for the statistician class:
* Assignments and the copy constructor may be used with statistician objects.
*/ 	

#ifndef statistician_h
#define statistician_h

namespace coen79_lab2
{
    class statistician
    {
    public:
        statistician();
        void next(double input);
        int length()const;
        double sum()const;
        double mean()const;
        double minimum()const;
        double maximum()const;
        void reset();
        friend statistician operator +(const statistician s1, const statistician& s2);
        friend statistician operator *(double scale, const statistician & s);
        friend bool operator ==(const statistician& s1, const statistician& s2);
    private:
        double stat_length;
        double stat_sum;
        double stat_mean;
        double stat_minimum;
        double stat_maximum;
    };
}


#endif /* statistician_h */
