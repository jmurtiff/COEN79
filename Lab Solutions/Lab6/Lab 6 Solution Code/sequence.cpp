//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

using namespace coen79_lab6;

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

	sequence::~sequence()
	{
		list_clear(head_ptr);
		many_nodes = 0;
	}

	void sequence:: start()
	{
		cursor = head_ptr;
		precursor = NULL;
	}

	void sequence::end()
	{
		cursor = tail_ptr;
		precursor = list_locate(head_ptr, many_nodes-1);
	}

	void sequence::advance()
	{
		assert(is_item() == true);
		if(cursor == NULL)
		{
			return;
		}
		precursor = cursor;
		cursor = cursor->link();
	}

	void sequence::insert(const value_type& entry)
	{
		if(is_item() == true)
		{
			if(precursor == NULL)
			{
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
			}
			else
			{
				list_insert(precursor, entry);
				cursor = precursor->link();
			}
		}
		else
		{
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;
			precursor = NULL;
		}
		many_nodes+= 1;
		node* temporary = head_ptr;
		for(int i = 0; i < many_nodes; i++)
		{
            tail_ptr = temporary;
			temporary = temporary->link();
		}
	}

	void sequence::attach(const value_type& entry)
	{
		if(is_item())
		{
			list_insert(cursor, entry);
			precursor = cursor;
			cursor = cursor->link();
			if(precursor == tail_ptr)
			{
				tail_ptr = cursor;
			}
		}
		else
		{
			if(many_nodes == 0)
			{
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				head_ptr = cursor;
				tail_ptr = cursor;
				precursor = NULL;
			}
			else
			{
				list_insert(tail_ptr, entry);
				precursor = tail_ptr;
				cursor = precursor->link();
				tail_ptr = cursor;
			}

		}
		many_nodes++;
	}


	void sequence::operator =(const sequence& source)
	{
		if(this == &source)
		{
			return;
		}
		list_clear(head_ptr);
		init();
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		if(source.precursor == NULL)
		{
			if(source.cursor != NULL)
			{
				cursor = head_ptr;
			}
			else
			{
				cursor = NULL;
			}
			precursor = NULL;
		}
		else
		{
			node* temporary = head_ptr;
			node* tempSource = source.head_ptr;
			while(tempSource != source.precursor)
			{
				tempSource = tempSource->link();
				temporary = temporary->link();
			}
			cursor = temporary->link();
			precursor = temporary;
		}
		many_nodes = source.many_nodes;
	}

	void sequence::remove_current()
	{
		assert(is_item() == true);
		if(many_nodes == 1)
		{
			list_head_remove(head_ptr);
			cursor = NULL;
			precursor = NULL;
			head_ptr = NULL;
			many_nodes--;
			return;
		}
		if(cursor == head_ptr)
		{
			node* temporary = head_ptr;
			head_ptr = head_ptr->link();
			delete(temporary);
			cursor = head_ptr;
			precursor = NULL;
			many_nodes--;
			return;
		}
		cursor = cursor->link();
		list_remove(precursor);
		many_nodes--;
	}

	sequence::size_type sequence::size() const
	{
		return many_nodes;
	}

	bool sequence::is_item() const
	{
		if(cursor == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	node::value_type sequence::current() const
	{
		assert(is_item() == true);
		return cursor->data();
	}
};
