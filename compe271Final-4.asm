.data

board: .space 256 # 8 rows * 8 columns * 4 bytes 
newline: .asciiz "\n"
space: .asciiz " "
player_move: .asciiz "Enter move :\n"
turn: .word 1 # 1 for White, 2 for Black
pieces: .asciiz " PRNBQKprnbqk" 
player_input: .space 8
error: .asciiz "Invalid input\n"
white_turn_msg: .asciiz "\nWhite's turn\n"
black_turn_msg: .asciiz "\nBlack's turn\n"
dice_roll_msg: .asciiz "your dice rolled a  "
piece_msg: .asciiz "your chosen piece to move is "
white_pieces: .asciiz "PRNBQK"
black_pieces: .asciiz "prnbqk"
dice_roll_result: .word 0
board_top_border: .asciiz  "\n+--+--+--+--+--+--+--+--+\n"
board_bottom_border: .asciiz " +--+--+--+--+--+--+--+--+\n"
row_seperation: .asciiz " |"
col_seperation: .asciiz " |"
column_letters: .asciiz " a  b  c  d  e  f  g  h\n"

.text

.globl main  

main:
    jal start_board
    jal game_loop


game_loop:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    jal process_turn

    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

process_turn:

    addi $sp, $sp, -4
    sw $ra, 0($sp)

    jal display_board
    jal display_turn
    jal roll_dice

    li $v0, 4
    la $a0, player_move
    syscall

    la $a0, player_input
    li $a1, 16          #takes players input, reads it, and stores
    li $v0, 8
    syscall

    la $a0, player_input
    jal convert_input

    beq $v0, $zero, invalid_input

    move $a0, $s0
    move $a1, $s1  #players move
    move $a2, $s2
    move $a3, $s3
    jal make_move

    lw $t0, turn
    li $t1, 3         #turn switch 
    sub $t0, $t1, $t0
    sw $t0, turn

    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

invalid_input:
    li $v0, 4
    la $a0, error
    syscall
    j process_turn
    
display_turn:

    lw $t0, turn  #displays whos turn
    li $v0, 4 
    beq $t0, 1, white_turn
    la $a0, black_turn_msg
    j print_turn
    
white_turn:

    la $a0, white_turn_msg
    
print_turn:
    syscall
    jr $ra


roll_dice:

    li $a1, 6  #random number gen
    li $v0, 42
    syscall
    addi $a0, $a0, 1  
    move $t0, $a0     # Save dice roll
    sw $t0, dice_roll_result 

  
    li $v0, 4  #dice roll message
    la $a0, dice_roll_msg
    syscall

   
    li $v0, 1   # what number you rolled
    move $a0, $t0
    syscall

 
    li $v0, 4
    la $a0, newline
    syscall

 
    li $v0, 4  #what piece you got
    la $a0, piece_msg
    syscall

  
    lw $t1, turn  #get that piece
    la $t2, white_pieces   # Conditional Branch
    beq $t1, 2, black_piece
    j get_piece
    
black_piece:

    la $t2, black_pieces
    
get_piece:
    addi $t0, $t0, -1  
    add $t2, $t2, $t0
    lb $a0, ($t2)

  
    li $v0, 11   # Print piece
    syscall


    li $v0, 4
    la $a0, newline
    syscall

    jr $ra
###  https://openai.com/chatgpt/
start_board:
    la $t0, board

    # White pieces
    li $t1, 2
    sw $t1, 0($t0) # Rook
    sw $t1, 28($t0) # Rook

    li $t1, 3
    sw $t1, 4($t0) # Knight
    sw $t1, 24($t0) # Knight

    li $t1, 4
    sw $t1, 8($t0) # Bishop
    sw $t1, 20($t0) # Bishop

    li $t1, 5
    sw $t1, 12($t0) # Queen

    li $t1, 6
    sw $t1, 16($t0) # King

    li $t1, 1
    sw $t1, 32($t0) # Pawns
    sw $t1, 36($t0)
    sw $t1, 40($t0)
    sw $t1, 44($t0)
    sw $t1, 48($t0)
    sw $t1, 52($t0)
    sw $t1, 56($t0)
    sw $t1, 60($t0)

    # Black pieces
    li $t1, 8
    sw $t1, 224($t0) # Rook
    sw $t1, 252($t0) # Rook

    li $t1, 9
    sw $t1, 228($t0) # Knight
    sw $t1, 248($t0) # Knight

    li $t1, 10
    sw $t1, 232($t0) # Bishop
    sw $t1, 244($t0) # Bishop

    li $t1, 11
    sw $t1, 236($t0) # Queen

    li $t1, 12
    sw $t1, 240($t0) # King

    li $t1, 7
    sw $t1, 192($t0) # Pawns
    sw $t1, 196($t0)
    sw $t1, 200($t0)
    sw $t1, 204($t0)
    sw $t1, 208($t0)
    sw $t1, 212($t0)
    sw $t1, 216($t0)
    sw $t1, 220($t0)

    jr $ra
### end of copied code 
display_board:

    li $t0, 0 # row 
    la $t1, board

    li $v0, 4   #Print top border
    la $a0, board_top_border
    syscall

display_loop_row:

    li $v0, 1      # Print row number  Nested Loop
    li $t9, 8
    sub $a0, $t9, $t0
    syscall


    li $v0, 4      # Print seperastion
    la $a0, row_seperation
    syscall

    li $t2, 0 # column counter

display_loop_col:

    lw $t3, ($t1) # Load piece ,  Nested Loop
    la $t4, pieces
    add $t4, $t4, $t3
    lb $a0, ($t4) # Load piece character

    li $v0, 11
    syscall

  
    li $v0, 4
    la $a0, col_seperation
    syscall

    addi $t1, $t1, 4 # Next board puece
    addi $t2, $t2, 1 # Increment column
    blt $t2, 8, display_loop_col


    li $v0, 4
    la $a0, newline
    syscall

    addi $t0, $t0, 1 # Increment row
    blt $t0, 8, display_loop_row


    li $v0, 4    # Print bottom border
    la $a0, board_bottom_border
    syscall

    
    la $a0, column_letters  # Print column letters
    syscall 

    jr $ra

make_move:

    addi $sp, $sp, -4
    sw $ra, 0($sp)

    la $t0, board
   
    mul $t1, $a0, 32 # row * 8 * 4 (4 bytes)
    mul $t2, $a1, 4 # column * 4
    add $t1, $t1, $t2 
    add $t1, $t1, $t0 

    lw $t3, ($t1)

    lw $t4, dice_roll_result

    lw $t5, turn
    la $t6, white_pieces
    beq $t5, 2, get_black_piece
    j get_white_piece

get_black_piece:
    la $t6, black_pieces

get_white_piece:
    addi $t4, $t4, -1
    add $t6, $t6, $t4
    lb $t7, ($t6)

    lb $t8, pieces($t3)
    bne $t7, $t8, invalid_piece

    mul $t4, $a2, 32
    mul $t5, $a3, 4
    add $t4, $t4, $t5 
    add $t4, $t4, $t0 

    sw $t3, ($t4)
    sw $zero, ($t1) 


    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

invalid_piece:
    li $v0, 4
    la $a0, error
    syscall
    
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

convert_input:
    la $t0, player_input
    li $v0, 1  

    lb $t1, 0($t0)  # Load column letter
    lb $t2, 1($t0)  # Load row number

    subi $t1, $t1, 'a'   # Convert column letter to number (0-7)
    bltz $t1, invalid_char #sub acsll value of a
    bgt $t1, 7, invalid_char
    move $s1, $t1  

   
    subi $t2, $t2, '1'    # Convert row number to number (0-7)
    bltz $t2, invalid_char #sub acsll value of 1
    bgt $t2, 7, invalid_char
    li $t3, 7
    sub $s0, $t3, $t2  

   
    lb $t1, 2($t0) #check if space
    bne $t1, ' ', invalid_char


    lb $t1, 3($t0)  # Load column letter
    lb $t2, 4($t0)  # Load row number

    subi $t1, $t1, 'a'
    bltz $t1, invalid_char
    bgt $t1, 7, invalid_char
    move $s3, $t1  

    subi $t2, $t2, '1'
    bltz $t2, invalid_char
    bgt $t2, 7, invalid_char
    li $t3, 7
    sub $s2, $t3, $t2  

    jr $ra

invalid_char:
    li $v0, 0  # Invalid input
    jr $ra
