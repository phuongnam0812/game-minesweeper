CC = g++
CFLAGS = -Wall -Werror -std=c++11

.PHONY: all clean

all: minesweeper

run: ./minesweeper

minesweeper: main.o MineSweeper.o Cell.o Board.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.cpp MineSweeper.h
	$(CC) $(CFLAGS) -c $< -o $@

MineSweeper.o: MineSweeper.cpp MineSweeper.h Cell.h Board.h
	$(CC) $(CFLAGS) -c $< -o $@

Cell.o: Cell.cpp Cell.h
	$(CC) $(CFLAGS) -c $< -o $@

Board.o: Board.cpp Board.h Cell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o minesweeper