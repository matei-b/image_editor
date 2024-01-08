// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "equalize.h"
#include "histogram.h"
#include "apply.h"

//verific daca pixelul se afla pe margine
int check_border(int i, int j, int x, int y)
{
	if (i == 0 || i == (y - 1) || j == 0 || j == (x - 1))
		return 1;
	return 0;
}

//fac suma folosind vectori de directie
float ker_sum(struct pixel **matrix, float ker[3][3],
			  int x, int y, int colour)
{
	float sum = 0;
	int dir_x[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dir_y[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int i = 0;
	while (i < 9) {
		if (colour == 0)
			sum += matrix[x + dir_x[i]][y + dir_y[i]].red
				   * ker[1 + dir_x[i]][1 + dir_y[i]];
		if (colour == 1)
			sum += matrix[x + dir_x[i]][y + dir_y[i]].green
				   * ker[1 + dir_x[i]][1 + dir_y[i]];
		if (colour == 2)
			sum += matrix[x + dir_x[i]][y + dir_y[i]].blue
				   * ker[1 + dir_x[i]][1 + dir_y[i]];
		i++;
	}
	sum = clamp(sum);
	return sum;
}

void apply_ker(struct image *img, int allocated)
{
	int nononono = NUMBER_NO_ONE_WOULD_THINK_OF;
	char line[MAX_LEN], par[MAX_LEN] = "hihihiha";
	char parameters[4][MAX_LEN] = {"EDGE", "BLUR", "SHARPEN", "GAUSSIAN_BLUR"};
	fgets(line, sizeof(line), stdin);
	int check = sscanf(line, " %s %d\n", par, &nononono);
	if (allocated == 0) {
		printf("No image loaded\n");
		return;
	}
	int ok = 0;
	//verific daca am parametrii corecti
	for (int i = 0; i < 4; i++)
		if (strcmp(parameters[i], par) == 0 &&
			nononono == NUMBER_NO_ONE_WOULD_THINK_OF)
			ok = 1;
	if (ok == 0) {
		if (strcmp(par, "hihihiha") != 0)
			printf("APPLY parameter invalid\n");
		else
			printf("Invalid command\n");
		return;
	}
	//verific daca am formatul corect
	if (img->format == 2 || img->format == 5) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	float edge[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
	float sharpen[3][3] = {{0, -1, 0}, {-1, 5, -1}, { 0, -1, 0}};
	float blur[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	float gaussian_blur[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			blur[i][j] = blur[i][j] / 9.;
			gaussian_blur[i][j] = gaussian_blur[i][j] / 16.;
		}
	struct pixel **temp_matrix = matrix_mem_alloc(img->x2, img->y2);
	for (int i = 0; i < img->y2; i++)
		for (int j = 0; j < img->x2; j++)
			temp_matrix[i][j] = img->matrix[i][j];
	for (int i = img->sel.y1; i < img->sel.y2; i++)
		for (int j = img->sel.x1; j < img->sel.x2; j++)
			if (check_border(i, j, img->x2, img->y2) == 0) {
				if (strcmp(par, "EDGE") == 0) {
					temp_matrix[i][j].red = ker_sum(img->matrix,
													edge, i, j, 0);
					temp_matrix[i][j].green = ker_sum(img->matrix, edge,
													  i, j, 1);
					temp_matrix[i][j].blue = ker_sum(img->matrix, edge,
													 i, j, 2);
				}
				if (strcmp(par, "SHARPEN") == 0) {
					temp_matrix[i][j].red = ker_sum(img->matrix, sharpen,
													i, j, 0);
					temp_matrix[i][j].green = ker_sum(img->matrix, sharpen,
													  i, j, 1);
					temp_matrix[i][j].blue = ker_sum(img->matrix, sharpen,
													 i, j, 2);
				}
				if (strcmp(par, "BLUR") == 0) {
					temp_matrix[i][j].red = ker_sum(img->matrix, blur,
													i, j, 0);
					temp_matrix[i][j].green = ker_sum(img->matrix, blur,
													  i, j, 1);
					temp_matrix[i][j].blue = ker_sum(img->matrix, blur,
													 i, j, 2);
				}
				if (strcmp(par, "GAUSSIAN_BLUR") == 0) {
					temp_matrix[i][j].red = ker_sum(img->matrix,
													gaussian_blur, i, j, 0);
					temp_matrix[i][j].green = ker_sum(img->matrix,
													  gaussian_blur, i, j, 1);
					temp_matrix[i][j].blue = ker_sum(img->matrix,
													 gaussian_blur, i, j, 2);
				}
			}
	free_matrix(img->y2, img->matrix);
	img->matrix = temp_matrix;
	printf("APPLY %s done\n", par);
}
