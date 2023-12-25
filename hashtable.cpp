// Include all the necessary libraries
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<list>

// Include all the neccessary headera
#include "hashtable.hpp"
#include "hotel.hpp"
#include "bst.hpp"



using namespace std;

// Constructor
HashTable::HashTable(int capacity){
    this->capacity = capacity;  // Set the capacity of the hash table
    this->size = 0;             // Initialize size to 0
    this->collisions = 0;       // Initialize collision count to 0

    buckets = new list<Entry>[capacity];  // Allocate memory for the array of lists
}

// Hash function: Converts a string key into a valid index for the hash table
unsigned long HashTable::hashCode(string key){
    unsigned long hCode = 0;  // Initialize hash code

    for(int i = 0; i < key.size(); i++){  // Iterate over each character in the key
        hCode += (unsigned long)key[i];   // Add ASCII value of the character to the hash code

        hCode = (hCode << 2) | (hCode >> 62);  // Left shift by 2 and right shift by 62 for mixing bits
    }

    hCode = (5 * hCode + 7) % capacity;  // Apply a final transformation and modulo by capacity

    return hCode;  // Return the computed hash code
}

// Method to insert a key-value pair into the hash table
void HashTable::insert(string key, Hotel* value){
	stringstream ss(key); // Use string stream for parsing the key
 	string hotelName, cityName;

 	getline(ss, hotelName, ','); // Extract hotel name from the key
 	getline(ss, cityName, '\0'); // Extract city name from the key

 	cityRecords.insert(cityRecords.getRoot(), cityName, value); // Insert into city records in the BST


 	unsigned long index = hashCode(key); // Compute hash code for the key

 	if(buckets[index].empty()){ // Check if bucket is empty
 		// cout << "New Record has been successfully added to the Database." << endl;
 		buckets[index].push_back(Entry(key, value)); // Insert new entry
 		size++; // Increment size of the hash table
 		return;
 	}

 	// Search through the bucket using an iterator
 	for(list<Entry>::iterator p = buckets[index].begin(); p != buckets[index].end(); p++){
 		if(p->key == key){ // Check if key already exists
 			cout << "Existing Record has been updated." << endl;
 			p->value = value; // Update value for the existing key
 			return;
 		}
 	}

 	// If the key is not present in the bucket
 	buckets[index].push_back(Entry(key, value)); // Insert new entry at the end
 	size++; // Increment size
 	collisions++; // Increment collision count

 	// cout << "New Record has been successfully added to the Database." << endl;
}

// Method to find a value associated with a key in the hash table
Hotel* HashTable::find(string key){
 	unsigned long index = hashCode(key); // Compute hash code for the key
 	int comparison = 1; // Initialize comparison counter

 	// Search through the bucket
 	for(list<Entry>::iterator p = buckets[index].begin(); p != buckets[index].end(); p++){
 		if(p->key == key){ // If the keys match
 			cout << "Record found after: " << comparison << " comparisons" << endl;
 			return p->value; // Return the associated value
 		}
 		comparison++; // Increment the comparison counter
 	}

 	// In case the was not found, display a message and return null pointer in this case
 	cout << "Record have not been found" << endl;
 	return nullptr;

}

// Method to find all hotels in a given city with specified stars
void HashTable::findAll(string city,string stars){
	// In case, the node returned by the BST, print an error message
	if(cityRecords.find(cityRecords.getRoot(), city, stars) == nullptr){
		cout << "City Records were not found." << endl;
		return;
	}

 	cityRecords.find(cityRecords.getRoot(), city, stars)->print(stars); // Print found records
}

// Method to erase a key-value pair from the hash table
void HashTable::erase(string key){
	stringstream ss(key); // Use string stream for parsing the key
 	string hotelName, cityName;

 	getline(ss, hotelName, ','); // Extract hotel name from the key
 	getline(ss, cityName, '\0'); // Extract city name from the key

 	unsigned long index = hashCode(key); // Compute hash code for the key

 	// Search through the bucket
 	for(list<Entry>::iterator p = buckets[index].begin(); p != buckets[index].end(); p++){
 		if(p->key == key){ // If keys match
 			cityRecords.remove(cityRecords.getRoot(), cityName, p->value); // Remove hotel from the BST
 			buckets[index].erase(p); // Remove the Entry (key-value) from the bucket
 			cout << key << " has been successfully deleted." << endl; // Display a message to the user
 			return;
 		}
 	}

 	// In case the key was not found, display a message
 	cout << "Record have not been found" << endl;



}

// Method to get the size of the hash table
unsigned int HashTable::getSize(){
 	return size; // Return the size
}

// Method to get the number of collisions in the hash table
unsigned int HashTable::getCollisions(){
 	return collisions; // Return the collision count
}

// Method to dump the contents of the hash table into a file
void HashTable::dump(string path){ 
	ofstream ofile; // Create an output file stream
	ofile.open(path); // Open the specified file
	int counter = 0; // Initialize a counter

	// If the file fails to open, display an error message
	if(ofile.fail()){
		cerr << "Could not open one fo the files" << endl;
		return;
	}

	ofile << "hotelName,cityName,stars,price,countryName,address" << endl; // Write header to file

	// Iterate through the buckets
	for(int i = 0; i < capacity; i++){
		// Iterate through each bucket
		for(list<Entry>::iterator p = buckets[i].begin(); p != buckets[i].end(); p++){
			// Write each record to the file
			ofile << p->value->getName() << "," << p->value->getCity() << "," << p->value->getStars() << "," << p->value->getPrice() << "," << p->value->getCountry() << "," << p->value->getAddress() << endl;
			// Increment the counter
			counter++;
 		}
	}

	cout << counter << " records have been successfully exported to " << path << endl; // Print a message to the user
	ofile.close();// Close the file


}

// Destructor for the HashTable class
HashTable::~HashTable(){
	delete[] buckets; // Deallocate the array of lists
}