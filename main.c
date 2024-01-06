#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "load.h"
#include "select.h"
#include "histogram.h"
#include "equalize.h"
#include "apply.h"
#include "crop.h"
#include "save.h"

int main()
{
	int allocated = 0, ok, done_fr = 0;
	char command[MAX_LEN];
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
		if (strcmp(command, "APPLY") == 0) {
			apply_ker(&img, allocated);
			ok = 1;
		}
		if (strcmp(command, "CROP") == 0) {
			crop_img(&img, allocated);
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
		if (ok == 0)
			printf("Invalid command\n");
	}
	return 0;
}