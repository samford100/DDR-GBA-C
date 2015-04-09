#include "myLib.h"
#include "titlescreen.h"
#include "leftarrow.h"
#include "rightarrow.h"
#include "uparrow.h"
#include "downarrow.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include "gameover.h"


#define MAXWIDTH (200)
#define MINWIDTH (20)

typedef struct {
	int row;
	int col;
	int size;
	int speed;
	int cd;
	int delay;
	unsigned short color;
} ARROW;


int main()
{
	REG_DISPCNT= MODE3 | BG2_ENABLE;
	int i = 0;
	//create all arrows
	

    ARROW cLeftArrow;
		cLeftArrow.row = 10;
		cLeftArrow.col = 10;
		cLeftArrow.size = 20;
		cLeftArrow.color = BLUE;
	ARROW cRightArrow;
		cRightArrow.row = 10;
		cRightArrow.col = 210;
		cRightArrow.size = 20;
		cRightArrow.color = GREEN;
	ARROW cUpArrow;
		cUpArrow.row = 10;
		cUpArrow.col = 144;
		cUpArrow.size = 20;
		cUpArrow.color = WHITE;
	ARROW cDownArrow;
		cDownArrow.row = 10;
		cDownArrow.col = 77;
		cDownArrow.size = 20;
		cDownArrow.color = YELLOW;
    //ARROW cRightArrow;
    //ARROW cUpArrow;
    //ARROW cDownArrow;

	


	//
	int score = 0;

	int lPressed = 0;
	int rPressed = 0;
	int uPressed = 0;
	int dPressed = 0;
	int sPressed = 0;
	int selPressed = 0;
	
	ARROW *cur;
    //cLeftArrow = arrowSetup(cLeftArrow, 10, 10, 20, BLUE);
    //cRightArrow = arrowSetup(cRightArrow, 10, 80, 20, BLUE);
    //cUpArrow = arrowSetup(cUpArrow, 10, 10, 150, BLUE);
    //cDownArrow = arrowSetup(cDownArrow, 10, 10, 220, BLUE);

    //drawRect3(cLeftArrow.row, cLeftArrow.col, cLeftArrow.size, cLeftArrow.size, cLeftArrow.color);
    //drawRect3(cRightArrow.row, cRightArrow.col, cRightArrow.size, cRightArrow.size, cRightArrow.color);
    //drawRect3(cUpArrow.row, cUpArrow.col, cUpArrow.size, cUpArrow.size, cUpArrow.color);
    //drawRect3(cDownArrow.row, cDownArrow.col, cDownArrow.size, cDownArrow.size, cDownArrow.color);
	

    //ARROW[] moves; //list of moves - check against player moves - add one move each time



	//unsigned short bgcolor = GRAY;
	//DMA[3].src = &bgcolor;
	//DMA[3].dst = videoBuffer;
	//DMA[3].cnt = 240*160 | DMA_ON | DMA_SOURCE_FIXED;

    int f = 0;
	while(1) {
	drawImage3(0, 0, 240, 160, titlescreen);
	drawRect3(135, (f%39)+190, 15, 5, BLACK);
		while(1) {
			//title screen
			//drawRect3(0, 0, 240, 160, RED);
			
			
			if(KEY_DOWN_NOW(BUTTON_START))
			{
			if(!sPressed) {
				break;
			}
			sPressed = 1;
			} else {
			sPressed = 0;
			}
			if(KEY_DOWN_NOW(BUTTON_LEFT))
			{
				if(!lPressed) {
					f -= 13;
					if (f<0) {
						f=0;
					}
					drawImage3(0, 0, 240, 160, titlescreen);
					drawRect3(135, (f%39)+190, 15, 5, BLACK);
					
				}
				lPressed = 1;
			} else {
				lPressed = 0;
			}
			if(KEY_DOWN_NOW(BUTTON_RIGHT))
			{
				if(!rPressed) {
					f += 13;
					drawImage3(0, 0, 240, 160, titlescreen);
					drawRect3(135, (f%39)+190, 15, 5, BLACK);
					
				}
				rPressed = 1;
			} else {
				rPressed = 0;
			}
		}
		//set up arrows
	score = 0;
	ARROW leftArrows[2];
	ARROW oldLeftArrows[2];
	int leftArrowsSize = sizeof(leftArrows)/sizeof(leftArrows[0]);
	for(i=0; i<leftArrowsSize; i++) {
		leftArrows[i].delay = (rand()%3)*30 * i;//reset after bounds check 
		leftArrows[i].row = 160 + (rand()%4)*20;
		leftArrows[i].col = 10;
		leftArrows[i].size = 20;
		leftArrows[i].color = RED;
		leftArrows[i].speed = -(f/13 + 1);
		leftArrows[i].cd = 0;
		oldLeftArrows[i] = leftArrows[i];
	}
	ARROW rightArrows[2];
	ARROW oldRightArrows[2];
	int rightArrowsSize = sizeof(rightArrows)/sizeof(rightArrows[0]);
	for(i=0; i<rightArrowsSize; i++) {
		rightArrows[i].row = 160 + (rand()%4)*20;
		rightArrows[i].col = 210;
		rightArrows[i].size = 20;
		rightArrows[i].color = RED;
		rightArrows[i].speed = -(f/13 + 1);
		rightArrows[i].cd = 0;
		oldRightArrows[i] = rightArrows[i];
	}
	ARROW upArrows[2];
	ARROW oldUpArrows[2];
	int upArrowsSize = sizeof(upArrows)/sizeof(upArrows[0]);
	for(i=0; i<upArrowsSize; i++) {
		upArrows[i].delay = (rand()%3)*30 * i;//reset after bounds check 
		upArrows[i].row = 160 + (rand()%4)*20;
		upArrows[i].col = 144;
		upArrows[i].size = 20;
		upArrows[i].color = RED;
		upArrows[i].speed = -(f/13 + 1);
		upArrows[i].cd = 0;
		oldUpArrows[i] = upArrows[i];
	}
	ARROW downArrows[2];
	ARROW oldDownArrows[2];
	int downArrowsSize = sizeof(downArrows)/sizeof(downArrows[0]);
	for(i=0; i<downArrowsSize; i++) {
		downArrows[i].delay = (rand()%3)*30 * i;//reset after bounds check 
		downArrows[i].row = 160 + (rand()%4)*20;
		downArrows[i].col = 77;
		downArrows[i].size = 20;
		downArrows[i].color = RED;
		downArrows[i].speed = -(f/13 + 1);
		downArrows[i].cd = 0;
		oldDownArrows[i] = downArrows[i];
	}
	drawRect3(0,0,240,160,BLACK);

	while(1) {
	
	//draw score
	drawChar(0, 0, 's', RED);
	drawChar(8, 0, 'c', RED);
	drawChar(16, 0, 'o', RED);
	drawChar(24, 0, 'r', RED);
	drawChar(32, 0, 'e', RED);
	int b = score;
	for (i = 0; i<5; i++) {
		drawRect3(80-8*i, 0, 6, 8, BLACK);
		drawChar(80-8*i, 0, '0'+abs(b)%10, RED);
		b = b/10;
	}
	drawRect3(88, 0, 6, 8, BLACK);
	if(score<0) {
		drawChar(88, 0, '-', RED);
	}

		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			if(!selPressed) {
				break;
			}
			selPressed = 1;
		} else {
			selPressed = 0;
		}

		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			if(!lPressed) {
				//check against all arrows in l arrows
				int e = 0;
				for (i=0; i<leftArrowsSize; i++) {
					cur = leftArrows + i;
					if (cur->row > 10 && cur->row < 30) { //hit at same time almost
						e=1;
						cur->cd = 1;
					}
				}
				if(e == 1) {
					score += 2;
				} else {
					score -= 1;
				}
			}
			lPressed = 1;
		} else {
			lPressed = 0;
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			if(!rPressed) {
				int e = 0;
				//check against all arrows in l arrows
				for (i=0; i<rightArrowsSize; i++) {
					cur = rightArrows + i;
					if (cur->row > 10 && cur->row < 30) { //hit at same time almost
						e=1;
						cur->cd = -1;
					}
				}
				if(e == 1) {
					score += 2;
				} else {
					score -= 1;
				}
			}
			rPressed = 1;
		} else {
			rPressed = 0;
		}
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			if(!uPressed) {
				int e = 0;
				//check against all arrows in l arrows
				for (i=0; i<upArrowsSize; i++) {
					cur = upArrows + i;
					if (cur->row > 10 && cur->row < 30) { //hit at same time almost
						e=1;
						cur->cd = -1;
					}
				}
				if(e == 1) {
					score += 2;
				} else {
					score -= 1;
				}
			}
			uPressed = 1;
		} else {
			uPressed = 0;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			if(!dPressed) {
				int e = 0;
				//check against all arrows in l arrows
				for (i=0; i<downArrowsSize; i++) {
					cur = downArrows + i;
					if (cur->row > 10 && cur->row < 30) { //hit at same time almost
						e=1;
						cur->cd = 1;
					}
				}
				if(e == 1) {
					score += 2;
				} else {
					score -= 1;
				}
			}
			dPressed = 1;
		} else {
			dPressed = 0;
		}


		WaitForVblank();
		for(i=0; i<leftArrowsSize; i++) {
			cur = leftArrows + i;
			cur->row = cur->row + cur->speed;
			cur->col = cur->col + cur->cd;

			//cur->col = cur->col + cur->cd;

			if (boundsCheck(cur->row, 239, 20)) { //passed bounds
        			cur->row = 160 + rand()%4*30; ; //puts back to bottom
				cur->col = cLeftArrow.col;
				cur-> cd = 0;
			}

			cur = rightArrows + i;
			cur->row = cur->row + cur->speed;
			cur->col = cur->col + cur->cd;

			//cur->col = cur->col + cur->cd;

			if (boundsCheck(cur->row, 239, 20)) { //passed bounds
        			cur->row = 160 + rand()%4*30; ; //puts back to bottom
				cur->col = cRightArrow.col;
				cur-> cd = 0;
			}
			cur = upArrows + i;
			cur->row = cur->row + cur->speed;
			cur->col = cur->col + cur->cd;

			//cur->col = cur->col + cur->cd;

			if (boundsCheck(cur->row, 239, 20)) { //passed bounds
        			cur->row = 160 + rand()%4*30; ; //puts back to bottom
				cur->col = cUpArrow.col;
				cur-> cd = 0;
			}
			cur = downArrows + i;
			cur->row = cur->row + cur->speed;
			cur->col = cur->col + cur->cd;

			//cur->col = cur->col + cur->cd;

			if (boundsCheck(cur->row, 239, 20)) { //passed bounds
        			cur->row = 160 + rand()%4*30; ; //puts back to bottom
				cur->col = cDownArrow.col;
				cur-> cd = 0;
			}
		}
		for(i=0; i<leftArrowsSize; i++) {
			cur = oldLeftArrows + i;
			if(cur->row < 160 && cur->row > 0) {
				drawRect3(cur->row, cur->col, 20, 20, BLACK);
			}
			cur = oldRightArrows + i;
			if(cur->row < 160 && cur->row > 0) {
				drawRect3(cur->row, cur->col, 20, 20, BLACK);
			}
			cur = oldUpArrows + i;
			if(cur->row < 160 && cur->row > 0) {
				drawRect3(cur->row, cur->col, 20, 20, BLACK);
			}
			cur = oldDownArrows + i;
			if(cur->row < 160 && cur->row > 0) {
				drawRect3(cur->row, cur->col, 20, 20, BLACK);
			}
		}
		for(i=0; i<leftArrowsSize; i++) {
			cur = leftArrows + i;
			if(cur->row < 160 && cur->row > 0) {
				//drawRect3(cur->row, cur->col, 20, 20, cur->color);
				drawImage3(cur->row, cur->col, 20, 20, leftarrow);
			}
			cur = rightArrows + i;
			if(cur->row < 160 && cur->row > 0) {
				//drawRect3(cur->row, cur->col, 20, 20, cur->color);
				drawImage3(cur->row, cur->col, 20, 20, rightarrow);
			}
			cur = upArrows + i;
			if(cur->row < 160 && cur->row > 0) {
				//drawRect3(cur->row, cur->col, 20, 20, cur->color);
				drawImage3(cur->row, cur->col, 20, 20, uparrow);
			}
			cur = downArrows + i;
			if(cur->row < 160 && cur->row > 0) {
				//drawRect3(cur->row, cur->col, 20, 20, cur->color);
				drawImage3(cur->row, cur->col, 20, 20, downarrow);
			}
			oldLeftArrows[i] = leftArrows[i];
			oldRightArrows[i] = rightArrows[i];
			oldUpArrows[i] = upArrows[i];
			oldDownArrows[i] = downArrows[i];
		}

		//draw cArrows
	//drawRect3(cLeftArrow.row, cLeftArrow.col, cLeftArrow.size, cLeftArrow.size, cLeftArrow.color);
    	//drawRect3(cRightArrow.row, cRightArrow.col, cRightArrow.size, cRightArrow.size, cRightArrow.color);
    	//drawRect3(cUpArrow.row, cUpArrow.col, cUpArrow.size, cUpArrow.size, cUpArrow.color);
    	//drawRect3(cDownArrow.row, cDownArrow.col, cDownArrow.size, cDownArrow.size, cDownArrow.color);
	drawRect3(30, 10, 220, 1, WHITE);
	drawRect3(50, 10, 220, 1, WHITE);

	if(score < -5) {
		break;
	}
	WaitForVblank();
	}
	drawImage3(0, 0, 240, 160, gameover);
	while(1) {
		//button press to break
		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			if(!selPressed) {
				break;
			}
			selPressed = 1;
		} else {
			selPressed = 0;
		}

	}
}
	

}

