// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#ifndef MATRIX_H_
#define MATRIX_H_

#define MAX_LEN 100

struct selection {
	int x1, y1, x2, y2;
};

struct pixel {
	float red, green, blue, grey;
};

struct image {
	int format, x2, y2, colour_range;
	struct selection sel;
	struct pixel **matrix;
};

struct pixel **matrix_mem_alloc(int x, int y);

void free_matrix(int y, struct pixel **matrix);

#endif
