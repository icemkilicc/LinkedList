networkmap:CircularLinkedListApartment DoublyLinkedListFlat main
	g++ -std=c++11 CircularLinkedListApartment.o DoublyLinkedListFlat.o main.o -o networkmap
CircularLinkedListApartment:
	g++ -std=c++11 -c CircularLinkedListApartment.cpp -o CircularLinkedListApartment.o
DoublyLinkedListFlat:
	g++ -std=c++11 -c DoublyLinkedListFlat.cpp -o DoublyLinkedListFlat.o
main:
	g++ -std=c++11 -c main.cpp -o main.o
	
	

