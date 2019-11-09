// See statistican.h for documentation of all functions.

#include "statistician.h"
#include <cassert>
#include <iostream>

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{
    statistician::statistician()
    {
        stat_length = 0;
        stat_sum = 0.0;
    }
    
    void statistician::next(double input)
    {
		if(stat_length == 0)
		{

			stat_maximum = input;
			stat_minimum = input;
		}
		else
		{
			if (stat_maximum < input)
				{
					stat_maximum = input;
				}
        	else if(stat_minimum > input)
				{
            		stat_minimum = input;
				}
        }
        stat_length++;
        stat_sum = stat_sum + input;
        stat_mean = stat_sum/stat_length;
    }
    
    int statistician::length() const
    {
        return stat_length;
    }

    double statistician::sum() const
    {
        return stat_sum;
    }

    double statistician::mean() const
    {
        assert(stat_length > 0);
        return stat_mean;
    }

    double statistician::maximum() const
    {
        assert(stat_length > 0);
        return stat_maximum;
    }

    double statistician::minimum() const
    {
        assert(stat_length > 0);
        return stat_minimum;
    }
    
    void statistician::reset()
    {
        stat_sum = 0.0;
        stat_length = 0;
    }
    
    statistician operator +(const statistician s1, const statistician& s2)
    {
        statistician temp;
        temp.stat_length = s1.stat_length + s2.stat_length;
        temp.stat_sum = s1.stat_sum + s2.stat_sum;
        temp.stat_mean = temp.stat_sum/temp.stat_length;
        if (s1.stat_maximum > s2.stat_maximum)
        {
            temp.stat_maximum = s1.stat_maximum;
        }
        else
        {
            temp.stat_maximum = s2.stat_maximum;
        }
        if (s1.stat_minimum < s2.stat_minimum)
        {
            temp.stat_minimum = s1.stat_minimum;
        }
        else
        {
            temp.stat_minimum = s2.stat_minimum;
        }
        return temp;
    }

    statistician operator *(double scale, const statistician & s)
    {
        statistician temp;
		temp.stat_length = s.stat_length;
        temp.stat_sum = s.stat_sum * scale;
		temp.stat_mean = temp.stat_sum/temp.stat_length;
        temp.stat_maximum = s.stat_minimum * scale;
        temp.stat_minimum = s.stat_maximum * scale;
		if(temp.stat_maximum < temp.stat_minimum)
		{
			int max = temp.stat_maximum;
			temp.stat_maximum = temp.stat_minimum;
			temp.stat_minimum = max;
		}
        return temp;
    }

    bool operator ==(const statistician& s1, const statistician& s2)
    {
        if(s1.stat_length == 0 && s2.stat_length == 0)
        {
            return true;
        }
        return(s1.stat_length == s2.stat_length && s1.stat_sum == s2.stat_sum && s1.stat_mean == s2.stat_mean && s1.stat_minimum == s2.stat_minimum && s1.stat_maximum == s2.stat_maximum);
    }
    
}
