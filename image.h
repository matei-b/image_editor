#ifndef IMAGE_H_
#define IMAGE_H_

#define MAX_LEN 100

struct pixel {
	float red, green, blue, grey;
};

struct image {
	char img_name[MAX_LEN];
	int format, x, y, colour_range;
	struct pixel **matrix;
};

struct image *image_mem_alloc(int format, int x, int y,
							  int colour_range, struct pixel **matrix);

void free_image(struct image *img, int x, int y, struct pixel **matrix);

#endif