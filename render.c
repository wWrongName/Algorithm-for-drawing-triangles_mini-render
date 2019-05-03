#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "render.h"
#define SWAP(x,y) x=x^y; y=y^x; x=x^y; 

RGB color(unsigned char R, unsigned char G, unsigned char B) {
	RGB clr_of_pix;
	clr_of_pix.blue  = B;
	clr_of_pix.green = G;
	clr_of_pix.red   = R;
	return clr_of_pix;
}

void line(RGB **image, RGB color, int x0, int y0, int x1, int y1) {
	int delta_x = x1 - x0;
	int delta_y = y1 - y0;
	char rot = 0;
	int y;

	if (abs(delta_x) < abs(delta_y)){
		SWAP(x0, y0);
		SWAP(x1, y1);
		rot = 1;
	}

	if (x0 > x1) {
		SWAP(x0, x1);
		SWAP(y0, y1);
	}

	for (int x = x0; x < x1; x++) {
		float k = (delta_y) / (float)(delta_x);
		y = k * (x - x0) + y0;
		if (rot)
			image[y][x] = color;
		else 
			image[x][y] = color;
	}
}
