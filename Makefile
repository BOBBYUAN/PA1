
all: prog1A prog1B

prog1A: main.o HashTable.o
	g++ main.o HashTable.o -o prog1A

prog1B: advance.o HashTable.o
	g++ advance.o HashTable.o -o prog1B

main.o: main.cpp
	g++ -c main.cpp

advance.o: advance.cpp
	g++ -c advance.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -c HashTable.cpp

clean:
	rm *.o prog1A
	rm *.o prog1B
