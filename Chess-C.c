#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define board_size 8

typedef enum {
    empty, pawn, knight, bishop, rook, queen, king
} 
    piece;

typedef struct {
    piece type;bool color;
    }
    chesspiece;

chesspiece board[board_size][board_size];
  
  ///https://openai.com/chatgpt/
void start_board() {
    for (int row = 0; row < board_size; row++) {
        for (int col = 0; col < board_size; col++) {
            board[row][col].type = empty;
            
        }
    }

    for (int col = 0; col < board_size; col++) {
        board[1][col].type = pawn;
        board[1][col].color = false; // black 
        board[6][col].type = pawn;
        board[6][col].color = true;  // white 
    }

    piece pieces[] = {rook, knight, bishop, queen, king, bishop, knight, rook};
    for (int col = 0; col < board_size; col++) {
        board[0][col].type = pieces[col];
        board[0][col].color = false; // black
        board[7][col].type = pieces[col];
        board[7][col].color = true;  // white 
    }
}

void print_board() {
    printf("\n  a b c d e f g h\n");
    printf(" +-----------------\n");
    for (int row = 0; row < board_size; row++) {
        printf("%d| ", 8 - row);
        for (int col = 0; col < board_size; col++) {
            char piece = ' ';
            if (board[row][col].type != empty) {
                switch (board[row][col].type) {
                    case pawn:
                        piece = 'P';
                        break;
                    case knight:
                        piece = 'N';
                        break;
                    case bishop:
                        piece = 'B';
                        break;
                    case rook:
                        piece = 'R';
                        break;
                    case queen:
                        piece = 'Q';
                        break;
                    case king:
                        piece = 'K';
                        break;
                    default:
                        break;
                }
                if (!board[row][col].color) {
                    piece = tolower(piece);
                }
            }
            printf("%c ", piece);
        }
        printf("|\n");
    }
    printf(" +-----------------\n");
}
/// end of copied code
int 
file (char file) 
 {			// character to column   
  if (file >= 'a' && file <= 'h')
	  
{
 
return file - 'a';	// Convert 
		}
		else
		
		{
return -1;			//invalid input
		}
}
int 
rank (char rank) 
		{ 
if (rank >= '1' && rank <= '8') 
 {
return '8' - rank; 
 
}
													else
{											
 
return -1; 
}										
}
		

bool within_board(int row, int col) {
    return row >= 0 && row < board_size && col >= 0 && col < board_size;
}

bool valid_move(chesspiece piece, int start_row, int start_col, int end_row, int end_col) {
    if (!within_board(end_row, end_col)) {
        return false;
    }
    
    if (start_row == end_row && start_col == end_col) {
        return false;
    }
    if (board[end_row][end_col].type != empty && board[end_row][end_col].color == piece.color) {
        if (board[end_row][end_col].type != king) {
            return true; //friendly fire
        } else {
            return false; 
        }
    }

    switch (piece.type) {
        case pawn:
        
            if (end_col == start_col && board[end_row][end_col].type == empty) {
                if (piece.color) { // White 
                    if (end_row == start_row - 1) {
                        return true;
                    } else if (start_row == 6 && end_row == 4 && board[5][end_col].type == empty) {
                        return true; 
                    }
                } else { // Black 
                    if (end_row == start_row + 1) {
                        return true;
                    } else if (start_row == 1 && end_row == 3 && board[2][end_col].type == empty) {
                        return true; 
                    }
                }
            }
            if (abs(end_col - start_col) == 1) {
                if (piece.color) { // White 
                    if (end_row == start_row - 1 && board[end_row][end_col].type != empty && !board[end_row][end_col].color) {
                        return true;
                    }
                } else { // Black 
                    if (end_row == start_row + 1 && board[end_row][end_col].type != empty && board[end_row][end_col].color) {
                        return true;
                    }
                }
            }
            break;
        case knight:
        
            if ((abs(end_row - start_row) == 2 && abs(end_col - start_col) == 1) ||
                (abs(end_row - start_row) == 1 && abs(end_col - start_col) == 2)) {
                return true;
            }
            break;
        case bishop:
        
            if (abs(end_row - start_row) == abs(end_col - start_col)) {
            int direct_row;
            if (end_row > start_row) {
                 direct_row = 1;
                } else {
                 direct_row = -1;
                }
            int direct_col;
            if (end_col > start_col) {
                  direct_col = 1;
            } else {
              direct_col = -1;
                }   
                for (int i = 1; i < abs(end_row - start_row); i++) {
                    if (board[start_row + i * direct_row][start_col + i * direct_col].type != empty) {
                        return false;
                    }
                }
                return true;
            }
            break;
        case rook:
        
            if (start_row == end_row || start_col == end_col) {
                if (start_row == end_row) {
             int direct_col;
            if (end_col > start_col) {
             direct_col = 1;
            } else{
            direct_col = -1;
             }
                    for (int i = 1; i < abs(end_col - start_col); i++) {
                        if (board[start_row][start_col + i * direct_col].type != empty) {
                            return false;
                        }
                    }
                } else { //diagonal
                 int direct_row;
                if (end_row > start_row) {
                 direct_row = 1;
                } else {
                  direct_row = -1;
                    }
                    for (int i = 1; i < abs(end_row - start_row); i++) {
                        if (board[start_row + i * direct_row][start_col].type != empty) {
                            return false;
                        }
                    }
                }
                return true;
            }
            break;
        case queen:

            if ((start_row == end_row || start_col == end_col) || (abs(end_row - start_row) == abs(end_col - start_col))) {
                if (start_row == end_row) {
                  int direct_col;
            if (end_col > start_col) {
                 direct_col = 1;
                    } else {
                    direct_col = -1;
                    }
                    for (int i = 1; i < abs(end_col - start_col); i++) {
                        if (board[start_row][start_col + i * start_col].type != empty) {
                            return false;
                        }
                    }
                } else if (start_col == end_col) {
                    int direct_row;
                    if (end_row > start_row) {
                  direct_row = 1;
                    } else {
                   direct_row = -1;
                    }
                    for (int i = 1; i < abs(end_row - start_row); i++) {
                        if (board[start_row + i * direct_row][start_col].type != empty) {
                            return false;
                        }
                    }
                } else { 
                     int direct_row;
                    if (end_row > start_row) {
                     direct_row = 1;
                    } else {
                 direct_row = -1;
                    }
                    int direct_col;
                if (end_col > start_col) {
                direct_col = 1;
                } else {
             direct_col = -1;
                    }
                    for (int i = 1; i < abs(end_row - start_row); i++) {
                        if (board[start_row + i * direct_row][start_col + i * direct_col].type != empty) {
                            return false;
                        }
                    }
                }
                return true;
            }
            break;
        case king:
        
            if (abs(end_row - start_row) <= 1 && abs(end_col - start_col) <= 1) {
                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

void move_piece(int start_row, int start_col, int end_row, int end_col) {
    board[end_row][end_col] = board[start_row][start_col];
    board[start_row][start_col].type = empty;
}

 is_in_check(bool color) {
    int king_row, king_col;
    piece king_type; 
        if (color) {
    king_type = king; 
}   else if (!color) { 
     king_type = king + 6; 
        }
    for (int row = 0; row < board_size; row++) {
        for (int col = 0; col < board_size; col++) {
            if (board[row][col].type == king_type && board[row][col].color == color) {
                king_row = row;
                king_col = col;
                break;
            }
        }
    }

    for (int row = 0; row < board_size; row++) {
        for (int col = 0; col < board_size; col++) {
            if (board[row][col].type != empty && board[row][col].color != color) {
                if (valid_move(board[row][col], row, col, king_row, king_col)) {
                    return true;
                }
            }
        }
    }
    return false;
}

 checkmate(bool color) {

    if (!is_in_check(color)) {
        return false;
    }

    int king_row, king_col;
   piece king_type; 
if (color) {
    king_type = king; 
  }     else {
     king_type = king + 6; 
}
    for (int row = 0; row < board_size; row++) {
        for (int col = 0; col < board_size; col++) {
            if (board[row][col].type == king_type && board[row][col].color == color) {
                king_row = row;
                king_col = col;
                break;
            }
        }
    }
    for (int row = 0; row < board_size; row++) {
        for (int col = 0; col < board_size; col++) {
            if (board[row][col].type != empty && board[row][col].color != color) {
                if (valid_move(board[row][col], row, col, king_row, king_col)) {
                    return false;
                }
            }
        }
    }
    for (int start_row = 0; start_row < board_size; start_row++) {
        for (int start_col = 0; start_col < board_size; start_col++) {
            if (board[start_row][start_col].type != empty && board[start_row][start_col].color == color) {
                for (int end_row = 0; end_row < board_size; end_row++) {
                    for (int end_col = 0; end_col < board_size; end_col++) {
                        if (valid_move(board[start_row][start_col], start_row, start_col, end_row, end_col)) {
                            chesspiece original_piece = board[end_row][end_col];
                            move_piece(start_row, start_col, end_row, end_col);
                            bool check_avoided = !is_in_check(color);
                            move_piece(end_row, end_col, start_row, start_col);
                            board[end_row][end_col] = original_piece;

                            if (check_avoided) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}
// Roll a 4-sided dice
int roll_dice() {
    return rand() % 6 + 1;
}

int main() {
    bool turn = true; // true = white and false = black
    bool game_over = false;
    char move[6];
    srand(time(NULL)); 

    start_board();
    while (!game_over) {
        print_board();

        if (turn) {
            printf("\nWhite's turn: ");
        } else {
            printf("\nBlack's turn: ");
        }
        int dice_result = roll_dice();
        printf("You rolled a %d.\n", dice_result);
        piece piece_to_move;
        switch (dice_result) {
            case 1:
                piece_to_move = pawn; //1=pawn,2=knight,3=bishop,4=rook,5=queen,6=king
                break;
            case 2:
                piece_to_move = knight;
                break;
            case 3:
                piece_to_move = bishop;
                break;
            case 4:
                piece_to_move = rook;
                break;
           case 5:
                piece_to_move = queen;
                break;
           case 6:
                piece_to_move = king;
                break;
        }
        fgets(move, sizeof(move), stdin);
        move[strcspn(move, "\n")] = '\0'; 

        char start_file = move[0];
        char start_rank = move[1];
        char end_file = move[3];
        char end_rank = move[4];

        int start_col = file(start_file);
        int start_row = rank(start_rank);
        int end_col = file(end_file);
        int end_row = rank(end_rank);

        if (within_board(start_row, start_col) && within_board(end_row, end_col) &&
            board[start_row][start_col].type == piece_to_move && board[start_row][start_col].color == turn &&
            valid_move(board[start_row][start_col], start_row, start_col, end_row, end_col)) {
            move_piece(start_row, start_col, end_row, end_col);
            if (checkmate(turn)) {
                print_board();
       if (turn) {
     printf("\nCheckmate White wins.\n");
        }       else {
    printf("\nCheckmate Black wins.\n");
        }
                game_over = true;
            } else {
                turn = !turn;
            }
        } else {
            printf("\nincorrect move\n");
        }
    }

    return 0;
}


