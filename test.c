#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "equalize.h"
#include "histogram.h"
#include "apply.h"

int clamp(double num)
{
	if (num < 0)
		return 0;
	if (num > 255)
		return 255;
	return num;
}

int main() 
{
	float sum = 0;
	float ker[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
	float matrix[3][3] = {{160, 143, 144},{149, 125, 133},{101, 154, 135}};
	int dir_x[] = {0, 0, 0, 1, 1, 1, -1, -1, -1};
	int dir_y[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int i = 0;
	for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				ker[i][j] = ker[i][j]/16.;
				printf("%.4f ", ker[i][j]);
			}
		printf("\n");
	}
	while (i < 9) {
		sum += matrix[1 + dir_x[i]][1 + dir_y[i]] * ker[1 + dir_x[i]][1 + dir_y[i]];
		printf("%.0f ", sum);
		i++;
	}
	printf("\n");
	sum = clamp(sum);
	printf("%.0f\n", sum);
	return 0;
}