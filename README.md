Dice Chess - C and MIPS Implementations

Dice Chess is a command-line variation of chess in which every turn begins with a six-sided die roll. The result determines which type of piece the current player must move, adding an element of chance to the strategy of traditional chess.

This repository contains two versions of the project:

A C implementation with an in-memory board, piece-specific movement rules, turn handling, captures, and early check/checkmate logic.

A MIPS assembly implementation focused on board representation, console display, coordinate parsing, random piece selection, turn switching, and board updates.

How the Game Works

At the start of each turn, the program rolls a value from 1 to 6:

Roll

Required piece

1

Pawn

2

Knight

3

Bishop

4

Rook

5

Queen

6

King

The player must then enter a move using chessboard coordinates. For example:

e2 e4

This moves the piece on e2 to e4, provided that it belongs to the current player, matches the rolled piece type, and passes the validation implemented by that version.

Features

C version

Initializes and displays a standard 8 x 8 chessboard

Represents pieces with structures and enumerated piece types

Alternates between White and Black turns

Uses a random die roll to select the required piece type

Parses algebraic-style coordinates such as e2 e4

Implements movement checks for pawns, knights, bishops, rooks, queens, and kings

Supports captures and prevents most blocked sliding-piece moves

Includes experimental check and checkmate detection

MIPS version

Stores the chessboard as a 256-byte, word-based array

Initializes both players' pieces in their starting positions

Displays the board with ranks, files, borders, and piece symbols

Uses MARS random-number syscalls to generate the die roll

Parses and validates coordinate input

Ensures that the selected piece matches the rolled piece type

Moves pieces, updates the board, and alternates turns

Running the Project

C

Compile the C source with GCC or Clang. Replace <source-file>.c with the filename used in this repository:

gcc -std=c11 -Wall -Wextra <source-file>.c -o dice-chess
./dice-chess

MIPS

The assembly version is designed for the MARS MIPS simulator, since it uses MARS-specific syscalls such as syscall 42 for random integer generation.

Open the .asm file in MARS.

Assemble the program.

Run it from the MARS console.

Enter moves in the format e2 e4 when prompted.

Board Representation

The C version stores each square as a chesspiece structure containing a piece type and color. The MIPS version stores one numeric piece identifier per 32-bit word in a contiguous 8 x 8 board array. Both versions translate those internal values into familiar chess symbols when printing the board:

Uppercase letters represent White pieces.

Lowercase letters represent Black pieces.

P, N, B, R, Q, and K represent the six piece types.

Current Limitations

This project is an educational implementation and is not yet a complete chess engine.

Some movement, capture, check, and checkmate edge cases in the C version require further testing and correction.

The MIPS version validates the input format and rolled piece type but does not fully enforce every chess movement rule.

Castling, en passant, pawn promotion, stalemate, draws, and advanced game-state rules are not implemented.

A player may roll a piece type that has no legal move; reroll or turn-skipping behavior has not yet been formalized.

Possible Improvements

Complete and test all piece-movement validation

Prevent moves that leave the current player's king in check

Add robust checkmate and stalemate detection

Handle rolls for which no legal move exists

Add pawn promotion, castling, and en passant

Split the C version into smaller source and header files

Add automated tests for coordinate conversion, board updates, and legal moves

Bring the C and MIPS versions to feature parity

What I Learned

This project provided practice with translating the same game design between a high-level language and assembly. The C version emphasizes data structures and modular movement logic, while the MIPS version makes memory layout, register use, stack management, branching, syscalls, and coordinate conversion explicit.

License
