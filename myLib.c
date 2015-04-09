#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;


void setPixel(int row, int col, u16 color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}



//draws a rectangle at of the specified size at the specified location
void drawRect(int row, int col, int height, int width, u16 color)
{
	for(int r=0; r<height; r++)
	{
		for(int c=0; c<width; c++)
		{
			setPixel(row+r, col+c, color);
		}
	}
}

void drawRect3(int r, int c, int width, int height, u16 color) {
	for (int x = 0; x < height; x++) {
		DMA[3].src = &color;
DMA[3].dst = &videoBuffer[OFFSET(r + x, c, 240)];
DMA[3].cnt = (width) | DMA_SOURCE_FIXED | DMA_ON;
}
}


int boundsCheck(int row, int bound, int size) {
    if(row < 0) { //passes through the ground
        //objs->col = (rand()%3)*90 + 20; //picks new col
        //objs->row = 0; //puts back to top
        //objs->cd; do not want to change speed, all should be the same speed?
        return 1;
    }
    if (row < 0) {
	return 2;
    }
	return 0;
}

void drawImage3(int r, int c, int width, int height, const u16* image) {
	//dma_source_increment - standard
	//dma_destination_incremnt
	for (int a=0; a<height; a++) {
		DMA[3].src = &image[OFFSET(a, 0, width)];
		DMA[3].dst = &videoBuffer[OFFSET(a+r, c, 240)];
		DMA[3].cnt = width | DMA_ON;
	}
}

void WaitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}


