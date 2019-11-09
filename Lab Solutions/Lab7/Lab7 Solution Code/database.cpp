// 
// Team 8: Jordan Murtiff and Shaunak Mashalkar
// 
// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"
#include <iostream>


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
		company_array = new company[src.aloc_slots];
		aloc_slots = src.aloc_slots;
		used_slots = src.used_slots;
		std::copy(src.company_array,src.company_array+src.used_slots,company_array);
    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
		std::cout << "copying elements of database...";
		aloc_slots = rhs.aloc_slots;
		used_slots = rhs.used_slots;
		company_array = new company[rhs.aloc_slots];
		std::copy(rhs.company_array,rhs.company_array+rhs.used_slots,company_array);
        return *this;
    }
    
    
    database::~database()
    {
        delete [] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        company *tempCompany = new company[new_capacity];
        std::copy(company_array,company_array+used_slots,tempCompany);
        company_array = tempCompany;
        aloc_slots = new_capacity;
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
		if(used_slots == aloc_slots)
		{
			reserve(aloc_slots+1);
		}
		company_array[used_slots] = company(entry);
		used_slots++;
		return true;
    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);
		size_type index = 0;
		index = search_company(company);
		if(index == COMPANY_NOT_FOUND)
		{
			return false;
		}
		company_array[index].insert(product_name, price);
		return true;
        
    }
    
    
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        //just shift everything over to overide erasing the company
        if(company_index == COMPANY_NOT_FOUND)
		{
			return false;
		}
		for(int i = company_index; i < used_slots-1; i++)
		{
			company_array[i] = company_array[i+1];
		}
		used_slots--;
		return true;
        
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);
		size_type company_index = search_company(cName);
		if(company_index == COMPANY_NOT_FOUND)
		{
			return false;
		}
		node* tempSearch = company_array[company_index].get_head();
		node* answer = list_search(tempSearch,pName);
		if(answer == NULL)
		{
			return false;
		}
		if(answer == company_array[company_index].get_head())
		{
			list_head_remove(answer);
		}
		else
		{
			node*cursor;
			for(cursor = company_array[company_index].get_head(); cursor != NULL; cursor = cursor->getLink())
			{
				if(cursor->getLink() == answer)
				{
					break;
				}
			}
			cursor->setLink(answer->getLink());
			delete answer;
		}
		return true;
	}
    
    
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
		size_type i;
		for(i = 0; i < used_slots; i++)
		{
			if(company == company_array[i].get_name())
			{
				return i;
			}
		}
		return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
