#ifndef _RENDER_
#define _RENDER_

#pragma pack(push, 1)
typedef struct {
	unsigned short bi_file_type;
	unsigned int bi_file_size;
	unsigned short bi_file_res1;
	unsigned short bi_file_res2;
	unsigned int bi_off_bits;
} BMPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BMP {
	unsigned int bi_size;
	int bi_width;
	int bi_height;
	unsigned short bi_planes;
	unsigned short bi_bit_count;
	unsigned int bi_compression;
	unsigned int bi_size_image;
	int bi_x;
	int bi_y;
	unsigned int bi_clrs_used;
	unsigned int bi_clrs_imp;
} BMPINFOHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct RGB_pix {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} RGB;
#pragma pack(pop)

void line(RGB **image, RGB color, int x0, int y0, int x1, int y1);
RGB color(char R, char G, char B);

#endif
