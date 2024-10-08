// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "histogram.h"
#include "select.h"

void select_img(struct image *img, int allocated)
{
	int x1 = NUMBER_NO_ONE_WOULD_THINK_OF, y1 = NUMBER_NO_ONE_WOULD_THINK_OF;
	int x2 = NUMBER_NO_ONE_WOULD_THINK_OF, y2 = NUMBER_NO_ONE_WOULD_THINK_OF;
	char line[MAX_LEN];
	fgets(line, sizeof(line), stdin);
	if (allocated == 0) {
		printf("No image loaded\n");
		return;
	}
	if (strstr(line, "ALL")) {
		img->sel.x1 = 0;
		img->sel.y1 = 0;
		img->sel.x2 = img->x2;
		img->sel.y2 = img->y2;
		printf("Selected ALL\n");
		return;
	}
	int check = sscanf(line, " %d %d %d %d\n", &x1, &y1, &x2, &y2);
	//verific daca numarul de coordonate citite este 4
	//(am aflat prea tarziu ca sscanf imi returneaza numarul
	//de elemente citite ;( )
	int ouchie = 0;
	if (x1 == NUMBER_NO_ONE_WOULD_THINK_OF)
		ouchie = 1;
	if (x2 == NUMBER_NO_ONE_WOULD_THINK_OF)
		ouchie = 1;
	if (y1 == NUMBER_NO_ONE_WOULD_THINK_OF)
		ouchie = 1;
	if (y2 == NUMBER_NO_ONE_WOULD_THINK_OF)
		ouchie = 1;
	if (ouchie == 1) {
		printf("Invalid command\n");
	} else {
		if (x1 > img->x2 || x2 > img->x2 || y1 > img->y2 || y2 > img->y2) {
			printf("Invalid set of coordinates\n");
		} else {
			if (x1 < 0 || y1 < 0 || x2 == x1 || y2 == y1) {
				printf("Invalid set of coordinates\n");
			} else {
				if (x1 > x2) {
					int aux = x1;
					x1 = x2;
					x2 = aux;
				}
				if (y1 > y2) {
					int aux = y1;
					y1 = y2;
					y2 = aux;
				}
				img->sel.x1 = x1;
				img->sel.y1 = y1;
				img->sel.x2 = x2;
				img->sel.y2 = y2;
				printf("Selected %d %d ", img->sel.x1, img->sel.y1);
				printf("%d %d\n", img->sel.x2, img->sel.y2);
			}
		}
	}
}
