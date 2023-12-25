//============================================================================
// Name         : 
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-04-2023
// Date Modified: 23-08-2023 
// Description  : 
//============================================================================
#pragma once 
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<list>
#include "hotel.hpp"
#include "bst.hpp"


using namespace std;
class Entry
{
	private:
		string key;			//hotel name
		Hotel *value;		//hotel object
	public:
		Entry(string key, Hotel *value)
		{
			this->key = key;
			this->value = value;
		}
		friend class HashTable;
};
//===============================================================
class HashTable
{
	private:
		list<Entry> *buckets;		    			// Array of lists of type Entries for Chaining
		BST<string,Hotel*> cityRecords;
		unsigned int size;					   		//Current Size of HashTable
		unsigned int capacity;				    	// Total Capacity of HashTable
		unsigned int collisions; 					// Total Number of Collisions
	public:
		HashTable(int capacity); // Constructor		
		unsigned long hashCode(string key); // Hash function: Converts a string key into a valid index for the hash table
		void insert(string key, Hotel* value); // Method to insert a key-value pair into the hash table
		Hotel* find(string key); // Method to find a value associated with a key in the hash table
		void findAll(string city,string stars); // Method to find all hotels in a given city with specified stars
		void erase(string key); // Method to erase a key-value pair from the hash table
		unsigned int getSize(); // Method to get the size of the hash table
		unsigned int getCollisions(); // Method to get the number of collisions in the hash table
		void dump(string path); // Method to dump the contents of the hash table into a file
		~HashTable(); // Destructor for the HashTable class
};
//=================================================================
// implement the methods list above in a file called hashtable.cpp