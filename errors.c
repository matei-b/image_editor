#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "image.h"
#include "errors.h"

int open_error(FILE *in, char img_name[MAX_LEN])
{
	if (in == NULL) {
		fprintf(stderr, "Failed to load %s", img_name);
		exit(-1);
	}
	return 0;
}