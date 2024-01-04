#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "image.h"
#include "load.h"
#include "errors.h"

void image_load()
{
	char img_name[MAX_LEN], buffer[3];
	int format, x, y, colour_range;
	struct pixel **matrix;
	fgets(img_name, sizeof(img_name), stdin);
	img_name[strcspn(img_name, "\n")] = '\0';
	FILE *in = fopen(img_name, "rt");
	open_error(in, img_name);
	fgets(buffer, sizeof(buffer), in);
	buffer[strcspn(buffer, "\n")] = '\0';
	format = buffer[1] - '0';
	fscanf(in, "%d %d %d\n", &x, &y, &colour_range);
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
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++) {
			if (format == 3) {
				fscanf(in, "%f", &matrix[i][j].red);
				fscanf(in, "%f", &matrix[i][j].green);
				fscanf(in, "%f", &matrix[i][j].blue);
			}
			if (format == 2)
				fscanf(in, "%f", &matrix[i][j].grey);
			if (format == 6) {
				char pix;
				fread(&pix, 1, 1, in);
				matrix[i][j].red = pix;
				fread(&pix, 1, 1, in);
				matrix[i][j].green = pix;
				fread(&pix, 1, 1, in);
				matrix[i][j].blue = pix;
			}
			if (format == 5) {
				char pix;
				fread(&pix, 1, 1, in);
				matrix[i][j].grey = pix;
			}
		}
	struct image *img = image_mem_alloc(format, x, y, colour_range, matrix);
	printf("%d %d %d %d\n", img->format, img->x, img->y, img->colour_range);
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++)
			//printf("%f %f %f %f ", img->matrix[i][j].red, img->matrix[i][j].green, img->matrix[i][j].blue, img->matrix[i][j].grey);
			printf("%f ", img->matrix[i][j].grey);
		printf("\n");
	}
	free_image(img, x, y, matrix);
	fclose(in);
}