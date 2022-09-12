#include "stm32f769xx.h"
#include "maze.h"

#include<stdint.h>
#include<stdlib.h>
#include<math.h>

typedef struct Player{
	char name;
	int x_pos;
	int y_pos;
} player;

void move(player p, int x, int y){
	p.x_pos = x;
	p.y_pos = y;
}

int** create_map(int num_rows, int num_cols, int generate_maze){

	//store a copy of the board in memory to check if that location is valid
	int **board = (int**)calloc(num_rows, sizeof(int*));
	for (int i = 0; i<num_rows; i++){
		board[i] = (int*)calloc(num_cols, sizeof(int));
	} //already initialized to zeros!

	// generate maze
	if (generate_maze == 1){
		for (int i = 0; i<num_rows; i++){
			for (int j = 0; j<floor(num_cols/5); j++){
				int location = rand()%num_cols+1;
				if (i==0&&location==1) continue;
				board[i][location-1]=1;
			}
		}
	}

	return board;
}

void free_board(int **board, int num_rows){
	for(int i = 0; i<num_rows; i++){
		free(board[i]);
	}
	free(board);
}

//check if the move is a valid move
void check_and_move(int** board, char move, player *P, int num_rows, int num_cols, int start_row, int start_col){
	int curr_x = P->x_pos-start_row, curr_y = P->y_pos-start_col;
	int new_x = curr_x, new_y = curr_y;
	if (move == 0x41 || move == 0x61) new_y--; 		//A
	else if (move == 0x44 || move == 0x64) new_y++; //D
	else if (move == 0x53 || move == 0x73) new_x++; //S
	else if (move == 0x57 || move == 0x77) new_x--; //W

	//check if out of bounds, check if there's a wall
	printf("\033[21H\033[2K\033[21;%dH%d, %d", start_col, new_x, new_y);
	fflush(stdout);


	if (new_x >= num_rows || new_y >= num_cols || new_x<0 || new_y<0 || board[new_x][new_y] == 1){
		printf("\033[21H\033[2K\033[21;%dHThat's a wall! %d, %d", start_col, new_x, new_y);
		fflush(stdout);
		return;
	}
	printf("\033[23H\033[2K\033[21;%dH%d, %d board value: %d", start_col, new_x, new_y, board[new_x][new_y]);
	fflush(stdout);
	P->x_pos = new_x + start_row;
	P->y_pos = new_y + start_col;
}

void GPIO_Init(){
	GPIO_InitTypeDef init_struct;
	//modes for LED
	init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	init_struct.Pin = GPIO_PIN_5;
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	HAL_GPIO_Init(GPIOJ, &init_struct);

	//initialize blue push-button
	init_struct.Mode = GPIO_MODE_INPUT;
	init_struct.Pin = GPIO_PIN_0;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &init_struct);

}

void maze_game(){
	//initialize game screen
	int start_row = 7;
	int end_row = 18;
	int start_col = 30;
	int num_rows = 10;
	int num_cols = 20;
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
	P.x_pos = start_row;
	P.y_pos = start_col;

	//print starting location and print cursor
	printf("\033[%d;%dH%c\033[s", P.x_pos+1, P.y_pos+1, P.name);
	fflush(stdout);

	//board has 1s at locations with walls.
	int** board = create_map(num_rows, num_cols, 1);
	//prints walls 50-50 to be | or -
	for(int i = 0; i<num_rows; i++){
		for (int j = 0; j<num_cols; j++){
			if (board[i][j] == 0 ) continue;
			char wall;
			wall = (rand()%2 == 1)?'|':'-';
			printf("\033[%d;%dH%c", start_row+i+1, start_col+j+1, wall);
			fflush(stdout);
		}
	}

	//set up GPIO and turn off LED
	GPIO_Init();
	HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_5, GPIO_PIN_RESET);
	//accept inputs (accept hard reset (button)
	char move;
	int reset_flag = 0;
	while(1){
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET){
			reset_flag = 1;
		}
		if (reset_flag == 1){
			P.x_pos = start_row;
			P.y_pos = start_col;
			reset_flag = 0;
		}

		printf("\033[20;%dHWASD to move: ",start_col);
		fflush(stdout);

		//asks for a character until valid
		//reset is stuck on this!!! need an interrupt
		move = getchar();
		printf("\033[20;%dH%c\n", start_col+14, move);
		if (move == (0x1b) || move == (0x41) || move == (0x44) || move == (0x53) || move == (0x57) ||
			move == (0x61) || move == (0x64) || move == (0x73) || move == (0x77)){
			printf("\033[21;%dHGreat Success!",start_col);
			fflush(stdout);
		}
		else{
			printf("\033[21;%dHInvalid Move  \033[20,%dH",start_col, start_col+13);
			fflush(stdout);
			continue;
		}

		if (move == 0x1b){
			printf("\033[2J\033[12;38HDONE");
			fflush(stdout);
			break;
		}
		//check if move is valid, bumps into walls and moves it if its a valid move
		check_and_move(board, move, &P, num_rows, num_cols, start_row, start_col);
		//check if (reached end of the maze)
		printf("\033[u\033[1D \033[%d;%dH%c\033[s", P.x_pos+1, P.y_pos+1, P.name);
		fflush(stdout);
		//go to next position
		if (P.x_pos == start_row + num_rows-1 && P.y_pos == start_col + num_cols-1){
			printf("\033[21;%dHFINISHED!            ",start_col);
			HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_5, GPIO_PIN_SET);
			fflush(stdout);
			break;
		}
		//break if reached the end
	}

	/*
	 * TO-DO: SETUP BUTTON, SET UP LED WHEN FINISHED
	 */
	//output
	//free board
	free_board(board, num_rows);

}
