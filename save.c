#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "load.h"

int round_up(float num)
{
	int x = num + 0.5;
	return x;
}

void save(struct image img, int allocated)
{
	char info[MAX_LEN], *new_img_name;
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		fgets(info, sizeof(info), stdin);
		new_img_name = strtok(info, " ");
		new_img_name[strcspn(new_img_name, "\n")] = '\0';
		FILE *out = fopen(new_img_name, "w");
		if (out == NULL) {
			fprintf(stderr, "Failed to open\n");
			exit(-1);
		}
		if ((strstr(info, "ascii"))) {
			if (img.format == 2 || img.format == 3) 
				fprintf(out, "P%d\n", img.format);
			if (img.format == 5)
				fprintf(out, "P2\n");
			if (img.format == 6)
				fprintf(out, "P3\n");
			fprintf(out, "%d %d\n", img.x2, img.y2);
			fprintf(out, "%d\n", img.colour_range);
			for (int i = img.y1; i < img.y2; i++) {
				for (int j = img.x1; j < img.x2; j++)
					if (img.format == 2 || img.format == 5) {
						fprintf(out, "%d ", round_up(img.matrix[i][j].grey));
					} else {
						fprintf(out, "%d ", round_up(img.matrix[i][j].red));
						fprintf(out, "%d ", round_up(img.matrix[i][j].green));
						fprintf(out, "%d ", round_up(img.matrix[i][j].blue));
					}
				fprintf(out, "\n");
			}
		} else {
			if (img.format == 5 || img.format == 6) 
				fprintf(out, "P%d\n", img.format);
			if (img.format == 2)
				fprintf(out, "P5\n");
			if (img.format == 3)
				fprintf(out, "P6\n");
			fprintf(out, "%d %d\n", img.x2, img.y2);
			fprintf(out, "%d\n", img.colour_range);
			for (int i = img.y1; i < img.y2; i++)
				for (int j = img.x1; j < img.x2; j++)
					if (img.format == 5 || img.format == 2) {
						unsigned char pix;
						pix = round_up(img.matrix[i][j].grey);
						fwrite(&pix, sizeof(unsigned char), 1, out);
					} else {
						unsigned char pix;
						pix = round_up(img.matrix[i][j].red);
						fwrite(&pix, sizeof(char), 1, out);
						pix = round_up(img.matrix[i][j].green);
						fwrite(&pix, sizeof(char), 1, out);
						pix = round_up(img.matrix[i][j].blue);
						fwrite(&pix, sizeof(char), 1, out);
					}
		}
		fclose(out);
		printf("Saved %s\n", new_img_name);
	}
}
