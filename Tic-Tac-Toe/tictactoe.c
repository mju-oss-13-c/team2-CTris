/********************************************************************
 ** Program Filename:tictactoe.c
 ** Author: Christopher Harper
 ** Date: 5/29/12
 ** Description: Play a game of tictactoe
 ** Input: 1 or 2 players, players' pieces, position selection
 ** Output: rendered board, error and outcome messages
 *********************************************************************/



#include <stdio.h>
#include <string.h>

void players(int*);
void character(int, char*, char*);
void clear_array(char [*][3]);
void render_board(char [*][3]);
void enter_turn(int*, int*, int*, char[*][3], int);
void ai_move(int*, int*);
int valid_move(int, int, char[*][3]);
int occupied(int, int, char[*][3]);
void turn_to_board(int, int, char [*][3], int*, char, char);
int completion(char [*][3], char, char);
int winner(char[*][3], char, char);
int board_full(char[*][3]);
int check_rows(char[*][3], char, char);
int check_columns(char[*][3], char, char);
int check_diagonals(char[*][3], char, char);
int diagonal1(char[*][3], char, char);
int diagonal2(char[*][3], char, char);


struct tic_tac_toe{
	char board[3][3];
	char player1;
	char player2;
	int player_select;
	int turn;
	int row;
	int column;
};


int main(){
	int repeat_game = 1; //index variable

	/*Setup the game*/
	struct tic_tac_toe setup;
	setup.turn = 1;
	clear_array(setup.board);
	players(&setup.player_select);
	character(setup.player_select, &setup.player1, &setup.player2);
	
	/*Play the game until finished*/
	while(repeat_game == 1){
		render_board(setup.board);
		enter_turn(&setup.turn, &setup.row, &setup.column, setup.board, setup.player_select);
		turn_to_board(setup.row, setup.column, setup.board, &setup.turn, setup.player1, setup.player2);
		repeat_game = completion(setup.board, setup.player1, setup.player2);
	}
	return 0;
}




/*Clear the array of initial garbage and set to a space*/

void clear_array(char board[3][3]){
	memset(&board[0][0],' ',sizeof(board));
	board[2][2] = ' ';
}



/*Determine if playing against another human or computer*/

void players(int* player_select){
	int playerIndex = 0;        //index variable
	//int player_select;
	while(playerIndex == 0){
		printf("Would you like to play against\n"
				"1. Another player\n"
				"2. The computer\n");
		scanf("%d%*c",player_select);
		if(*player_select == 1 || *player_select == 2)
			playerIndex++;
		else
			printf("Invalid selection\n");
	}
}




/*Set player characters*/


void character(int player_select, char* player1, char* player2   ){
	int charIndex = 1; //index variable
	while(charIndex == 1){
		printf("Player 1 select your character(X/O)");
		scanf("%c", player1);	

		if(*player1 == 'X' || *player1 == 'x'){
			*player1 = 'X';
			printf("Player 2 is O\n");
			*player2 = 'O';
			charIndex = 0;
		}
		else if(*player1 == 'O' || *player1 == 'o'){
			*player1 = 'O';
			printf("Player 2 is X\n");
			*player2 = 'X';
			charIndex = 0;
		}
		else
			printf("You have entered an invalid selection\n");
	}
}



/*Render the board with any inputs*/

void render_board(char board[3][3]){
	int renIndex; //index variable

	for(renIndex = 0; renIndex <= 2; renIndex++){
		printf("  %c  |  %c  |  %c  \n", board[renIndex][0], board[renIndex][1], board[renIndex][2]);
		if(renIndex != 2) // make sure the board render is 3x3
			printf("-----------------\n");
	}
}



/*Take user's move*/

void enter_turn(int* turn, int* row, int* column, char board[3][3],int player_select){
	int turnIndex = 1; //index variable while
	//int k;     //index variable for
	int row_check = 1;
	int column_check = 1;
	while(turnIndex == 1){
		if(*turn % 2 == 1){
			printf("Player 1 enter your move (row column)");
			scanf("%d %d",row, column);
		}
		else {
			printf("Player 2 enter your move (row column)");
			if(player_select == 1)
				scanf("%d %d",row, column);
			else{
				ai_move(row, column);
				printf("%d, %d\n",*row, *column);   //Show AI move
			}
		}
		
		turnIndex = valid_move(*row, *column, board);       //break-out of loop if valid_move returns no problems (0)
		printf("\n");
	}	
}


/*Generate random move for computer*/

void ai_move(int* row, int* column){
	*row = (rand() % 3) + 1;
	*column = (rand() % 3) + 1;
}


/*Check if move is valid*/

int valid_move(int row, int column, char board[3][3]){
	int gridIndex; //index variable
	int problem;
	int row_check = 1;
	int column_check = 1;

	/*Check if selection is in grid*/
	for(gridIndex = 1; gridIndex <= 3; gridIndex++){
		if( row == gridIndex)
			row_check = 0;
		if( column == gridIndex)
			column_check = 0;
	}

	/*Check for parameter errors*/
	if( row_check == 1 || column_check == 1){
		printf("Invalid entry\n");
		problem = 1;
	}
	/*Check for occupation errors*/
	else if(occupied(row, column, board) == 1){
		printf("Space occupied\n");
		problem = 1;
	}
	else
		problem = 0;
	return problem;	
}


/*Checks if space is already occupied*/

int occupied(int row, int column, char board[3][3]){
	int problem; //return variable
	if(board[row -1][column - 1] !=' ')
		problem = 1;
	else
		problem = 0;
	return problem;
}



/*Injects move into board array*/

void turn_to_board(int row, int column, char board[3][3], int* turn, char player1, char player2){
	
	if(*turn % 2 == 1)
		board[row - 1][column - 1] = player1;
	else
		board[row - 1][column - 1] = player2;
	*turn += 1;
}


/*Check if game is finished*/

int completion(char board[3][3], char player1, char player2){
	int complete = 1; //return variable

	/*Check for winner*/
	if(winner(board, player1, player2) == 0)
		complete = 0;

	/*Check for full board*/		
	else if (board_full(board) == 0){
		printf("No winner \n");
		complete = 0;
	}
	return complete;
}


/*Check for winner*/

int winner(char board[3][3], char player1, char player2){
	int rowWin = 1; //math check
	int colWin = 1;
        int diagWin = 1;
	int winner = 1;     // there is no winner yet
	/*Check for wins*/
	rowWin = check_rows(board, player1, player2);
	colWin = check_columns(board, player1, player2);
        diagWin = check_diagonals(board, player1, player2);

	/*If there is a win set winner to true*/
	if(rowWin + colWin + diagWin != 3) 
		winner = 0;
    return winner;
}


/*Check rows for win*/

int check_rows(char board[3][3], char player1, char player2){
	int rowWin = 1; 
	int rowIndex; //index
	for(rowIndex = 0; rowIndex <= 2; rowIndex++){
		if(board[rowIndex][0] == board[rowIndex][1] && board[rowIndex][0] == board[rowIndex][2]){
			if(board[rowIndex][0] == player1){
				printf("Player 1 Wins! \n");
				rowWin = 0;  //A win has occured
			}
			else if(board[rowIndex][0] == player2){
				printf("Player 2 Wins! \n");
				rowWin = 0; //A win has occured
			}
		}
	}
	return rowWin;  //Return if there was a win in a row
}


/*Check columns for win*/

int check_columns(char board[3][3], char player1, char player2){
	int colWin = 1;
	int colIndex; //index
	for(colIndex = 0; colIndex <= 2; colIndex++){
		if(board[0][colIndex] == board [1][colIndex] && board[0][colIndex] == board[2][colIndex]){
			if(board[0][colIndex] == player1){
				printf("Player 1 Wins! \n");
				colWin = 0; //A win has occured
			}
			else if(board[0][colIndex] == player2){
				printf("Player 2 Wins! \n");
				colWin = 0; //A win has occured
			}
		}
	}
	return colWin;  //Return if there was a win in the column
}


/*Check diagonals for win*/

int check_diagonals(char board[3][3], char player1, char player2){
    int diagWin = 1; 
    int lTor = 1;
    int rTol = 1; 
    lTor = diagonal1(board, player1, player2);
    rTol = diagonal2(board, player1, player2);
    if(lTor + rTol != 2) // Check if either diagonal returned a win 
        diagWin = 0;
    return diagWin;
}


/*Check top left to bottom right diagonal*/

int diagonal1(char board[3][3], char player1, char player2){
    int win = 1; 
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        if(board[0][0] == player1){
            printf("Player 1 Wins!\n");
            win = 0;
        }
        else if(board[0][0] == player2){
            printf("Player 2 Wins!\n");
            win = 0;
        }
    }
    return win;
}


/*Check top right to bottom left diagonal*/

int diagonal2(char board[3][3], char player1, char player2){
    int win = 1;
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        if(board[0][2] == player1){
            printf("Player 1 Wins!\n");
            win = 0;
        }
        else if(board[0][2] == player2){
            printf("Player 2 Wins!\n");
            win = 0;
        }
    
    }
    return win;
}


/*Check if board is full*/

int board_full(char board[3][3]){
	int full = 0; //return
	int rowIndex; //index
	int colIndex; //index 2
	/*Check every row and then check every column in that row for a space, if it finds one the board isn't full*/
	for(rowIndex = 0; rowIndex <= 2; rowIndex++){
		for(colIndex = 0; colIndex <= 2; colIndex++){
			if(board[rowIndex][colIndex] == ' ')
				full = 1;
			}
	}
	return full;
}
