#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#define  BMP 19778

int main(int argc, char **argv)
{
	BMPFILEHEADER fh;
	BMPINFOHEADER ih;
	
	fh.bi_file_type = BMP;
	fh.bi_file_size = 7077942;
	fh.bi_file_res1 = 0;
	fh.bi_file_res2 = 0;
	fh.bi_off_bits = 54;

	ih.bi_size = 40;
	ih.bi_height = 1152;
	ih.bi_width = 2048;
	ih.bi_planes = 1;
	ih.bi_bit_count = 24;
	ih.bi_compression = 0;
	ih.bi_size_image = 7077888;
	ih.bi_x = 4724;
	ih.bi_y = 4724;
	ih.bi_clrs_used = 0;
	ih.bi_clrs_imp = 0;

	TRIANGLE tgl = set_triangle(set_coord(100, 100), set_coord(100, 1000), set_coord(1000, 1000));

	RGB **image;
	image = (RGB**)malloc(ih.bi_height * sizeof(RGB*));
	for (int i = 0; i < ih.bi_height; i++) {
		image[i] = (RGB*)malloc(ih.bi_width * sizeof(RGB));
	}

	for (int i = 0; i < ih.bi_height; i++)
		for (int j = 0; j < ih.bi_width; j++) {
			image[i][j] = set_color(0, 0, 0);
		}

	draw_triangle(image, set_color(255,255,255), tgl);

	FILE *out = fopen("C:\\Users\\John\\Desktop\\input.bmp", "wb");
	fwrite(&fh, sizeof(BMPFILEHEADER), 1, out);
	fwrite(&ih, sizeof(BMPINFOHEADER), 1, out);
	
	for (int i = 0; i < ih.bi_height; i++) {
		for (int j = 0; j < ih.bi_width; j++) {
			fwrite(&image[i][j], sizeof(RGB), 1, out);
		}
	}
	return 0;
}
