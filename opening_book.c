#include "opening_book.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 100

OpeningBook opening_book;

void initialize_opening_book() {
    opening_book.entries = (OpeningEntry *)malloc(INITIAL_CAPACITY * sizeof(OpeningEntry));
    opening_book.size = 0;
    opening_book.capacity = INITIAL_CAPACITY;
}

void add_opening_move(const char *position, Move move) {
    if (opening_book.size >= opening_book.capacity) {
        opening_book.capacity *= 2;
        opening_book.entries = (OpeningEntry *)realloc(opening_book.entries, opening_book.capacity * sizeof(OpeningEntry));
    }
    strcpy(opening_book.entries[opening_book.size].position, position);
    opening_book.entries[opening_book.size].move = move;
    opening_book.size++;
}

Move get_opening_move(const char *position) {
    for (size_t i = 0; i < opening_book.size; i++) {
        if (strcmp(opening_book.entries[i].position, position) == 0) {
            return opening_book.entries[i].move;
        }
    }
    Move no_move = {-1, -1, -1, -1, {EMPTY, WHITE}};
    return no_move;
}

void load_opening_book() {
    initialize_opening_book();
    // Opening: 1. e4 e5
    Move e4_e5 = {4, 6, 4, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", e4_e5);

    // Opening: 1. e4 e5 2. Nf3 Nc6
    Move Nf3_Nc6 = {1, 7, 2, 5, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1", Nf3_Nc6);

    // Opening: 1. d4 d5
    Move d4_d5 = {3, 6, 3, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", d4_d5);

    // Opening: 1. c4 e5
    Move c4_e5 = {2, 6, 2, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", c4_e5);

    // Opening: 1. Nf3 d5
    Move Nf3_d5 = {1, 7, 2, 5, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", Nf3_d5);

    // Opening: 1. g3 d5
    Move g3_d5 = {6, 7, 6, 5, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", g3_d5);

    // Opening: 1. e4 c5
    Move e4_c5 = {4, 6, 4, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", e4_c5);

    // Opening: 1. e4 e6
    Move e4_e6 = {4, 6, 4, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", e4_e6);

    // Opening: 1. e4 c6
    Move e4_c6 = {4, 6, 4, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", e4_c6);

    // Opening: 1. d4 Nf6
    Move d4_Nf6 = {3, 6, 3, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", d4_Nf6);

    // Opening: 1. d4 f5
    Move d4_f5 = {3, 6, 3, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", d4_f5);
}

