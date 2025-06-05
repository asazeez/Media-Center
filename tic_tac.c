#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include <stdlib.h>

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */
#define HEIGHT 9
#define WIDTH 20
#define EMPTY ' '
#define TUBE '*'
#define BIRD "O"

int grid[3][3];

void cursor_delay(int div){
	int i;
	int val = 10000000/div;
	int count;
	for (i = 0; i<val; i++){
		count ++;
	}
}

void init_grid(){
	int i;
	int j;
	for (i = 0; i<3; i++){
		for (j = 0; j<3; j++){
			grid[i][j] = 2;
		}
	}
}

int draw_symbol(int ln, int col, int x){
	GLCD_DisplayChar(ln, col ,1, ' ');
	if (x==1){
		GLCD_DisplayChar(ln, col, 1, 'X');
	}
	else {
		GLCD_DisplayChar(ln, col, 1, 'O');
	}
}

void draw_rows(){
	GLCD_SetTextColor(White);
	GLCD_DisplayString(3,0,1, "  ---------------- ");
	GLCD_DisplayString(6,0,1, "  ---------------- ");
}

void draw_columns(){
	int i;

	for (i = 1; i < 9 ; i++){
		GLCD_DisplayChar(i,6,1, '|');
	}
	for (i = 1; i < 9 ; i++){
		GLCD_DisplayChar(i,13,1, '|');
	}
}

int update_count(int count){
	int new_count; 
	if (count == 0){
		new_count = 1;
	}
	else {
		new_count = 0;
		}	
	return new_count;
}

int update_board(int col, int ln, int ln_num, int col_num, int count){
	int new_count;
	if (grid[ln][col] == 2){
		if (count==1){
			grid[ln][col] = 1;
		}
		else {
			grid[ln][col] = 0;
		}
		draw_symbol(ln_num, col_num, count);
		new_count = update_count(count);
	}
	else {
		GLCD_DisplayString(0, 0, 1, "Invalid move");
		new_count = count;
	}
	return new_count;
}

void move_cursor(int ln_pos, int prev_ln, int col_pos, int prev_col, int ln, int col){
	GLCD_DisplayChar(prev_ln, prev_col+1, 1, ' ');
	GLCD_DisplayChar(ln_pos, col_pos+1, 1, '*');
	cursor_delay(2);
}

int get_ln_pos(int ln){
	int ln_num;
	if (ln == 1){
			ln_num = 5; 
	}
	else if (ln == 0){
		ln_num = 2;
	}
	else if (ln == 2){
		ln_num = 8;
	}
	return ln_num;
}

int get_col_pos(int col){
	int col_num;
	if (col == 1){
			col_num = 9; 
	}
	else if (col == 0){
		col_num = 4;
	}
	else if (col == 2){
		col_num = 16;
	}
	return col_num;
}

int check_board(){
	int i;
	//check rows
	for (i = 0; i < 3; i++) { 
		if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) { 
			if (grid[i][0] == 1) 
				return 1;
			else if (grid[i][0] == 0) 
				return 0;
		} 
	} 	
	//check columns
	for (i = 0; i < 3; i++) { 
		if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) { 
			if (grid[0][i] == 1) 
				return 1;
			else if (grid[0][i] == 0) 
				return 0;
		} 
	} 	
	//check diagonals
	if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]){
		if (grid[0][0] == 1){
			return 1;
		}
		else if (grid[0][0] == 0){
			return 0;
		}
	}
	
	if (grid[0][2] == grid[1][1] && grid[1][1] == grid [2][0]){
		if (grid[0][2] == 1){
			return 1;
		}
		else if (grid[0][2] == 0){
			return 0;		
		}
	}
	return 2;
}

int check_board_empty(){
	int i;
	int j;
	int check = 0;
	for (i = 0; i<3; i++){
		for (j = 0; j<3; j++){
			if (grid[i][j] == 2){
				check = 1;
			}
		}
	}
	return check;
}

int tic_tac_game_over(int winner){
	int joystick_sel;
	int sel_num;
	GLCD_Clear(Purple);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0,1,"     GAME OVER     ");
	if (winner == 1){
		GLCD_DisplayString(1,0,1,"    Player 2 Wins    ");
	}
	else if (winner == 0){
		GLCD_DisplayString(1,0,1,"    Player 1 Wins    ");
	}
	else {
		GLCD_DisplayString(1,0,1,"      No Win      ");
	}
	GLCD_DisplayString(2, 0, 1, "   UP/DOWN - Scroll  ");
  GLCD_DisplayString(3, 0, 1, "   SELECT - Select   ");
	GLCD_DisplayString(5,0,1,"Replay");
	GLCD_DisplayString(6,0,1,"Exit");
	while(1){
		joystick_sel = get_button();
		if (sel_num == 0 || sel_num == 1){
			if (joystick_sel == KBD_DOWN){
				sel_num --;
			}
			else if (joystick_sel == KBD_UP){
				sel_num++;
			}
		}
		else {
			sel_num = 0;
		}
		
		if (sel_num == 0){
			GLCD_SetBackColor(LightGrey);
			GLCD_DisplayString(5,0,1,"Replay");
			GLCD_SetBackColor(Purple);
			GLCD_DisplayString(6,0,1,"Exit");
			joystick_sel = get_button();
			if (joystick_sel == KBD_SELECT){
				return 1;
			}
		}
		else if (sel_num == 1){
			GLCD_SetBackColor(Purple);
			GLCD_DisplayString(5,0,1,"Replay");
			GLCD_SetBackColor(LightGrey);
			GLCD_DisplayString(6,0,1,"Exit");
			joystick_sel = get_button();
			if (joystick_sel == KBD_SELECT){
				return 0;
			}
		}
	}
}

void restart_tic_tac(){
	tic_tac();
}

int tic_tac(){
	int joystick;
	int col_pos = 1;
	int ln_pos = 1;
	int prev_ln_pos = 1;
	int prev_col_pos = 1;
	int ln_num;
	int prev_ln_num;
	int col_num;
	int prev_col_num;
	int count = 0;
	int check;
	
	GLCD_Clear(Purple);
	init_grid();
	draw_rows();
	draw_columns();
	
	while(1){
		joystick = get_button();
		GLCD_ClearLn(0, 1);
		prev_col_pos = col_pos;
		prev_ln_pos  = ln_pos;
		if (check_board_empty() == 1){
			if (joystick == KBD_SELECT){
				count = update_board(col_pos, ln_pos, ln_num, col_num, count);
				cursor_delay(2);
				check = check_board();
				if (check == 1){
				if (tic_tac_game_over(1) == 1){
						restart_tic_tac();
						break;
					}
					else {
						return 0;
					}
				}
				else if (check == 0){
					if (tic_tac_game_over(1) == 1){
						restart_tic_tac();
						break;
					}
					else {
						return 0;
					}
				}
			}
			else {
				if (0 <= ln_pos && ln_pos <=2){
					if (joystick == KBD_DOWN){
						ln_pos++;
					}
					else if (joystick == KBD_UP){
						ln_pos--;
					}
				}
				else {
					ln_pos = 1;
				}
				if (0 <= col_pos && col_pos <= 2){
					if (joystick == KBD_LEFT){
						col_pos--;
					}
					else if (joystick == KBD_RIGHT){
						col_pos++;
					}
				}
				else {
					col_pos = 1;
				}
				prev_col_num = get_col_pos(prev_col_pos);
				prev_ln_num = get_ln_pos(prev_ln_pos);
				
				col_num = get_col_pos(col_pos);
				ln_num = get_ln_pos(ln_pos);
				
				move_cursor(ln_num, prev_ln_num, col_num, prev_col_num, ln_pos, col_pos);
			}
		} 
		else {
			check = check_board();
			if (tic_tac_game_over(check) == 1){
				restart_tic_tac();
				break;
			}
			else {
				return 0;
			}
		}
	}
	
}


