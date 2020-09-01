.default: all

all: assign2

clean:
	rm -f assign2 *.o

assign2:
	main.o Player.o PlayerBoard.o
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -c $^