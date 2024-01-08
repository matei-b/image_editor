// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "load.h"

void image_load(struct image *img, int *allocated)
{
	//eliberez memoria la fiecare noua apelare a lui LOAD
	if ((*allocated) == 1)
		free_matrix(img->y2, img->matrix);
	//in buffer citesc magic word-ul
	char buffer[3], img_name[MAX_LEN];
	struct pixel **matrix;
	scanf("%s", img_name);
	FILE *in = fopen(img_name, "rt");
	if (!in) {
		fprintf(stdout, "Failed to load %s\n", img_name);
		(*allocated) = 0;
		return;
	}
	(*allocated) = 1;
	img->sel.x1 = 0;
	img->sel.y1 = 0;
	fgets(buffer, sizeof(buffer), in);
	buffer[strcspn(buffer, "\n")] = '\0';
	img->format = buffer[1] - '0';
	fscanf(in, "%d%d%d\n", &img->x2, &img->y2, &img->colour_range);
	img->sel.x2 = img->x2;
	img->sel.y2 = img->y2;
	matrix = matrix_mem_alloc(img->x2, img->y2);
	for (int i = 0; i < img->y2; i++)
		for (int j = 0; j < img->x2; j++) {
			//daca valorile nu sunt comprimate
			//doar citesc fiecare valoare din fisier
			if (img->format == 3) {
				fscanf(in, "%f", &matrix[i][j].red);
				fscanf(in, "%f", &matrix[i][j].green);
				fscanf(in, "%f", &matrix[i][j].blue);
			}
			if (img->format == 2)
				fscanf(in, "%f", &matrix[i][j].grey);
			//din moment ce fiecare valoare poate fi cuprinsa
			//intr-un singur byte, voi folosi un tip de date
			//care sa satisfaca aceasta conditie (unsigned, deoarece
			//am observat ca pentru valori mai mare de 128, pe un char
			//simplu ultimul bit era considerat de semn si obtineam valori
			//negative)
			//apoi, facand uz de functia fread citesc fiecare byte din fisier
			//conversia catre float o sa o fac pur si simplu prin egalarea
			//char-ului (care are valoarea byte-ul citit)
			//cu elementul corespunzator din matricea de elemente (float)
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
