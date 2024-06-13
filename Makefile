CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread

SRC = main.c board.c evaluation.c moves.c minimax.c game.c opening_book.c
OBJ = $(SRC:.c=.o)

chess_engine: $(OBJ)
	$(CC) $(CFLAGS) -o chess_engine $(OBJ)

clean:
	rm -f $(OBJ) chess_engine
