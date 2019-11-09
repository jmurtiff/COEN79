//See sequence1.h for documentation
//Name: Jordan Murtiff

#include "sequence1.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3
{
	sequence::sequence()
	{
		used = 0;
		current_index = 0;
	}

	void sequence::start()
	{
 	  	current_index = 0;
	}

	void sequence::end()
	{
	    current_index = used - 1;
	}

	void sequence::last()
	{
 	  	current_index = sequence::CAPACITY - 1;
	}

	sequence::value_type sequence::current() const
	{
 	   assert (is_item() == true);
 	   return data[current_index];
	}

	void sequence::advance()
	{
	    assert(is_item() == true);
	    if(current_index < used)
	    {
	        current_index++;
 	    }
	}

	void sequence::retreat()
	{
		if(current_index != 0)
		{
			current_index--;
		}
	}
	
	void sequence::insert(const value_type & entry)
	{
	    assert(used < sequence::CAPACITY);
		if(is_item() == true)
		{	
	    	for(int i = used; i > current_index; i--)
	   	 	{
	   	    	 data[i] = data[i-1];
	  	    }
			data[current_index] = entry;
		}
		else
		{
			data[current_index] = entry;
		}
	    used++;
	}

	void sequence::attach(const value_type & entry)
	{
   		assert(used < sequence::CAPACITY);
	 	if(is_item() == true)
		{
  		 	 for(int i = used; i > (current_index+1); i--)
  			 {
  	   		   data[i] = data[i-1];
  			 }
			 data[current_index+1] = entry;
		}
		else
		{
			data[current_index] = entry;
		}
	    current_index++;
	    used++;
	}
	
	void sequence::remove_current()
	{
	    assert(is_item() == true);
	    for( int i = current_index; i < (used-1); i++)
	    {
	        data[i] = data[i+1];
   		}
		used--;
	}

	void sequence::insert_front(const value_type &entry)
	{
		assert (used < sequence::CAPACITY);
		for(int i = used; i > 0; i--)
		{
			data[i] = data[i-1];
		}
		data[0] = entry;
		used++;
		current_index = 0;	
	}

	void sequence::attach_back(const value_type &entry)
	{
		assert(used < sequence::CAPACITY);
		data[used] = entry;
		current_index = used;
		used++;
	}

	void sequence::remove_front()
	{
		assert(is_item() == true);
		for(int i=0; i < (used-1); i++)
		{
			data[i] = data[i+1];
		}
		used--;
		current_index = 0;
	}
	
	sequence::size_type sequence::size() const
	{
		return used;
	}

	bool sequence::is_item() const
	{
  		if(current_index < used)
	    {
	        return true;
	    }
  	  	else
     	 {
   	        return false;
   		 }
	}

	sequence::value_type sequence::operator[](int index) const
	{
		assert(index < used);
		return data[index];
	}
	
	double sequence::mean() const
	{
		double sum = 0.0;
		double answer;
	
		for(int i = 0; i < used; i++)
		{
			sum += data[i];
		}
		answer = sum/(double) used;
		return answer;
	}


	double sequence::standardDeviation() const
	{
	    sequence::value_type sum = 0;
	    for(int i = 0; i < size(); i++)
   		{
 	       sum+= pow(data[i]-mean(),2);
    	}
    	return sqrt (sum);
	}

	sequence operator+(const sequence& lhs, const sequence& rhs)
	{
		assert((lhs.used + rhs.used) < sequence::CAPACITY);

		sequence temp;
		for(int i = 0; i <lhs.used; i++)
		{
			temp.data[i] = lhs.data[i];
			temp.used++;
		}
		for(int j =0; j <rhs.used; j++)
		{
			temp.data[(lhs.used) + j] = rhs.data[j];
			temp.used++;
		}
		return temp;
	}

	void sequence::operator+=(const sequence& rhs)
	{
		assert((this->size() + rhs.size()) <sequence::CAPACITY);
		std::copy(rhs.data,((rhs.data)+(rhs.used)),((this->data)+(this->used)));
		used+=rhs.used;
	}

    sequence::value_type summation(const sequence &s)
	{
		sequence::value_type sum = 0.0;
		for(int i=0; i < s.size(); i++)
		{
			sum+= s[i];
		}
		return sum;
	}

};


