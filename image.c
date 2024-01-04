#include <string.h>
#include <stdlib.h>
#include "image.h"

#define MAX_LEN 100

struct image *image_mem_alloc(int format, int x, int y,
							  int colour_range, struct pixel **matrix)
{
	struct image *img = malloc(sizeof(struct image));
	img->format = format;
	img->x = x;
	img->y = y;
	img->colour_range = colour_range;
	img->matrix = matrix;
	return img;
}

void free_image(struct image *img, int x, int y, struct pixel **matrix)
{
	for (int i = 0; i < x; i++)
		free(matrix[i]);
	free(matrix);
	free(img);
}