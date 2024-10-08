// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"
#include "load.h"

void save_img(struct image img, int allocated)
{
	char info[MAX_LEN], *new_img_name;
	fgets(info, sizeof(info), stdin);
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		new_img_name = strtok(info, " ");
		new_img_name[strcspn(new_img_name, "\n")] = '\0';
		FILE *out = fopen(new_img_name, "w");
		if (!out) {
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
			//la load, transform orice valoare binara
			//pentru a le putea folosi in operatii,
			//deci pentru scrierea matricii este suficient
			//sa copiez fiecare termen ca atare
			for (int i = 0; i < img.y2; i++) {
				for (int j = 0; j < img.x2; j++)
					if (img.format == 2 || img.format == 5) {
						fprintf(out, "%d ", (int)round(img.matrix[i][j].grey));
					} else {
						fprintf(out, "%d ", (int)round(img.matrix[i][j].red));
						fprintf(out, "%d ", (int)round(img.matrix[i][j].green));
						fprintf(out, "%d ", (int)round(img.matrix[i][j].blue));
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
			//din moment ce fiecare valoare poate fi cuprinsa
			//intr-un singur byte, voi folosi un tip de date
			//care sa satisfaca aceasta conditie (unsigned, deoarece
			//am observat ca pentru valori mai mare de 128, pe un char
			//simplu ultimul bit era considerat de semn si obtineam valori
			//negative)
			//apoi, facand uz de functia fwrite scriu fiecare byte in fisier
			for (int i = 0; i < img.y2; i++)
				for (int j = 0; j < img.x2; j++)
					if (img.format == 5 || img.format == 2) {
						unsigned char pix;
						pix = round(img.matrix[i][j].grey);
						fwrite(&pix, sizeof(unsigned char), 1, out);
					} else {
						unsigned char pix;
						pix = round(img.matrix[i][j].red);
						fwrite(&pix, sizeof(char), 1, out);
						pix = round(img.matrix[i][j].green);
						fwrite(&pix, sizeof(char), 1, out);
						pix = round(img.matrix[i][j].blue);
						fwrite(&pix, sizeof(char), 1, out);
					}
		}
		fclose(out);
		printf("Saved %s\n", new_img_name);
	}
}
