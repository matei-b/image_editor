#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"

#define MAX_LEN 100

struct pixel **matrix_mem_alloc(int x, int y)
{
	struct pixel **matrix;
	matrix = calloc(y, sizeof(struct pixel *));
	if (!matrix) {
		fprintf(stderr, "Eroare la alocare dinamica.\n");
		exit(-1);
	}
	for (int i = 0; i < y; i++) {
		matrix[i] = calloc(x, sizeof(struct pixel));
		if (!matrix[i]) {
			fprintf(stderr, "Eroare la alocare dinamica.\n");
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