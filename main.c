#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "image.h"
#include "load.h"

int main()
{
	char line[MAX_LEN];
	char *command;
	fgets(line, sizeof(line), stdin);
	command = strtok(line, " ");
	command[strcspn(command, "\n")] = '\0';
	if (strcmp(command, "LOAD") == 0) {
		image_load();
	}
	return 0;
}