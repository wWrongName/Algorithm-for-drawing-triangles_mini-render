#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"
#define SWAP(x,y) x=x^y; y=y^x; x=x^y; 
char for_free = 0;

TRIANGLE *set_triangle(COORD one, COORD two, COORD three) {
	TRIANGLE *out_triangle = (TRIANGLE*)malloc(sizeof(TRIANGLE));
	out_triangle->one   = one;
	out_triangle->two   = two;
	out_triangle->three = three;
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
	if (tgl->three.y == tgl->two.y)                // if it's a "plain" triangle
		draw_plain_triangle(image, color, tgl, 0);
	else if (tgl->one.y == tgl->two.y) {           // if it's an overturned "plain" triangle
		draw_plain_triangle(image, color, tgl, 1);
	}
	else {// if it's a triangle with different "Y" coordinates of vertices 
		float div = (float)(tgl->three.x - tgl->one.x) / (float)(tgl->three.y - tgl->one.y);// we must divide a triangle into two "plain" triangles
		int mid_x = (tgl->two.y - tgl->one.y) * div + tgl->one.x;
		for_free = 1;
		draw_plain_triangle(image, color, set_triangle(tgl->one, tgl->two, set_coord(mid_x, tgl->two.y)), 0);
		draw_plain_triangle(image, color, set_triangle(set_coord(mid_x, tgl->two.y), tgl->two, tgl->three), 1);
		for_free = 0;
	}
}

TRIANGLE *sort_coords(TRIANGLE *tgl) {
	COORD tmp;
	if (tgl->one.y > tgl->two.y) {
		tmp = tgl->one;
		tgl->one = tgl->two;
		tgl->two = tmp;
	}
	if (tgl->one.y > tgl->three.y) {
		tmp = tgl->one;
		tgl->one = tgl->three;
		tgl->three = tmp;
	}
	if (tgl->two.y > tgl->three.y) {
		tmp = tgl->two;
		tgl->two = tgl->three;
		tgl->three = tmp;
	}
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
void draw_plain_triangle(RGB **image, RGB color, TRIANGLE *tgl, char flip_f) {
	if (flip_f == 1) {
		SWAP(tgl->one.y, tgl->three.y);
		tgl->two.y = tgl->one.y;
		tgl = sort_coords(tgl);
	}
	float delta_left =  (float)(tgl->three.x - tgl->one.x) / (float)(tgl->three.y - tgl->one.y);
	float delta_right = (float)(tgl->two.x - tgl->one.x) / (float)(tgl->two.y - tgl->one.y);
	int last_y = tgl->three.y;
	int back_ctr = -1;                 //for flip again
	for (int y = tgl->one.y; y <= last_y; y++) {
		back_ctr++;
		int x1 = (y - tgl->one.y) * delta_left  + tgl->one.x;
		int x2 = (y - tgl->one.y) * delta_right + tgl->one.x;
		if (x1 > x2) {
			SWAP(x1, x2);
		}
		for (; x1 <= x2; x1++) {
			if (flip_f == 0)
				image[y][x1] = color;  //draw line between x1 and x2
			else {
				int y_r = last_y - back_ctr;
				image[y_r][x1] = color;// for reverse rotation
			}
		}
	}
	if (for_free)
		free(tgl);
}

VERTEX *read_obj(FILE *in_obj) {
	VERTEX *vertexes;
	unsigned int counter = 0;
	if (!in_obj)
		return NULL;
	int tmp;
	while (!feof(tmp = fgetc(in_obj))) {
		if (!strcmp(tmp, 'v') && !strcmp(tmp = fgetc(in_obj), ' ')) {
			vertexes = (VERTEX*)realloc(vertexes, sizeof(VERTEX)*(++counter));
			vertexes = read_vertex(in_obj, vertexes, counter);
		}
		else
			break;
	}
	return vertexes;
}

VERTEX *read_vertex(FILE *in_obj, VERTEX *vertexes, unsigned int counter) {
	int tmp;

	vertexes[counter - 1].x = 0;
	while (strcmp(tmp = fgetc(in_obj), ' '))
		vertexes[counter - 1].x = vertexes[counter - 1].x * 10 + (tmp - '0');

	vertexes[counter - 1].y = 0;
	while (strcmp(tmp = fgetc(in_obj), ' '))
		vertexes[counter - 1].y = vertexes[counter - 1].y * 10 + (tmp - '0');

	vertexes[counter - 1].z = 0;
	while (isdigit(tmp = fgetc(in_obj)))
		vertexes[counter - 1].z = vertexes[counter - 1].z * 10 + (tmp - '0');

	return vertexes;
}