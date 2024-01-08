// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "histogram.h"
#include "rotate.h"

//rotirea se face la dreapta
void rotate_selection_img(struct pixel **temp_matrix, struct pixel **matrix,
						  int selx1, int selx2, int sely1, int sely2,
						  int x2, int y2)
{
	for (int i = 0; i < y2; i++)
		for (int j = 0; j < x2; j++)
			temp_matrix[i][j] = matrix[i][j];
			for (int i = sely1; i < sely2; i++)
				for (int j = selx1; j < selx2; j++) {
					//am urmarit pe o ciorna cum se modifica
					//liniile si coloanele si am dedus
					//urmatorul tipar
					int i2 = j + sely1 - selx1;
					int j2 = (sely2 - 1) - i + selx1;
					temp_matrix[i2][j2] = matrix[i][j];
				}
}

void rotate_img(struct image *img, int allocated)
{
	char line[MAX_LEN];
	int angle, nup = NUMBER_NO_ONE_WOULD_THINK_OF;
	fgets(line, sizeof(line), stdin);
	int check = sscanf(line, " %d %d\n", &angle, &nup);
	if (allocated == 0) {
		printf("No image loaded\n");
		return;
	}
	if (nup != NUMBER_NO_ONE_WOULD_THINK_OF) {
		printf("Invalid command\n");
		return;
	}
	//verific daca zona este patrata
	//sau daca selectia nu cuprinde intreaga poza
	if ((img->sel.x2 - img->sel.x1) != (img->sel.y2 - img->sel.y1) &&
	    (img->sel.x1 != 0 || img->sel.y1 != 0 ||
	     img->sel.x2 != img->x2 || img->sel.y2 != img->y2)) {
		printf("The selection must be square\n");
		return;
	}
	if (angle % 90 != 0) {
		printf("Unsupported rotation angle\n");
		return;
	}
	//unghiul fiind un multiplu de 90
	//acesta este echivalent cu mai
	//multe rotiri consecutive de 90 de grade
	int num_rotations;
	if (angle < 0)
		num_rotations = (angle / 90) + 4;
	else
		num_rotations = (angle / 90) % 4;
	if ((img->sel.x2 - img->sel.x1) == (img->sel.y2 - img->sel.y1)) {
		for (int r = 0; r < num_rotations; r++) {
			struct pixel **temp_matrix = matrix_mem_alloc(img->x2, img->y2);
			rotate_selection_img(temp_matrix, img->matrix, img->sel.x1,
								 img->sel.x2, img->sel.y1, img->sel.y2,
								 img->x2, img->y2);
			free_matrix(img->y2, img->matrix);
			img->matrix = temp_matrix;
		}
	} else {
		for (int r = 0; r < num_rotations; r++) {
			struct pixel **temp_matrix = matrix_mem_alloc(img->y2, img->x2);
			for (int i = 0; i < img->y2; i++)
				for (int j = 0; j < img->x2; j++)
					//analog pasilor de la rotirea selectiei
					//in ceea ce priveste deducerea schimbarii
					//de indici
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
