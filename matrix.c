// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"

#define MAX_LEN 100

//alocarea de memorie pentru matricea de valori
//ale pixelilor
struct pixel **matrix_mem_alloc(int x, int y)
{
	struct pixel **matrix;
	matrix = calloc(y, sizeof(struct pixel *));
	if (!matrix) {
		fprintf(stderr, "Dynamic allocation error.\n");
		exit(-1);
	}
	for (int i = 0; i < y; i++) {
		matrix[i] = calloc(x, sizeof(struct pixel));
		if (!matrix[i]) {
			fprintf(stderr, "Dynamic allocation error.\n");
			exit(-1);
		}
	}
	return matrix;
}

void free_matrix(int y, struct pixel **matrix)
{
	for (int i = 0; i < y; i++)
		free(matrix[i]);
	free(matrix);
}
