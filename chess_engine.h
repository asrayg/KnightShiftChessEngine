#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 8
#define NUM_THREADS 4

typedef enum { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING } Piece;
typedef enum { WHITE, BLACK } Color;

typedef struct {
    Piece piece;
    Color color;
} Square;

typedef struct MoveList {
    Move move;
    struct MoveList *next;
} MoveList;


typedef struct {
    int x1, y1, x2, y2;
    Square captured;
} Move;

extern Square board[SIZE][SIZE];
extern Move best_move;
extern MoveList *move_list;



void initialize_board();
void generate_moves(Color color);
void generate_pawn_moves(int x, int y, Color color);
void generate_knight_moves(int x, int y, Color color);
void generate_bishop_moves(int x, int y, Color color);
void generate_rook_moves(int x, int y, Color color);
void generate_queen_moves(int x, int y, Color color);
void generate_king_moves(int x, int y, Color color);
bool is_valid_move(int x, int y);
int evaluate_board();
int minimax_alpha_beta(int depth, bool isMaximizing, int alpha, int beta);
void play_game();
void print_board();
void make_move(int x1, int y1, int x2, int y2);
void undo_move(int x1, int y1, int x2, int y2, Square captured);
bool is_checkmate(Color color);
bool is_stalemate(Color color);
int evaluate_position(Square square, int x, int y);
void initialize_bitboards();
char* board_to_fen();
Move get_opening_move(char* position);

#endif 
