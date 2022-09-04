#include "stm32f769xx.h"
#include "maze.h"

#include<stdint.h>

typedef struct Player{
	char name;
	int x_pos;
	int y_pos;
} player;

void move(player p, int x, int y){
	p.x_pos = x;
	p.y_pos = y;
}

int** create_map(){

	//store a copy of the board in memory to check if that location is valid
	int **board = (int**)calloc(num_rows, sizeof(int*));
	for (int i = 0; i<num_rows; i++){
		board[i] = (int*)calloc(num_cols, sizeof(int));
	} //already initialized to zeros!

	// generate maze
	/*
	 *  TO DO!!!!!!!!!!
	 */

	return board;
}


//make sure char is either WASD or <ESC>
int valid_char(char c){
	//          <ESC>	 A		 D		 S		 W		 a		 d 		 s		 w
	if (move != (0x1b || 0x41 || 0x44 || 0x53 || 0x57 || 0x61 || 0x64 || 0x73 || 0x77)){
		return false;
	}
	return true;
}

void maze_game(){
	//initialize game screen
	int start_row = 7;
	int end_row = 18;
	int start_col = 30;
	int num_rows = end_row-start_row-1;
	int num_cols = 10;
	printf("\033[2J\033[40;31m"); // Erase screen & move cursor to home position
	fflush(stdout);

	//draw square (board)
	printf("\033[%d;%dH*--------------------*\n", start_row, start_col);
	for (int i = start_row+1; i<end_row; i++){
		printf("\033[%d;%dH|                    |", i, start_col);
	}
	printf("\033[%d;%dH*--------------------*\n", end_row, start_col);



	//initialize player
	printf("\033[20;%dHEnter Name: ",start_col);
	fflush(stdout);
	char name;
	name = getchar();
	player P;
	P.name = name;
	P.x_pos = start_row+1;
	P.y_pos = start_col+1;

	printf("\033[%d;%dH%c", start_row+1, start_col+1, P.name);
	fflush(stdout);

	int** board = create_map();

	//accept inputs (accept hard reset (button)
	while(1){
		printf("\033[20;%dHWASD to move: ",start_col);
		fflush(stdout);

		//asks for a character until valid
		do {
			char move;
			move = getchar();
		} while(valid_char(move));

		//break if reached the end
		break;
	}
	//output

}
