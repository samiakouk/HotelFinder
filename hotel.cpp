#include "hotel.hpp" // Include the header file for the Hotel class definition.
#include<iostream>  // Include the standard input-output stream library for using cout.
#include<iomanip>   // Include the input-output manipulators library for formatting output.
#include<string>    // Include the string library for using the string data type.

using namespace std; // Use the standard namespace to avoid prefixing std::.

// Constructor for the Hotel class. It initializes the Hotel object with the given parameters.
Hotel::Hotel(string name, string city, string stars, string price, string country, string address){
	this->name = name;       // Set the hotel's name.
	this->city = city;       // Set the city where the hotel is located.
	this->stars = stars;     // Set the star rating of the hotel.
	this->price = price;     // Set the price per night of the hotel.
	this->country = country; // Set the country where the hotel is located.
	this->address = address; // Set the address of the hotel.
}

// Getter method for the hotel's name.
string Hotel::getName(){
	return name;
}	

// Getter method for the city where the hotel is located.
string Hotel::getCity(){
	return city;
}	

// Getter method for the hotel's star rating.
string Hotel::getStars(){
	return stars;
}

// Getter method for the hotel's price per night.
string Hotel::getPrice(){
	return price;
}

// Getter method for the country where the hotel is located.
string Hotel::getCountry(){
	return country;
}

// Getter method for the hotel's address.
string Hotel::getAddress(){
	return address;
}

// Method to print the hotel's details in a formatted manner. This version does not return a value.
string Hotel::toString(){
	cout << "Hotel Name: " << name << endl
		 << "City: " << city << endl
		 << "Stars: " << stars << endl
		 << "Price: " << price << "$/night" << endl
		 << "Country: " << country << endl
		 << "Address: " << address << endl;
}

// Alternate method to print the hotel's details. This version does not return a value.
void Hotel::print(){
	cout << "Hotel Name: " << name << endl
		 << "City: " << city << endl
		 << "Stars: " << stars << endl
		 << "Price: " << price << "$/night" << endl
		 << "Country: " << country << endl
		 << "Address: " << address << endl;
}

// Another alternate method for printing the hotel's details, but in a tabular format using iomanip manipulators.
void Hotel::print2(){
	cout << left << setw(50) << name << " " << setw(10) << city << " " << setw(5) << stars << " " << setw(10) << price << " " << setw(20) << country << " " << address << endl;
}
