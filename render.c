#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "render.h"
#define SWAP(x,y) x=x^y; y=y^x; x=x^y; 

RGB set_color(unsigned char R, unsigned char G, unsigned char B) {
	RGB clr_of_pix;
	clr_of_pix.blue  = B;
	clr_of_pix.green = G;
	clr_of_pix.red   = R;
	return clr_of_pix;
}

C_VEC set_vector(int x0, int y0, int x1, int y1) {
	C_VEC out_vector;
	out_vector.x0 = x0;
	out_vector.y0 = y0;
	out_vector.x1 = x1;
	out_vector.y1 = y1;
	return out_vector;
}

void line(RGB **image, RGB color, C_VEC *l_vector) {
	int delta_x = l_vector->x1 - l_vector->x0;
	int delta_y = l_vector->y1 - l_vector->y0;
	char rot = 0;
	int y;

	if (abs(delta_x) < abs(delta_y)){
		SWAP(l_vector->x0, l_vector->y0);
		SWAP(l_vector->x1, l_vector->y1);
		rot = 1;
	}

	if (l_vector->x0 > l_vector->x1) {
		SWAP(l_vector->x0, l_vector->x1);
		SWAP(l_vector->y0, l_vector->y1);
	}

	for (int x = l_vector->x0; x < l_vector->x1; x++) {
		float k = (delta_y) / (float)(delta_x);
		y = k * (x - l_vector->x0) + l_vector->y0;
		if (rot)
			image[y][x] = color;
		else 
			image[x][y] = color;
	}
}
