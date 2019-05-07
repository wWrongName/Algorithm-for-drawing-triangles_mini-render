#ifndef _RENDER_
#define _RENDER_

#pragma pack(push, 1)
typedef struct {               //about BMP file header
	unsigned short bi_file_type;
	unsigned int bi_file_size;
	unsigned short bi_file_res1;
	unsigned short bi_file_res2;
	unsigned int bi_off_bits;
} BMPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)        
typedef struct BMP {           //about BMP image
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
typedef struct RGB_pix {       //color of pixel
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} RGB;
#pragma pack(pop)

typedef struct {
	int x, y;
} COORD;

typedef struct LINE_COORDS {   //store coordinates of line
	COORD one;
	COORD two;
} C_VEC;

typedef struct TRGL_COORDS{
	COORD one;
	COORD two;
	COORD three;
} TRIANGLE;

COORD set_coord(int x, int y);
C_VEC set_vector(COORD one, COORD two);
TRIANGLE set_triangle(COORD one, COORD two, COORD three);
RGB set_color(unsigned char R, unsigned char G, unsigned char B);  
void draw_triangle(RGB **image, RGB color, TRIANGLE tgl);
void draw_line(RGB **image, RGB color, C_VEC l_vector);  

#endif
