// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "crop.h"

void crop_img(struct image *img, int allocated)
{
	if (allocated == 0) {
		printf("No image loaded\n");
		return;
	}
	int i = -1, j;
	int dif_y, dif_x;
	//dimensiunile noi ale matricei dupa taiere
	dif_y = img->sel.y2 - img->sel.y1;
	dif_x = img->sel.x2 - img->sel.x1;
	struct pixel **tmp_matrix = matrix_mem_alloc(dif_x, dif_y);
	for (int l = img->sel.y1; l < img->sel.y2; l++) {
		i++;
		j = -1;
		for (int k = img->sel.x1; k < img->sel.x2; k++) {
			j++;
			tmp_matrix[i][j] = img->matrix[l][k];
		}
	}
	free_matrix(img->y2, img->matrix);
	//resetarea selectiei
	img->x2 = j + 1;
	img->y2 = i + 1;
	img->sel.x1 = 0;
	img->sel.y1 = 0;
	img->sel.x2 = img->x2;
	img->sel.y2 = img->y2;
	img->matrix = tmp_matrix;
	printf("Image cropped\n");
}
