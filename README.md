# KnightShiftChessEngine

## Overview

This project implements a simple chess engine in C. The engine uses the Minimax algorithm with Alpha-Beta pruning for decision-making and includes features such as an evaluation function, move generation, and an opening book.

## Features

- **Minimax Algorithm with Alpha-Beta Pruning**: The core decision-making algorithm used to evaluate moves.
- **Evaluation Function**: Considers piece values, piece-square tables, mobility, king safety, and pawn structure.
- **Move Generation**: Generates legal moves for all pieces.
- **Opening Book**: Uses a predefined set of opening moves to improve early-game performance.
- **Parallel Search**: Utilizes multi-threading to parallelize the search process.
- **Game Over Checks**: Complete checks for checkmate and stalemate considering all rules.

## File Structure

```
chess_engine/
├── Makefile
├── chess_engine.h
├── main.c
├── board.c
├── evaluation.c
├── moves.c
├── minimax.c
├── game.c
├── opening_book.c
└── opening_book.h
└── Asray_s_Chess_Engine_Analysis.pdf
```

## Installation

1. **Clone the repository**:
    ```sh
    git clone <repository_url>
    cd chess_engine
    ```

2. **Compile the project**:
    ```sh
    make
    ```

3. **Run the executable**:
    ```sh
    ./chess_engine
    ```

## Usage

- The program runs a game of chess where the engine plays against itself using the Minimax algorithm and opening book.
- The board state is printed to the console after each move.
- The engine evaluates the board state and makes the best move based on the evaluation function and the opening book.

## Algorithms

### Minimax Algorithm with Alpha-Beta Pruning

The Minimax algorithm is a recursive decision-making algorithm used in two-player games like chess. The objective is to minimize the possible loss in a worst-case scenario (for the minimizing player) or maximize the possible gain (for the maximizing player).

**Alpha-Beta Pruning** is an optimization technique for the Minimax algorithm that reduces the number of nodes evaluated in the search tree. It keeps track of two values, alpha and beta:
- **Alpha**: The best value that the maximizing player can guarantee.
- **Beta**: The best value that the minimizing player can guarantee.

When exploring the search tree:
- If the current node's value is worse than the value of alpha for the maximizing player, or worse than the value of beta for the minimizing player, further exploration of this node is stopped (pruned).

### Evaluation Function

The evaluation function is crucial for the engine's decision-making. It assesses the board state and returns a numerical value indicating the favorability of the position for a player.

**Key Components**:
- **Piece Values**: Assigns values to different pieces (e.g., Pawn=100, Knight=320).
- **Piece-Square Tables**: Provides additional value based on a piece's position on the board.
- **Mobility**: The number of legal moves available to a player.
- **King Safety**: Assesses the safety of the king considering factors like pawn shields and nearby attacks.
- **Pawn Structure**: Evaluates the position and formation of pawns (e.g., isolated pawns, doubled pawns).

### Move Generation

Move generation is responsible for creating a list of all legal moves for a player. This involves:
- **Piece-Specific Moves**: Generating moves for each piece type (e.g., pawns, knights, bishops).
- **Move Validation**: Ensuring moves are within the bounds of the board and do not leave the player in check.

### Opening Book

The opening book contains a set of pre-computed opening moves to guide the engine during the initial phase of the game. This helps in:
- **Speeding Up Early Moves**: By using pre-determined moves, the engine saves computational resources.
- **Improving Play Quality**: Using well-known openings helps in achieving a stronger position in the early game.

### Parallel Search

Parallel search utilizes multi-threading to improve the efficiency of the Minimax algorithm. By dividing the search tree among multiple threads, the engine can explore more nodes in the same amount of time, leading to deeper searches and better move decisions.

### Game Over Checks

The engine includes comprehensive checks for:
- **Checkmate**: When the player's king is in check and no legal moves can remove the threat.
- **Stalemate**: When the player has no legal moves and the king is not in check.

## Code Explanation

### Header File: `chess_engine.h`

Defines the core structures and function prototypes used throughout the project.

### Main File: `main.c`

Entry point for the program, calls the `play_game` function.

### Board Initialization and Management: `board.c`

- Initializes the board to the starting position.
- Converts the board state to a FEN string.
- Prints the board state.
- Implements functions to make and undo moves.

### Evaluation Function: `evaluation.c`

- Defines piece-square tables for evaluating piece positions.
- Implements the evaluation function considering piece values, mobility, king safety, and pawn structure.

### Move Generation: `moves.c`

- Generates legal moves for all pieces.
- Implements helper functions to add moves to the move list.

### Minimax Algorithm: `minimax.c`

- Implements the Minimax algorithm with Alpha-Beta pruning.
- Parallelizes the search using multi-threading.

### Game Management: `game.c`

- Manages the game loop.
- Checks for game over conditions (checkmate and stalemate).

### Opening Book: `opening_book.c` and `opening_book.h`

- Implements a simple hash map for storing and retrieving opening moves.
- Preloads a set of common opening moves to improve early-game performance.

## Adding More Opening Moves

To add more opening moves, update the `load_opening_book` function in `opening_book.c`:

```c
void load_opening_book() {
    initialize_opening_book();
    
    // Example: Adding a new opening move
    Move e4_e5 = {4, 6, 4, 4, {EMPTY, WHITE}};
    add_opening_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", e4_e5);

    // Add more opening moves as needed
}
```


### Asray_s_Chess_Engine_Analysis.pdf `Asray_s_Chess_Engine_Analysis.pdf`

Just an analysis of the engine

## Future Improvements

- **Advanced Evaluation Heuristics**: Enhance the evaluation function with more sophisticated heuristics like piece activity, control of the center, and endgame-specific considerations.
- **Endgame Tablebases**: Integrate endgame tablebases for perfect play in certain endgame scenarios.
- **GUI Integration**: Develop a graphical user interface to interact with the chess engine.
- **Opening Book Expansion**: Expand the opening book with more moves for better early-game performance.
- **Logging and Debugging Tools**: Implement detailed logging and debugging tools to track the engine's decision-making process.

## Contributing

Feel free to submit issues, fork the repository, and send pull requests. Contributions are welcome!

## License

This project is licensed under the MIT License.
