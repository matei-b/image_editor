#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "crop.h"

void crop_img(struct image *img, int allocated)
{
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		int i = -1, j;
		struct pixel **tmp_matrix = matrix_mem_alloc(img->x2, img->y2);
		for (int l = img->sel.y1; l < img->sel.y2; l++) {
			i++;
			j = -1;
			for (int k = img->sel.x1; k < img->sel.x2; k++) {
				j++;
				if (img->format == 2 || img->format == 5) {
					tmp_matrix[i][j].grey = img->matrix[l][k].grey;
				} else {
					tmp_matrix[i][j].red = img->matrix[l][k].red;
					tmp_matrix[i][j].green = img->matrix[l][k].green;
					tmp_matrix[i][j].blue = img->matrix[l][k].blue;
				}
			}
		}
		free_matrix(img->y2, img->matrix);
		img->x2 = j + 1;
		img->y2 = i + 1;
		img->sel.x1 = 0;
		img->sel.y1 = 0;
		img->sel.x2 = img->x2;
		img->sel.y2 = img->y2;
		img->matrix = tmp_matrix;
		printf("Image cropped\n");
	}
}