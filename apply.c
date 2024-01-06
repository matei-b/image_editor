#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "equalize.h"
#include "histogram.h"
#include "apply.h"

int check_border(int i, int j, int x, int y)
{
	if (i == 0 || i == (y - 1) || j == 0 || j == (x - 1))
		return 1;
	return 0;
}

float ker_sum(struct pixel **matrix, float ker[3][3],
			  int x, int y, int colour) 
{
	float sum = 0;
	int dir_x[] = {0, 0, 0, 1, 1, 1, -1, -1, -1};
	int dir_y[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int i = 0;
	while (i < 8) {
		if (colour == 0)
			sum += matrix[x + dir_x[i]][y + dir_y[i]].red * ker[1 + dir_x[i]][1 + dir_y[i]];
		if (colour == 1)
			sum += matrix[x + dir_x[i]][y + dir_y[i]].green * ker[1 + dir_x[i]][1 + dir_y[i]];
		if (colour == 2)
			sum += matrix[x + dir_x[i]][y + dir_y[i]].blue * ker[1 + dir_x[i]][1 + dir_y[i]];
		i++;
	}
	sum = clamp(sum);
	return sum;
}

void apply_ker(struct image *img, int allocated)
{
	int nononono = NUMBER_NO_ONE_WOULD_THINK_OF, par_ind = 0;
	char line[MAX_LEN], par[MAX_LEN];
	char parameters[4][MAX_LEN] = {"EDGE", "BLUR", "SHARPEN", "GAUSSIAN_BLUR"};
	fgets(line, sizeof(line), stdin);
	sscanf(line, " %s %d\n", par, &nononono);
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		int ok = 0;
		for(int i = 0; i < 4; i++)
			if(strcmp(parameters[i], par) == 0 && nononono == NUMBER_NO_ONE_WOULD_THINK_OF) {
				ok = 1;
				par_ind = i;
			}
		if (ok == 0) {
			if (nononono == NUMBER_NO_ONE_WOULD_THINK_OF)
				printf("APPLY parameter invalid\n");
			else
				printf("Invalid command\n");
		} else {
			if (img->format == 2 || img->format == 5) {
				printf("Easy, Charlie Chaplin\n");
			} else {
				float edge[3][3] = {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};
				float sharpen[3][3] = {{0,-1,0},{-1,5,-1},{0,-1,0}};
				float blur[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
				float gaussian_blur[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++) {
						blur[i][j] = blur[i][j]/9.;
						gaussian_blur[i][j] = gaussian_blur[i][j]/16.;
					}
				struct pixel **temp_matrix = matrix_mem_alloc(img->x2,img->y2);
				for (int i = 0; i < img->y2; i++)
					for (int j = 0; j < img->x2; j++) {
						temp_matrix[i][j].red = img->matrix[i][j].red;
						temp_matrix[i][j].green = img->matrix[i][j].green;
						temp_matrix[i][j].blue = img->matrix[i][j].blue;
					}
				int cnt = 0;
				for (int i = img->sel.y1; i < img->sel.y2; i++)
					for (int j = img->sel.x1; j < img->sel.x2; j++)
						if (check_border(i, j, img->x2, img->y2) == 0) {
							if (par_ind == 0){
								temp_matrix[i][j].red = ker_sum(img->matrix, edge, i, j, 0);
								temp_matrix[i][j].green = ker_sum(img->matrix, edge, i, j, 1);
								temp_matrix[i][j].blue = ker_sum(img->matrix, edge, i, j, 2);
							}
							if (par_ind == 1) {
								temp_matrix[i][j].red = ker_sum(img->matrix, sharpen, i, j, 0);
								temp_matrix[i][j].green = ker_sum(img->matrix, sharpen, i, j, 1);
								temp_matrix[i][j].blue = ker_sum(img->matrix, sharpen, i, j, 2);
							}
							if (par_ind == 2) {
								temp_matrix[i][j].red = ker_sum(img->matrix, blur, i, j, 0);
								temp_matrix[i][j].green = ker_sum(img->matrix, blur, i, j, 1);
								temp_matrix[i][j].blue = ker_sum(img->matrix, blur, i, j, 2);
							}
							if (par_ind == 3) {
								temp_matrix[i][j].red = ker_sum(img->matrix, gaussian_blur, i, j, 0);
								temp_matrix[i][j].green = ker_sum(img->matrix, gaussian_blur, i, j, 1);
								temp_matrix[i][j].blue = ker_sum(img->matrix, gaussian_blur, i, j, 2);
							}
						}
				free_matrix(img->y2, img->matrix);
				img->matrix = temp_matrix;
				printf("APPLY %s done\n", par);
			}
		}
	}
}
//nu uita sa eliberezi memoria matricei dupa ce o schimbi cu cea auxiliara