//See mystring.h for documentation.
// 
//	INVARIENTS for the string class: 
//	1. The number of characters used in the string is stored in the member variable
//	current_length. current_length is updated to the string length whenever new
//	characters are added to the string or taken out of the string.
//	2. The string is stored as a partially filled array of characters.
//	3. The array of characters is a dynamic array that is pointed to by the member
//	variable characters.
//	4. The characters of the string are stored in the first current_length characters
//	in the array followed by the terminating NULL character. We do not care about what
//	is inside the array past the terminating NULL character.
//	5. The size of the dynamic array is stored by the member variable allocated.  

#include <iostream>
#include <cassert>
#include <cstring>
#include "mystring.h"
using namespace coen79_lab5;

namespace coen79_lab5
{
    string::string(const char str[ ])
    {
        int length = strlen(str);
		assert(str[length] == '\0');
		allocated = 0;
		characters = NULL;
		current_length = 0;
		reserve(length);
		strncpy(characters, str, length+1);
		allocated = length + 1;
		current_length = length;
    }

    string::string(char c)
    {
		characters = NULL;
		allocated = 0;
		current_length = 0;
		reserve(1);
		characters[0] = c;
		characters[1] = '\0';
		current_length = 1;
    }

    string::string(const string& source)
    {
	   characters = NULL;
	   reserve(source.current_length);
	   strncpy(characters, source.characters, source.current_length +1);
	   current_length = source.current_length;
    }

    string::~string( )
    {
        delete[] characters;
    }
    
    void string::operator +=(const string& addend)
    {
        reserve(current_length+addend.current_length);
		strncat(characters, addend.characters, addend.current_length+1);
		current_length = current_length + addend.current_length;
    }

    void string::operator +=(const char addend[ ])
    {
        int length = strlen(addend);
		assert(addend[length] == '\0');
		reserve(current_length + length);
		strncat(characters, addend, length + 1);
		current_length = length + current_length;
    }

    void string::operator +=(char addend)
    {
        reserve(current_length + 1);
		strncat(characters, &addend, 1);
		current_length++;
    }

    void string::reserve(size_t n)
    {
        if((n+1) > allocated)
		{
			char *temporary = new char[n+1];
			if(characters != NULL)
			{
				strncpy(temporary, characters, current_length+1);
				delete [] characters;
			}
			characters = temporary;
			allocated = sizeof(*characters);
		}
    }

    string& string::operator =(const string& source)
    {
        reserve(source.allocated-1);
		current_length = source.length();
		strncpy(characters, source.characters, source.current_length+1);
		return *this;
    }

    void string::insert(const string& source, unsigned int position)
    {
        assert(position <= length());
		reserve(current_length + source.current_length);
		strncpy(characters+(position)+source.current_length,characters+position,length()-position);
		strncpy(characters+(position),source.characters,source.current_length);
		current_length += source.length();
    }

    void string::dlt(unsigned int position, unsigned int num)
    {
        assert(position + num <= length());
		memcpy(characters+position,characters+position+num,length()-num+1);
		current_length -= num;
    }

    void string::replace(char c, unsigned int position)
    {
        assert(position < length());
		characters[position] = c;
    }

    void string::replace(const string& source, unsigned int position)
    {
        assert((position + source.length()) <= length());
		strncpy(characters+(position), source.characters, source.current_length);
    }
    
    char string::operator [ ](size_t position) const
    {
        assert(position < length());
		return characters[position];
    }
    int string::search(char c) const
    {
        char* temporary = strchr(characters, c);
		if(temporary != NULL)
		{
			return temporary - characters;
		}
		else
		{
			return -1;
		}
    }
    int string::search(const string& substring) const
    {
        char* temporary = strstr(characters, substring.characters);
		if(temporary != NULL)
		{
			return temporary - characters;
		}
		else
		{
			return -1;
		}
    }
    unsigned int string::count(char c) const
    {
        unsigned int counter = 0;
		for(int i = 0; i <= current_length; i++)
		{
			if(characters[i] == c)
			{
				counter++;
			}
		}
		return counter;
    }
    
    std::ostream& operator <<(std::ostream& outs, const string& source)
    {
        int length = source.length();
		for(int i = 0; i <= length; i++)
		{
			outs << source.characters[i];
		}
		return outs;
    }

    bool operator ==(const string& s1, const string& s2)
    {
		if(strncmp(s1.characters, s2.characters, strlen(s1.characters)) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
    }

    bool operator !=(const string& s1, const string& s2)
    {
        if(s1 == s2)
		{
			return false;
		}
		else
		{
			return true;
		}
    }


    bool operator < (const string& s1, const string& s2)
    {
        if(strncmp(s1.characters,s2.characters,strlen(s1.characters)) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
    }

    bool operator > (const string& s1, const string& s2)
    {
        if((s1 < s2) || (s2 == s1))
		{
			return false;
		}
		else
		{
			return true;;
		}
    }

    
    bool operator >=(const string& s1, const string& s2)
    {
        if((s1 > s2) || (s1 == s2))
		{
			return true;
		}
		else
		{
			return false;
		}
    }

    bool operator <=(const string& s1, const string& s2)
    {
        if((s1 < s2) || (s1 == s2))
		{
			return true;
		}
		else
		{
			return false;
		}
    }

    string operator +(const string& s1, const string& s2)
    {
        string temporary(s1);
		temporary += s2;		
		return temporary;
    }

    string operator +(const string& s1, const char addend[ ])
    {
        string temporary(s1);
		temporary += addend;
		return temporary;
    }

    std::istream& operator >> (std::istream& ins, string& target)
    {
		char charEntered;
		string temporary;
		while(!ins.fail() && isspace(ins.peek()))
		{
			ins.ignore();
		}
		while(!ins.fail() && !isspace(ins.peek()))
		{
			ins >> charEntered;
			temporary += charEntered;
		}
		target = temporary;
		return ins;
    }    
};
