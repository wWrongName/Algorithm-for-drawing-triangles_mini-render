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
	int delta_x = l_vector->x0 - l_vector->x1;
	int delta_y = l_vector->y0 - l_vector->y1;
	int x0 = l_vector->x0, y0 = l_vector->y0;
	int x1 = l_vector->x1, y1 = l_vector->y1;
	char rot = 0;

	if (abs(delta_x) < abs(delta_y)) {
		SWAP(x0, y0);
		SWAP(x1, y1);
		rot = 1;
	}
	if (x0 > x1) {
		SWAP(x0, x1);
		SWAP(y0, y1);
	}

	for (int x = x0; x < x1; x++) {
		float k = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1 - k) + y1 * k;

		if (rot)
			image[x][y] = color;
		else 
			image[y][x] = color;
	}
}
