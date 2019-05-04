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

typedef struct LINE_COORDS {   //store coordinates of line
	int x0, y0;
	int x1, y1;
}C_VEC;

C_VEC set_vector(int x0, int y0, int x1, int y1);
RGB   set_color (unsigned char R, unsigned char G, unsigned char B);  
void  line      (RGB **image, RGB color, C_VEC *l_vector);              //draw a line 

#endif
