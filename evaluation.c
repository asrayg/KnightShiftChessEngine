#include "chess_engine.h"

const int pawn_table[SIZE][SIZE] = {
    {  0,  0,  0,  0,  0,  0,  0,  0 },
    { 50, 50, 50, 50, 50, 50, 50, 50 },
    { 10, 10, 20, 30, 30, 20, 10, 10 },
    {  5,  5, 10, 25, 25, 10,  5,  5 },
    {  0,  0,  0, 20, 20,  0,  0,  0 },
    {  5, -5,-10,  0,  0,-10, -5,  5 },
    {  5, 10, 10,-20,-20, 10, 10,  5 },
    {  0,  0,  0,  0,  0,  0,  0,  0 }
};

const int knight_table[SIZE][SIZE] = {
    { -50,-40,-30,-30,-30,-30,-40,-50 },
    { -40,-20,  0,  0,  0,  0,-20,-40 },
    { -30,  0, 10, 15, 15, 10,  0,-30 },
    { -30,  5, 15, 20, 20, 15,  5,-30 },
    { -30,  0, 15, 20, 20, 15,  0,-30 },
    { -30,  5, 10, 15, 15, 10,  5,-30 },
    { -40,-20,  0,  5,  5,  0,-20,-40 },
    { -50,-40,-30,-30,-30,-30,-40,-50 }
};

const int bishop_table[SIZE][SIZE] = {
    { -20,-10,-10,-10,-10,-10,-10,-20 },
    { -10,  0,  0,  0,  0,  0,  0,-10 },
    { -10,  0,  5, 10, 10,  5,  0,-10 },
    { -10,  5,  5, 10, 10,  5,  5,-10 },
    { -10,  0, 10, 10, 10, 10,  0,-10 },
    { -10, 10, 10, 10, 10, 10, 10,-10 },
    { -10,  5,  0,  0,  0,  0,  5,-10 },
    { -20,-10,-10,-10,-10,-10,-10,-20 }
};

const int rook_table[SIZE][SIZE] = {
    {  0,  0,  0,  0,  0,  0,  0,  0 },
    {  5, 10, 10, 10, 10, 10, 10,  5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    {  0,  0,  0,  5,  5,  0,  0,  0 }
};

const int queen_table[SIZE][SIZE] = {
    { -20,-10,-10, -5, -5,-10,-10,-20 },
    { -10,  0,  0,  0,  0,  0,  0,-10 },
    { -10,  0,  5,  5,  5,  5,  0,-10 },
    {  -5,  0,  5,  5,  5,  5,  0, -5 },
    {   0,  0,  5,  5,  5,  5,  0, -5 },
    { -10,  5,  5,  5,  5,  5,  0,-10 },
    { -10,  0,  5,  0,  0,  0,  0,-10 },
    { -20,-10,-10, -5, -5,-10,-10,-20 }
};

const int king_table[SIZE][SIZE] = {
    { -30,-40,-40,-50,-50,-40,-40,-30 },
    { -30,-40,-40,-50,-50,-40,-40,-30 },
    { -30,-40,-40,-50,-50,-40,-40,-30 },
    { -30,-40,-40,-50,-50,-40,-40,-30 },
    { -20,-30,-30,-40,-40,-30,-30,-20 },
    { -10,-20,-20,-20,-20,-20,-20,-10 },
    {  20, 20,  0,  0,  0,  0, 20, 20 },
    {  20, 30, 10,  0,  0, 10, 30, 20 }
};

const int king_endgame_table[SIZE][SIZE] = {
    { -50,-40,-30,-20,-20,-30,-40,-50 },
    { -30,-20,-10,  0,  0,-10,-20,-30 },
    { -30,-10, 20, 30, 30, 20,-10,-30 },
    { -30,-10, 30, 40, 40, 30,-10,-30 },
    { -30,-10, 30, 40, 40, 30,-10,-30 },
    { -30,-10, 20, 30, 30, 20,-10,-30 },
    { -30,-30,-10,  0,  0,-10,-30,-30 },
    { -50,-30,-30,-30,-30,-30,-30,-50 }
};

int piece_value(Piece piece) {
    switch (piece) {
        case PAWN: return 100;
        case KNIGHT: return 320;
        case BISHOP: return 330;
        case ROOK: return 500;
        case QUEEN: return 900;
        case KING: return 20000;
        default: return 0;
    }
}

int piece_square_value(Piece piece, Color color, int x, int y) {
    int value = 0;
    switch (piece) {
        case PAWN: value = pawn_table[x][y]; break;
        case KNIGHT: value = knight_table[x][y]; break;
        case BISHOP: value = bishop_table[x][y]; break;
        case ROOK: value = rook_table[x][y]; break;
        case QUEEN: value = queen_table[x][y]; break;
        case KING: value = (color == WHITE) ? king_table[x][y] : king_table[SIZE - 1 - x][y]; break;
        default: break;
    }
    return (color == WHITE) ? value : -value;
}

int evaluate_position(Square square, int x, int y) {
    int value = piece_value(square.piece);
    value += piece_square_value(square.piece, square.color, x, y);
    return (square.color == WHITE) ? value : -value;
}

int evaluate_board() {
    int score = 0;
    int mobility = 0;

    // Mobility: count the number of legal moves
    generate_moves(WHITE);
    for (MoveList *current = move_list; current != NULL; current = current->next) {
        mobility++;
    }
    generate_moves(BLACK);
    for (MoveList *current = move_list; current != NULL; current = current->next) {
        mobility--;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].piece != EMPTY) {
                score += evaluate_position(board[i][j], i, j);
            }
        }
    }

    score += mobility * 10; // Mobility factor
    score += king_safety(WHITE) - king_safety(BLACK); // King safety factor
    score += pawn_structure(WHITE) - pawn_structure(BLACK); // Pawn structure factor

    return score;
}

int king_safety(Color color) {
    int safety = 0;

    // Find king's position
    int king_x = -1, king_y = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].piece == KING && board[i][j].color == color) {
                king_x = i;
                king_y = j;
                break;
            }
        }
        if (king_x != -1) break;
    }

    // King position safety
    int king_position_value = piece_square_value(KING, color, king_x, king_y);
    safety += king_position_value;

    // Pawn shield
    int pawn_shield_value = 20;
    if (color == WHITE) {
        if (king_x > 0 && board[king_x - 1][king_y].piece == PAWN && board[king_x - 1][king_y].color == WHITE)
            safety += pawn_shield_value;
        if (king_x > 0 && king_y > 0 && board[king_x - 1][king_y - 1].piece == PAWN && board[king_x - 1][king_y - 1].color == WHITE)
            safety += pawn_shield_value;
        if (king_x > 0 && king_y < SIZE - 1 && board[king_x - 1][king_y + 1].piece == PAWN && board[king_x - 1][king_y + 1].color == WHITE)
            safety += pawn_shield_value;
    } else {
        if (king_x < SIZE - 1 && board[king_x + 1][king_y].piece == PAWN && board[king_x + 1][king_y].color == BLACK)
            safety += pawn_shield_value;
        if (king_x < SIZE - 1 && king_y > 0 && board[king_x + 1][king_y - 1].piece == PAWN && board[king_x + 1][king_y - 1].color == BLACK)
            safety += pawn_shield_value;
        if (king_x < SIZE - 1 && king_y < SIZE - 1 && board[king_x + 1][king_y + 1].piece == PAWN && board[king_x + 1][king_y + 1].color == BLACK)
            safety += pawn_shield_value;
    }

    // Opponent's attacks
    generate_moves(color == WHITE ? BLACK : WHITE);
    for (MoveList *current = move_list; current != NULL; current = current->next) {
        if ((current->move.x2 == king_x && current->move.y2 == king_y) ||
            (current->move.x2 == king_x - 1 && current->move.y2 == king_y) ||
            (current->move.x2 == king_x + 1 && current->move.y2 == king_y) ||
            (current->move.x2 == king_x && current->move.y2 == king_y - 1) ||
            (current->move.x2 == king_x && current->move.y2 == king_y + 1) ||
            (current->move.x2 == king_x - 1 && current->move.y2 == king_y - 1) ||
            (current->move.x2 == king_x - 1 && current->move.y2 == king_y + 1) ||
            (current->move.x2 == king_x + 1 && current->move.y2 == king_y - 1) ||
            (current->move.x2 == king_x + 1 && current->move.y2 == king_y + 1)) {
            safety -= 30; // Penalize if the king is under attack or near an attack
        }
    }

    return (color == WHITE) ? safety : -safety;
}

int pawn_structure(Color color) {
    int structure = 0;
    // Evaluate pawn structure (isolated, doubled, passed pawns)
    return (color == WHITE) ? structure : -structure;
}
