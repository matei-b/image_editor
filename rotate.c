#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "histogram.h"
#include "rotate.h"

void rotate_img(struct image *img, int allocated)
{
	char line[MAX_LEN];
	int angle, nup = NUMBER_NO_ONE_WOULD_THINK_OF;
	fgets(line, sizeof(line), stdin);
	sscanf(line, " %d %d\n", &angle, &nup);
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		if (nup != NUMBER_NO_ONE_WOULD_THINK_OF) {
			printf("Invalid command\n");
		} else {
			if((img->sel.x2 - img->sel.x1) != (img->sel.y2 - img->sel.y1) && (img->sel.x1 != 0 || img->sel.y1 != 0 || img->sel.x2 != img->x2 || img->sel.y2 != img->y2)) {
				printf("The selection must be square\n");
			} else {
				if (angle % 90 != 0) {
					printf("Unsupported rotation angle\n");
				} else {
					int num_rotations;
					if (angle == -90)
						num_rotations = 3;
					if (angle == -180)
						num_rotations = 2;
					if (angle == -270)
						num_rotations = 1;
					if (angle == -360)
						num_rotations = 0;
					if (angle >= 0)
						num_rotations = (angle / 90) % 4;
					if ((img->sel.x2 - img->sel.x1) == (img->sel.y2 - img->sel.y1)) {
						for (int r = 0; r < num_rotations; r++) {
							struct pixel **temp_matrix = matrix_mem_alloc(img->x2, img->y2);
							for (int i = 0; i < img->y2; i++)
								for (int j = 0; j < img->x2; j++)
									temp_matrix[i][j] = img->matrix[i][j];
							for (int i = img->sel.y1; i < img->sel.y2; i++)
								for (int j = img->sel.x1; j < img->sel.x2; j++) {
									int i2 = j + img->sel.y1 - img->sel.x1;
									int j2 = (img->sel.x2 - 1) - i + img->sel.y1;
									temp_matrix[i][j] = img->matrix[i2][j2];
								}
							free_matrix(img->y2, img->matrix);
							img->matrix = temp_matrix;
						}
					} else {
						for (int r = 0; r < num_rotations; r++) {
							struct pixel **temp_matrix = matrix_mem_alloc(img->y2, img->x2);
							for (int i = 0; i < img->y2; i++)
								for (int j = 0; j < img->x2; j++)
									temp_matrix[j][img->y2 - 1 - i] = img->matrix[i][j];
							free_matrix(img->y2, img->matrix);
							int aux = img->y2;
							img->y2 = img->x2;
							img->x2 = aux;
							img->sel.x1 = 0;
							img->sel.y1 = 0;
							img->sel.x2 = img->x2;
							img->sel.y2 = img->y2;
							img->matrix = temp_matrix;
						}
					}
					printf("Rotated %d\n", angle);
				}
			}
		}
	}
}