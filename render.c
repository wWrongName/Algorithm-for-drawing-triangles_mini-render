#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"
#define SWAP(x,y) x=x^y; y=y^x; x=x^y; 

TRIANGLE set_triangle(COORD one, COORD two, COORD three) {
	TRIANGLE out_triangle;
	out_triangle.one   = one;
	out_triangle.two   = two;
	out_triangle.three = three;
	return out_triangle;
}

COORD set_coord(int x, int y) {
	COORD out_point;
	out_point.x = x;
	out_point.y = y;
	return out_point;
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

void draw_line(RGB **image, RGB color, C_VEC l_vector) {

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

void draw_outline_of_triangle(RGB **image, RGB color, TRIANGLE *tgl) {
	draw_line(image, color, set_vector(tgl->one, tgl->two));
	draw_line(image, color, set_vector(tgl->two, tgl->three));
	draw_line(image, color, set_vector(tgl->three, tgl->one));
}

void draw_triangle(RGB **image, RGB color, TRIANGLE *tgl) {
	tgl = sort_coords(tgl);
	if (tgl->three.y == tgl->two.y) 
		draw_plain_triangle(image, color, tgl);
	else if (tgl->one.y == tgl->two.y) {
		/////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	else {
		//////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
}

TRIANGLE *sort_coords(TRIANGLE *tgl) {
	if (tgl->one.y > tgl->two.y)
		SWAP(tgl->one.y, tgl->two.y);
	if (tgl->one.y > tgl->three.y)
		SWAP(tgl->one.y, tgl->three.y);
	if (tgl->two.y > tgl->three.y)
		SWAP(tgl->two.y, tgl->three.y);
	return tgl;
}

//this function get coordinates in the order (one - bottom, two and three - top)|
//                                                                              |
//             three-----------------------two            it's                  | 
//                  \                     /               "plain"               |
//                   \                   /                triangle              | 
//                    \                 /                                       |
//                     \               /                                        |
//                      \             /                                         |
//                       \           /                                          |
//                        \         /                                           |
//                         \       /                                            |
//                          \     /                                             | 
//                           \   /                                              |
//                            \ /                                               |
//                            one                                               V
//
void draw_plain_triangle(RGB **image, RGB color, TRIANGLE *tgl) {
	if (tgl->three.x > tgl->two.x)          // in order to make a pattern above
		SWAP(tgl->two.x, tgl->three.x);     // swap vertex
	float delta_left = (float)(tgl->three.y - tgl->one.y) / (float)(tgl->three.x - tgl->one.x);
	float delta_right = (float)(tgl->two.y - tgl->one.y) / (float)(tgl->two.x - tgl->one.x);
	for (int y = tgl->one.y; y <= tgl->three.y; y++) {
		int x1 = (y - tgl->one.y) / delta_left  + tgl->one.x;
		int x2 = (y - tgl->one.y) / delta_right + tgl->one.x;;
		for ( ; x1 <= x2; x1++)
			image[x1][y] = color;   //draw line between x1 and x2
	}
}
//end of the function 
