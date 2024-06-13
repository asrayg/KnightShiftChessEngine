#include "chess_engine.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct MoveList {
    Move move;
    struct MoveList *next;
} MoveList;

MoveList *move_list = NULL;

void add_move(int x1, int y1, int x2, int y2, Square captured) {
    MoveList *new_move = (MoveList *)malloc(sizeof(MoveList));
    new_move->move.x1 = x1;
    new_move->move.y1 = y1;
    new_move->move.x2 = x2;
    new_move->move.y2 = y2;
    new_move->move.captured = captured;
    new_move->next = move_list;
    move_list = new_move;
}

void clear_move_list() {
    MoveList *current = move_list;
    while (current != NULL) {
        MoveList *temp = current;
        current = current->next;
        free(temp);
    }
    move_list = NULL;
}

bool is_valid_move(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

void generate_pawn_moves(int x, int y, Color color) {
    int direction = (color == WHITE) ? 1 : -1;
    if (is_valid_move(x + direction, y) && board[x + direction][y].piece == EMPTY) {
        add_move(x, y, x + direction, y, board[x + direction][y]);
    }
    if (is_valid_move(x + direction, y + 1) && board[x + direction][y + 1].piece != EMPTY && board[x + direction][y + 1].color != color) {
        add_move(x, y, x + direction, y + 1, board[x + direction][y + 1]);
    }
    if (is_valid_move(x + direction, y - 1) && board[x + direction][y - 1].piece != EMPTY && board[x + direction][y - 1].color != color) {
        add_move(x, y, x + direction, y - 1, board[x + direction][y - 1]);
    }
    if ((color == WHITE && x + direction == 7) || (color == BLACK && x + direction == 0)) {
        board[x][y].piece = QUEEN;
    }
}

void generate_knight_moves(int x, int y, Color color) {
    int knight_moves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    for (int i = 0; i < 8; i++) {
        int newX = x + knight_moves[i][0];
        int newY = y + knight_moves[i][1];
        if (is_valid_move(newX, newY) && (board[newX][newY].piece == EMPTY || board[newX][newY].color != color)) {
            add_move(x, y, newX, newY, board[newX][newY]);
        }
    }
}

void generate_bishop_moves(int x, int y, Color color) {
    int directions[4][2] = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
    for (int d = 0; d < 4; d++) {
        for (int i = 1; i < SIZE; i++) {
            int newX = x + i * directions[d][0];
            int newY = y + i * directions[d][1];
            if (is_valid_move(newX, newY)) {
                if (board[newX][newY].piece == EMPTY) {
                    add_move(x, y, newX, newY, board[newX][newY]);
                } else if (board[newX][newY].color != color) {
                    add_move(x, y, newX, newY, board[newX][newY]);
                    break;
                } else {
                    break;
                }
            }
        }
    }
}

void generate_rook_moves(int x, int y, Color color) {
    int directions[4][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
    for (int d = 0; d < 4; d++) {
        for (int i = 1; i < SIZE; i++) {
            int newX = x + i * directions[d][0];
            int newY = y + i * directions[d][1];
            if (is_valid_move(newX, newY)) {
                if (board[newX][newY].piece == EMPTY) {
                    add_move(x, y, newX, newY, board[newX][newY]);
                } else if (board[newX][newY].color != color) {
                    add_move(x, y, newX, newY, board[newX][newY]);
                    break;
                } else {
                    break;
                }
            }
        }
    }
}

void generate_queen_moves(int x, int y, Color color) {
    generate_bishop_moves(x, y, color);
    generate_rook_moves(x, y, color);
}

void generate_king_moves(int x, int y, Color color) {
    int king_moves[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
    for (int i = 0; i < 8; i++) {
        int newX = x + king_moves[i][0];
        int newY = y + king_moves[i][1];
        if (is_valid_move(newX, newY) && (board[newX][newY].piece == EMPTY || board[newX][newY].color != color)) {
            add_move(x, y, newX, newY, board[newX][newY]);
        }
    }
}

void generate_moves(Color color) {
    clear_move_list();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].color == color) {
                switch (board[i][j].piece) {
                    case PAWN:
                        generate_pawn_moves(i, j, color);
                        break;
                    case KNIGHT:
                        generate_knight_moves(i, j, color);
                        break;
                    case BISHOP:
                        generate_bishop_moves(i, j, color);
                        break;
                    case ROOK:
                        generate_rook_moves(i, j, color);
                        break;
                    case QUEEN:
                        generate_queen_moves(i, j, color);
                        break;
                    case KING:
                        generate_king_moves(i, j, color);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
