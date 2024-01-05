#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "load.h"
#include "select.h"
#include "histogram.h"
#include "save.h"

int main()
{
	int allocated = 0, ok, done_fr = 0;
	char command[MAX_LEN];
	struct image img;
	while (strcmp(command, "EXIT") != 0 || done_fr == 0) {
		ok = 0;
		scanf("%s", command);
		if (strcmp(command, "LOAD") == 0) {
			image_load(&img, &allocated);
			ok = 1;
		}
		if (strcmp(command, "SAVE") == 0) {
			save(img, allocated);
			ok = 1;
		}
		if (strcmp(command, "EXIT") == 0) {
			if (allocated == 0) {
				printf("No image loaded\n");
			} else {
				free_matrix(img.y2, img.matrix);
				done_fr = 1;
				return 0;
			}
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
		if (ok == 0)
			printf("Invalid command\n");
	}
	return 0;
}