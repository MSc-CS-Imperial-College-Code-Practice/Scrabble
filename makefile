exec: main.o scrabble.o
	  	g++ -Wall -g main.o scrabble.o -o exec

main.o: main.cpp scrabble.h
		g++ -Wall -g -c main.cpp

scrabble.o: scrabble.cpp scrabble.h
		  g++ -Wall -g -c scrabble.cpp 

clean:
	  rm -f *.o exec