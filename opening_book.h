#ifndef OPENING_BOOK_H
#define OPENING_BOOK_H

#include "chess_engine.h"

typedef struct {
    char position[100];
    Move move;
} OpeningEntry;

typedef struct {
    OpeningEntry *entries;
    size_t size;
    size_t capacity;
} OpeningBook;

void initialize_opening_book();
void add_opening_move(const char *position, Move move);
Move get_opening_move(const char *position);

#endif 
