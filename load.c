#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "load.h"

void image_load(struct image *img, int *allocated)
{
	if ((*allocated) == 1)
		free_matrix(img->y2, img->matrix);
	char buffer[3], img_name[MAX_LEN];
	struct pixel **matrix;
	scanf("%s", img_name);
	FILE *in = fopen(img_name, "rt");
	if (in == NULL) {
		fprintf(stdout, "Failed to load %s\n", img_name);
		(*allocated) = 0;
	} else {
		(*allocated) = 1;
		img->sel.x1 = 0;
		img->sel.y1 = 0;
		img->sel.x2 = 0;
		img->sel.y2 = 0;
		fgets(buffer, sizeof(buffer), in);
		buffer[strcspn(buffer, "\n")] = '\0';
		img->format = buffer[1] - '0';
		fscanf(in, "%d%d%d\n", &img->x2, &img->y2, &img->colour_range);
		matrix = matrix_mem_alloc(img->x2, img->y2);
		for (int i = 0; i < img->y2; i++)
			for (int j = 0; j < img->x2; j++) {
				if (img->format == 3) {
					fscanf(in, "%f", &matrix[i][j].red);
					fscanf(in, "%f", &matrix[i][j].green);
					fscanf(in, "%f", &matrix[i][j].blue);
				}
				if (img->format == 2)
					fscanf(in, "%f", &matrix[i][j].grey);
				if (img->format == 6) {
					unsigned char pix;
					fread(&pix, 1, 1, in);
					matrix[i][j].red = pix;
					fread(&pix, 1, 1, in);
					matrix[i][j].green = pix;
					fread(&pix, 1, 1, in);
					matrix[i][j].blue = pix;
				}
				if (img->format == 5) {
					unsigned char pix;
					fread(&pix, 1, 1, in);
					matrix[i][j].grey = pix;
				}
			}
		img->matrix = matrix;
		fclose(in);
		printf("Loaded %s\n", img_name);
	}
}