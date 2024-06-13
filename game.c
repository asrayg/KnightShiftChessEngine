#include "chess_engine.h"
#include "opening_book.h"
#include <stdio.h>
#include <limits.h>

bool is_check(Color color) {
    int king_x = -1, king_y = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].piece == KING && board[i][j].color == color) {
                king_x = i;
                king_y = j;
                break;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].color != color && board[i][j].piece != EMPTY) {
                Square captured = board[king_x][king_y];
                make_move(i, j, king_x, king_y);
                if (board[king_x][king_y].piece == KING) {
                    undo_move(i, j, king_x, king_y, captured);
                    return true;
                }
                undo_move(i, j, king_x, king_y, captured);
            }
        }
    }
    return false;
}

bool is_checkmate(Color color) {
    if (!is_check(color)) return false;

    generate_moves(color);
    for (MoveList *current = move_list; current != NULL; current = current->next) {
        make_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2);
        if (!is_check(color)) {
            undo_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2, current->move.captured);
            return false;
        }
        undo_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2, current->move.captured);
    }
    return true;
}

bool is_stalemate(Color color) {
    if (is_check(color)) return false;

    generate_moves(color);
    for (MoveList *current = move_list; current != NULL; current = current->next) {
        make_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2);
        if (!is_check(color)) {
            undo_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2, current->move.captured);
            return false;
        }
        undo_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2, current->move.captured);
    }
    return true;
}

void play_game() {
    initialize_board();
    load_opening_book();
    int depth = 3; // Set the depth for Minimax algorithm

    while (1) {
        print_board();

        char* position = board_to_fen();
        Move opening_move = get_opening_move(position);
        if (opening_move.x1 != -1) {
            // Use opening book move
            make_move(opening_move.x1, opening_move.y1, opening_move.x2, opening_move.y2);
        } else {
            // Use minimax for further moves
            int eval = parallel_minimax_alpha_beta(depth, true, INT_MIN, INT_MAX);
            printf("Board evaluation: %d\n", eval);

            // Update the board with the best move
            make_move(best_move.x1, best_move.y1, best_move.x2, best_move.y2);
        }

        // Check for game over conditions
        if (is_checkmate(BLACK)) {
            printf("Checkmate! White wins.\n");
            break;
        } else if (is_stalemate(BLACK)) {
            printf("Stalemate! It's a draw.\n");
            break;
        }

        print_board();
        int eval = parallel_minimax_alpha_beta(depth, false, INT_MIN, INT_MAX);
        printf("Board evaluation: %d\n", eval);

        // Update the board with the best move
        make_move(best_move.x1, best_move.y1, best_move.x2, best_move.y2);

        // Check for game over conditions
        if (is_checkmate(WHITE)) {
            printf("Checkmate! Black wins.\n");
            break;
        } else if (is_stalemate(WHITE)) {
            printf("Stalemate! It's a draw.\n");
            break;
        }
    }
}
