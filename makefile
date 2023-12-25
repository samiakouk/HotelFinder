hotelFinder: main.o hashtable.o bst.o hotel.o
	g++ main.o hashtable.o hotel.o -o hotelFinder

main.o: main.cpp 
	g++ -c main.cpp

hashtable.o: hashtable.hpp hashtable.cpp
	g++ -c   hashtable.cpp

bst.o: bst.hpp 
	g++ -c bst.hpp 


hotel.o: hotel.hpp hotel.cpp
	g++ -c hotel.cpp

clean:
	rm *.o hotelFinder
