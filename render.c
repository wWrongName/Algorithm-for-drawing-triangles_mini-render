#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "render.h"
#define SWAP(x,y) x=x^y; y=y^x; x=x^y; 

COORD set_coord(int x, int y) {
	COORD point;
	point.x = x;
	point.y = y;
	return point;
}

RGB set_color(unsigned char R, unsigned char G, unsigned char B) {
	RGB clr_of_pix;
	clr_of_pix.blue  = B;
	clr_of_pix.green = G;
	clr_of_pix.red   = R;
	return clr_of_pix;
}

C_VEC set_vector(COORD one, COORD two) {
	C_VEC out_vector;
	out_vector.one.x = one.x;
	out_vector.one.y = one.y;
	out_vector.two.x = two.x;
	out_vector.two.y = two.y;
	return out_vector;
}

void line(RGB **image, RGB color, C_VEC l_vector) {

	int delta_x = l_vector.two.x - l_vector.one.x;
	int delta_y = l_vector.two.y - l_vector.one.y;
	int x0 = l_vector.one.x, y0 = l_vector.one.y;
	int x1 = l_vector.two.x, y1 = l_vector.two.y;
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
		float t;
		int y;
		if (rot) {
			t = (float)(delta_x) / (float)(delta_y);
			y = t * (x - x0) + y0;
			image[x][y] = color;
		}
		else {
			t = (float)(delta_y) / (float)(delta_x);
			y = t * (x - x0) + y0;
			image[y][x] = color;
		}
	}
}
