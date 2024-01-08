// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "load.h"
#include "select.h"
#include "histogram.h"
#include "equalize.h"
#include "rotate.h"
#include "crop.h"
#include "apply.h"
#include "save.h"

//folosesc variabila allocated ca sa vad daca am
//memorie alocata de load, iar sirul ignore
//pentru a ma asigura ca ignor orice parametru
//al unei comenzi gresite
//done_fr doar imi spune ca am facut apel
//catre comanda EXIT, iar sarcinile sunt
//done F(or)R(eal)
int main(void)
{
	int allocated = 0, ok, done_fr = 0;
	char command[MAX_LEN], ignore[MAX_LEN];
	struct image img;
	while (!done_fr) {
		ok = 0;
		scanf("%s", command);
		if (strcmp(command, "LOAD") == 0) {
			image_load(&img, &allocated);
			ok = 1;
		}
		if (strcmp(command, "SELECT") == 0) {
			select_img(&img, allocated);
			ok = 1;
		}
		if (strcmp(command, "HISTOGRAM") == 0) {
			histogram_img(img, allocated);
			ok = 1;
		}
		if (strcmp(command, "EQUALIZE") == 0) {
			equalize_img(&img, allocated);
			ok = 1;
		}
		if (strcmp(command, "ROTATE") == 0) {
			rotate_img(&img, allocated);
			ok = 1;
		}
		if (strcmp(command, "CROP") == 0) {
			crop_img(&img, allocated);
			ok = 1;
		}
		if (strcmp(command, "APPLY") == 0) {
			apply_ker(&img, allocated);
			ok = 1;
		}
		if (strcmp(command, "SAVE") == 0) {
			save_img(img, allocated);
			ok = 1;
		}
		if (strcmp(command, "EXIT") == 0) {
			if (allocated == 0)
				printf("No image loaded\n");
			else
				free_matrix(img.y2, img.matrix);
			done_fr = 1;
			ok = 1;
		}
		if (ok == 0) {
			printf("Invalid command\n");
			fgets(ignore, sizeof(ignore), stdin);
		}
	}
	return 0;
}
