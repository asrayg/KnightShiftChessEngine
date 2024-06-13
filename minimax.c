#include "chess_engine.h"
#include <limits.h>
#include <pthread.h>

typedef struct {
    int depth;
    int alpha;
    int beta;
    bool isMaximizing;
    int result;
} SearchArgs;

void* parallel_search(void* args) {
    SearchArgs* search_args = (SearchArgs*)args;
    search_args->result = minimax_alpha_beta(search_args->depth, search_args->isMaximizing, search_args->alpha, search_args->beta);
    return NULL;
}

int minimax_alpha_beta(int depth, bool isMaximizing, int alpha, int beta) {
    if (depth == 0) {
        return evaluate_board();
    }

    if (isMaximizing) {
        int maxEval = INT_MIN;
        generate_moves(WHITE);
        for (MoveList *current = move_list; current != NULL; current = current->next) {
            make_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2);
            int eval = minimax_alpha_beta(depth - 1, false, alpha, beta);
            undo_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2, current->move.captured);
            if (eval > maxEval) {
                maxEval = eval;
                if (depth == 3) {
                    best_move = current->move;
                }
            }
            alpha = (alpha > eval) ? alpha : eval;
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        generate_moves(BLACK);
        for (MoveList *current = move_list; current != NULL; current = current->next) {
            make_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2);
            int eval = minimax_alpha_beta(depth - 1, true, alpha, beta);
            undo_move(current->move.x1, current->move.y1, current->move.x2, current->move.y2, current->move.captured);
            minEval = (eval < minEval) ? eval : minEval;
            beta = (beta < eval) ? beta : eval;
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

int parallel_minimax_alpha_beta(int depth, bool isMaximizing, int alpha, int beta) {
    pthread_t threads[NUM_THREADS];
    SearchArgs args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].depth = depth;
        args[i].alpha = alpha;
        args[i].beta = beta;
        args[i].isMaximizing = isMaximizing;
        pthread_create(&threads[i], NULL, parallel_search, &args[i]);
    }

    int final_result = isMaximizing ? INT_MIN : INT_MAX;

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        if (isMaximizing) {
            final_result = (args[i].result > final_result) ? args[i].result : final_result;
        } else {
            final_result = (args[i].result < final_result) ? args[i].result : final_result;
        }
    }

    return final_result;
}
