CC = g++
CFLAGS = -Wall -std=c++14

mainprogam: mainprogam.o card.o Player.o
	$(CC) $(CFLAGS) mainprogam.o card.o Player.o -o mainprogam

mainprogam.o: mainprogam.cpp card.hpp Player.hpp
	$(CC) $(CFLAGS) -c mainprogam.cpp

card.o: card.cpp card.hpp
	$(CC) $(CFLAGS) -c card.cpp

Player.o: Player.cpp Player.hpp
	$(CC) $(CFLAGS) -c Player.cpp

clean:
	rm *.o

