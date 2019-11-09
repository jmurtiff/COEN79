//  Documentation is in keyed_bag.h
//
//  INVARIENTS for the keyed_bag class:
//  1. The number of items in the keyed_bag is in the member variable used.
//  2. For an empty keyed bag, we do not care what is stored in any of data, 
//  for a non-empty keyed bag, the items in the keyed bag are stored in data[0]
//  through data[used-1], and we don't care what's in the rest of the data.
//  3. For an empty keyed bag, we do not care what is stored in any of keys, 
//  for a non-empty keyed bag, the keys are stored in keys[0] through 
//  keyed[used-1], and we don't care what's in the rest of the keys.
//  4. In either case, the number of items in the keyed bag must not exceed
//  capacity in either the data or keys array. The used variable should not
//  exceed max capacity.

#include "keyed_bag.h"
#include <cassert>
#include <algorithm>
using namespace std;
using namespace coen79_lab4;


namespace coen79_lab4
{
	keyed_bag::keyed_bag()
	{
		used = 0;
	}
	
    void keyed_bag::erase()
    {
        for(int i = 0; i < used; i++)
        {
            data[i] = '0';
			keys[i] = '\0';
        }
		used = 0;
    }
    
    bool keyed_bag::erase(const keyed_bag::key_type& key)
    {
        if(has_key(key) == false)
        {
            return false;
        }
		else
		{
			int index;
			for (int i = 0; i < used; i++)
			{
				if(key == keys[i])
				{
					index = i;
					break;
				}
			}
			for(int j = index; j < used; j++)
			{
				data[j] = data[j+1];
				keys[j] = keys[j+1];
			}
			used--;
			return true;
		}
    }
    
    void keyed_bag::insert(const value_type& entry, const key_type& key)
    {
		assert(size() < keyed_bag::CAPACITY);
		assert(has_key(key) == false);
        data[used] = entry;
		keys[used] = key;
		used++;
    }
    
    void keyed_bag::operator +=(const keyed_bag& addend)
    {
		assert(size() + addend.size() <= keyed_bag::CAPACITY);
		assert(hasDuplicateKey(addend) == false);
		int j = 0;
		for(int i = used; i < (used + addend.used); i++)
		{
			data[i] = addend.data[j];
			keys[i] = addend.keys[j];
			j++;
		}
		used += addend.used;
    }
    
    bool keyed_bag::has_key(const key_type& key) const
    {
        for(int i = 0; i < used; i++)
		{
			if(key == keys[i])
			{
				return true;
			}
		}
		return false;
    }
    
    keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const
    {
       assert(has_key(key) == true);
	   int index;
	   for(int i = 0; i < used; i++)
	   {
	   		if(key == keys[i])
			{
				index = i;
				break;
			}
	   }
	   return data[index];
    }
    
    keyed_bag::size_type keyed_bag::size( ) const
    {
        return used;
    }
    
    keyed_bag::size_type keyed_bag::count(const keyed_bag::value_type& target) const
    {
        size_type count = 0;
		for(int i = 0; i < used; i++)
		{
			if(data[i] == target)
			{
				count++;
			}
		}
		return count;
    }
    
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const
    {
        if((used == 0) || (otherBag.used == 0))
		{
			return false;
		}
		key_type temp;
		int j;
		int i;
		for(i = 0; i < used; i++)
		{
			temp = keys[i];
			for(j = 0; j < otherBag.used; j++)
			{
				if(temp == otherBag.keys[j])
				{
					return true;
				}
			}
		}
		return false;
    }
    
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2)
    {
        assert((b1.size() + b2.size()) <= keyed_bag::CAPACITY);
		assert(b1.hasDuplicateKey(b2) == false);
		keyed_bag temp;
		temp += b1;
		temp += b2;
		return temp;
    }
       
};
