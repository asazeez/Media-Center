#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include <stdlib.h>
#include <stdio.h>

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */
#define HEIGHT 9
#define WIDTH 20
#define EMPTY ' '
#define TUBE '*'
#define BIRD "O"

int joystick_sel;
int bird_ln = 5;
int bird_col = 5;
int tube_col;
int up_tube_ln = 0;
int btm_tube_ln = 10;
int tube_width = 2;

void delay(int div){
	int i;
	int val = 10000000/div;
	int count;
	for (i = 0; i<val; i++){
		count ++;
	}
}

int get_tube_height(){
	int random_num = (rand() % 4) + 1;
	return random_num;
}

void draw_bird(int bird_ln){
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayChar(bird_ln, bird_col, 1, 'O');
}

void move_bird(int prev_ln){
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(prev_ln,bird_col,1,"  ");
}

void create_new_tube(int *tube_ln) {
    *tube_ln = 20; 
}

void place_tube(int ln_pos, int col_pos, int tube_height){
	int i;
	int j;
	for (i = col_pos; i < col_pos + tube_height; i++){
		for (j = ln_pos; j < ln_pos + tube_width; j++){
			GLCD_SetBackColor(Green);
			GLCD_SetTextColor(Green);
			GLCD_DisplayChar(i,j,1,0x2A);
		}
	}
}

void move_tube(int prev_ln, int tube_col, int tube_height){
	int i;
	int j;
		for (i = tube_col; i < tube_col + tube_height; i++){
			for (j = prev_ln; j < prev_ln + tube_width; j++){
				GLCD_SetBackColor(White);
				GLCD_DisplayChar(i,j,1,' ');
			}
		}	
		for (i = tube_col; i < tube_col + tube_height; i++){
			for (j = prev_ln - 1; j < prev_ln + tube_width - 1; j++){
				GLCD_SetBackColor(Green);
				GLCD_SetTextColor(Green);
				GLCD_DisplayChar(i,j,1, 0x2A);
			}
		}
}

int game_over(int score){
	int js_sel;
	int sel_num = 0;
	char score_str[20];
	sprintf(score_str, "      SCORE: %d      ", score);
	GLCD_Clear(Purple);
	GLCD_SetBackColor(Purple);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0,1,"     GAME OVER      ");
	GLCD_DisplayString(1,0,1, score_str);
	GLCD_DisplayString(2, 0, 1, "   UP/DOWN - Scroll  ");
  GLCD_DisplayString(3, 0, 1, "   SELECT - Select   ");
	while(1){
		js_sel = get_button();
		if (sel_num == 0 || sel_num == 1){
			if (js_sel == KBD_DOWN){
				sel_num++;
			}
			else if (js_sel == KBD_UP){
				sel_num--;
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
			js_sel = get_button();
			if (js_sel == KBD_SELECT){
				return 0;
			}
		}
		else if (sel_num == 1){
			GLCD_SetBackColor(Purple);
			GLCD_DisplayString(5,0,1,"Replay");
			GLCD_SetBackColor(LightGrey);
			GLCD_DisplayString(6,0,1,"Exit");
			js_sel = get_button();
			if (js_sel == KBD_SELECT){
				return 1;
			}
		}
	}	
}

int game(){
	int tube1_col = 15;
	int tube2_col = 20;
	int tube3_col = 25;
	int tube4_col = 30;
	
	int btm_tube1_col = 20;
	int btm_tube2_col = 30;
	
	int tube1_height = 4;
	int tube2_height = 2;
	int tube3_height = 4;
	int tube4_height = 3;	
	
	int btm_tube1_height = 3;
	int btm_tube2_height = 2;
	
	int prev_ln;
	
	int bird_ln = 5;
	int bird_col = 5;
	int tube_col;
	int up_tube_ln = 0;
	int btm_tube_ln = 10;
	int tube_width = 2;
	int score = 0;
	
	joystick_sel = get_button();
	GLCD_Clear(White);
	draw_bird(bird_ln);
		
	place_tube(tube1_col, up_tube_ln, tube1_height);
	place_tube(tube2_col, up_tube_ln, tube2_height);
	place_tube(tube3_col, up_tube_ln, tube3_height);
	place_tube(tube4_col, up_tube_ln, tube4_height);
	
	place_tube(btm_tube1_col, btm_tube_ln - btm_tube1_height, btm_tube1_height);
	place_tube(btm_tube2_col, btm_tube_ln - btm_tube2_height, btm_tube2_height);	
	
	delay(1);
	
	while (1){
		joystick_sel = get_button();
		prev_ln = bird_ln;
		if(joystick_sel == KBD_UP){
			if (bird_ln < 1){
				return score;
			}
			else {
				bird_ln--;
			}
		}
		else {
			if (bird_ln > 8){
				return score;
			}
			else {
				bird_ln++; 
			}
		}

		move_bird(prev_ln);
		draw_bird(bird_ln);	
		delay(15);

		if (tube1_col == bird_col || (tube1_col + 1) == bird_col){
			if (bird_ln <= tube1_height){
				return score;
			}else{
				score++;
			}
		}
	
		else if (tube2_col == bird_col || (tube2_col + 1) == bird_col){
			if (bird_ln <= tube2_height){
				return score;
			}else{
				score++;
			}
		}
	
		else if (tube3_col == bird_col || (tube3_col + 1) == bird_col){
			if (bird_ln <= tube3_height){
				return score;
			}else{
				score++;
			}
		}

		else if (tube4_col == bird_col || (tube4_col + 1) == bird_col){
			if (bird_ln <= tube4_height){
				return score;
			}else{
				score++;
			}
		}

		if (btm_tube1_col == bird_col || (btm_tube1_col + 1) == bird_col){
			if (bird_ln >= btm_tube_ln - btm_tube1_height - 1 ){
				return score;
			}else{
				score++;
			}
		}

		else if (btm_tube2_col == bird_col || (btm_tube2_col + 1) == bird_col){
			if (bird_ln >= btm_tube_ln - btm_tube2_height - 1){
				return score;
			}else{
				score++;
			}
		}	
	
		move_tube(tube1_col, up_tube_ln, tube1_height); 
		move_tube(tube2_col, up_tube_ln, tube2_height);
		move_tube(tube3_col, up_tube_ln, tube3_height);
		move_tube(tube4_col, up_tube_ln, tube4_height);
		
		move_tube(btm_tube1_col, btm_tube_ln - btm_tube1_height, btm_tube1_height);
		move_tube(btm_tube2_col, btm_tube_ln - btm_tube2_height, btm_tube2_height); 
	
		if (tube1_col < -tube_width) {
			create_new_tube(&tube1_col); 
			tube1_height = get_tube_height();
		}
		if (tube2_col < -tube_width) {
			create_new_tube(&tube2_col); 
			tube2_height = get_tube_height();
		}
		if (tube3_col < -tube_width) {
			create_new_tube(&tube3_col); 
			tube3_height = get_tube_height();
		}
		if (tube4_col < -tube_width) {
			create_new_tube(&tube4_col);
			tube4_height = get_tube_height();
		}
		
		if (btm_tube1_col < -tube_width) {
			create_new_tube(&btm_tube1_col); 
			btm_tube1_height = get_tube_height();
		}
				
		if (btm_tube2_col < -tube_width) {
			create_new_tube(&btm_tube2_col);
			btm_tube2_height = get_tube_height();			
		}
		
		tube1_col--;
		tube2_col--;
		tube3_col--;
		tube4_col--;
		                                                                                                                                                                                                                                         
		btm_tube1_col --;
		btm_tube2_col --;
	
		delay(2); 
	}                                                                                                                                                                                          
}

void start_flappy(){
	int game_score = 0;
	int reset; 
	
	while(1){
		game_score = game();
		reset = game_over(game_score);
		
		if (reset == 1)
			break;
		}
}

