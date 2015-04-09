#include "myLib.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXWIDTH (200)
#define MINWIDTH (20)

typedef struct {
	int row;
	int col;
	int rd;
	int cd;
	int size;
	unsigned short color;
} COIN;

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	int row = 140;
	int col = 110;
	int oldrow = row;
	int oldcol = col;
	int isPressed = 0;
	int isPressed1 = 0;
	int size = 20;
	int oldsize = size;
	// drawChar(140, 5, 'A', RED);

	int i;
	int dels[] = {1, 2, 3, 4, 5};
	int numdels = sizeof(dels)/sizeof(dels[0]);
	unsigned short colors[] = {RED, GREEN, BLUE, MAGENTA, CYAN, YELLOW, WHITE};
	int numcolors = sizeof(colors)/sizeof(colors[0]);
	COIN objs[4];
	COIN oldobjs[4];
	int numCoins = sizeof(objs)/sizeof(objs[0]);
	COIN *cur;
	for(i=0; i<numCoins; i++)
	{
		objs[i].row = (rand()%100) - 100;// +  rand()% 20;

		//int a = rand() % 3;//tells which column to put block in
		objs[i].col = (i%3)*90 + 20; 
		objs[i].rd = dels[rand()%numdels];
		objs[i].cd = dels[rand()%numdels];
		//objs[i].rd = 2;
		//objs[i].cd = 2;
		objs[i].color = colors[i%numcolors];
		oldobjs[i] = objs[i];
	}



	//unsigned short bgcolor = LTGRAY;
	//DMA[3].src = &bgcolor;
	//DMA[3].dst = videoBuffer;
	//DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;

	while(1) // Game Loop
	{
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			if(!isPressed) {
				col = col + (MAXWIDTH - size) / 2;
				if (col >= MAXWIDTH) {
					col = MAXWIDTH;
				}
			}
			isPressed = 1;
		} else {
			isPressed = 0;
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			if(!isPressed1) {
				col = col - (MAXWIDTH - size) / 2;
				if (col <= MINWIDTH) {
					col = MINWIDTH;
				}
			}
			isPressed1 = 1;
		} else {
			isPressed1 = 0;
		}
	//draw coins
		for (i=0; i<numCoins; i++) {
			cur = objs + i;
			cur->row = cur->row + cur->rd;
			//cur->col = cur->col + cur->cd;

			if (boundsCheck(cur->row, 239, 20) == 1) { //passed bounds
				cur->col = (i%3)*90 + 20; //picks new col
        			cur->row = 0; //puts back to top
				cur->rd = dels[rand()%numdels];
			}
		}

		for(i=0; i<numCoins; i++) {
			drawRect(oldobjs[i].row, oldobjs[i].col, 20, 20, BLACK);
		}
		
		for(i=0; i<numCoins; i++) {
			cur = objs + i;
			if (boundsCheck(cur->row, 239, 20) != 2) { //less than 0
				drawRect(cur->row, cur->col, 20, 20, cur->color);
			}
			oldobjs[i] = objs[i];
			
		}
		oldsize = size;
	//


		WaitForVblank();
		drawRect(oldrow, oldcol, oldsize, oldsize, BLACK);// draw background
		drawRect(row, col, size, size, BLUE); //draw player


		oldrow = row;
		oldcol = col;
		oldsize = size;
	}
}
