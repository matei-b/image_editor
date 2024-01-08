// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "equalize.h"

int clamp(double num)
{
	if (num < 0)
		return 0;
	if (num > 255)
		return 255;
	return num;
}

void equalize_img(struct image *img, int allocated)
{
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		if (img->format == 3 || img->format  == 6) {
			printf("Black and white image needed\n");
		} else {
			double freq[256] = {0};
			double area = img->x2 * img->y2;
			//generarea vectorului de frecventa
			for (int i = 0; i < img->y2; i++)
				for (int j = 0; j < img->x2; j++)
					freq[(int)round(img->matrix[i][j].grey)]++;
			struct pixel **tmp_matrix = matrix_mem_alloc(img->x2, img->y2);
			//aplicarea formulei din documentatie
			for (int i = 0; i < img->y2; i++)
				for (int j = 0; j < img->x2; j++) {
					double hist_sum = 0;
					for (int k = 0; k <= img->matrix[i][j].grey; k++)
						hist_sum += freq[k];
					double num = ((255 * hist_sum) / area);
					tmp_matrix[i][j].grey = clamp(num);
				}
			free_matrix(img->y2, img->matrix);
			img->matrix = tmp_matrix;
			printf("Equalize done\n");
		}
	}
}
