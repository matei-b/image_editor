#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "load.h"
#include "save.h"

int main()
{
	int allocated = 0;
	char command[MAX_LEN];
	struct image img;
	while (strcmp(command, "EXIT") != 0) {
		scanf("%s", command);
		if (strcmp(command, "LOAD") == 0) {
			image_load(&img, &allocated);
		}
		if (strcmp(command, "SAVE") == 0) {
			save(img, allocated);
		}
	}
	return 0;
}
