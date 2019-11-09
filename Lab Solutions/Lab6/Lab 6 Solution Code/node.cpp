// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

using namespace coen79_lab6;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;
    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
	{
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); ++i)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;
    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
   		node *remove_ptr;
    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;
    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.

		list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }
	
	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
	{
		if(start_ptr == NULL || start_ptr == end_ptr)
		{
			head_ptr == NULL;
			tail_ptr == NULL;
			return;
		}

		if(head_ptr != NULL)
		{
			list_clear(head_ptr);
		}

		list_head_insert(head_ptr, start_ptr->data());
		tail_ptr = head_ptr;
		node* temp = start_ptr->link();
		while(temp != NULL && temp != end_ptr)
		{
			list_insert(tail_ptr, temp->data());
			temp = temp->link();
			tail_ptr = tail_ptr->link();
		}
	}

	size_t list_occurrences(node* head_ptr, const node::value_type& target)
	{
		node* temp = head_ptr;
		size_t counter = 0;
		while(temp != NULL)
		{
			if(temp->data() == target)
			{
				counter++;
			}
			temp = temp->link();
		}
		return counter;
	}

	void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position)
	{
		assert((position > 0) && (position <= list_length(head_ptr) + 1));
		if(position == 1)
		{
			node* addedNode = new node(entry, head_ptr);
			head_ptr = addedNode;
		}
		else
		{
			node* precursor = head_ptr;
			node* cursor = list_locate(head_ptr, position);
			while(precursor->link() != cursor)
			{
				precursor = precursor->link();
			}
			node* addedNode = new node(entry,cursor);
			precursor->set_link(addedNode);
		}
	}
	
	node::value_type list_remove_at(node*& head_ptr, size_t position)
	{
		assert((position > 0) && (position <= list_length(head_ptr)));
		node::value_type removeNode;
		node* cursor = head_ptr;
		if(position == 1)
		{
			head_ptr = cursor->link();
			removeNode = cursor->data();
			delete(cursor);
		}
		else
		{
			node* precursor = head_ptr;
			node* cursor = list_locate(head_ptr, position);
			while(precursor->link() != cursor)
			{
				precursor = precursor->link();
			}
			removeNode = cursor->data();
			precursor->set_link(cursor->link());
			delete(cursor);
		}
		return removeNode;
	}

	node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
	{
		assert(1 <= start);
		assert(start <= finish);
		assert(finish <= list_length(head_ptr));
		node* cursor = head_ptr;
		size_t loopCounter = start;
		node* temp = NULL;
		while((start) != 1)
		{
			cursor = cursor->link();
			start--;
		}
		list_head_insert(temp,cursor->data());
		node* tail_ptr = temp;
		for(size_t i = loopCounter+1; i<= finish; i++)
		{
			cursor = cursor->link();
			list_insert(tail_ptr, cursor->data());
			tail_ptr = tail_ptr->link();
		}
		return temp;
	}

	void list_print(const node* head_ptr)
	{
		const node* temp = head_ptr;
		while(temp != NULL)
		{
			if(temp->link() == NULL)
			{
				cout << temp->data() << " ";
			}
			else
			{
				cout << temp->data()<< "," << " ";
			}
			temp = temp->link();
		}
		cout << endl;
	}

	void list_remove_dups(node* head_ptr)
	{
		node *temp = head_ptr;
		while(temp != NULL)
		{
			node* runner = head_ptr;
			while(runner->link() != NULL)
			{
				if(runner->data() == runner->link()->data())
				{
					node* tempDelete = runner->link();
					node* tempLink = runner->link()->link();
					runner->set_link(tempLink);
					delete tempDelete;
				}
				else
				{
					runner = runner->link();
				}
			}
		temp = temp->link();
		}
	}

	node* list_detect_loop(node* head_ptr)
	{
		assert(head_ptr != NULL);
		node* slow_runner = head_ptr;
		node* fast_runner = head_ptr;
		while(fast_runner != NULL && fast_runner->link() != NULL)
		{
			slow_runner = slow_runner->link();
			fast_runner = fast_runner->link()->link();
			if(slow_runner == fast_runner)
			{
				cout << "the pointers met!" << endl;
				break;
			}
		}
		if(fast_runner == NULL || fast_runner->link() == NULL)
		{
			return NULL;
		}
		slow_runner = head_ptr;
		while(slow_runner != fast_runner)
		{
			slow_runner = slow_runner->link();
			fast_runner = fast_runner->link();
		}
		return fast_runner;
	}
};
