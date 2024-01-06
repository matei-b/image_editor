#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "select.h"

void select_img(struct image *img, int allocated)
{
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
	char line[MAX_LEN];
	fgets(line, sizeof(line), stdin);
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		if (strstr(line, "ALL")) {
			img->sel.x1 = 0;
			img->sel.y1 = 0;
			img->sel.x2 = img->x2;
			img->sel.y2 = img->y2;
			printf("Selected ALL\n");
		} else {
			sscanf(line, " %d %d %d %d\n", &x1, &y1, &x2, &y2);
			int ouchie = 0;
			if (x1 == -1)
				ouchie = 1;
			if (x2 == -1)
				ouchie = 1;
			if (y1 == -1)
				ouchie = 1;	
			if (y2 == -1)
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
						printf("Selected %d %d %d %d\n", img->sel.x1, img->sel.y1, img->sel.x2, img->sel.y2);
					}
				}
			}
		}
	}
}