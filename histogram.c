#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"
#include "save.h"
#include "histogram.h"

#define NUMBER_NO_ONE_WOULD_THINK_OF 190301239

void histogram_img(struct image img, int allocated)
{
	int i = 0, j = 0, nononono = NUMBER_NO_ONE_WOULD_THINK_OF;
	//stelute binuri
	char line[MAX_LEN];
	fgets(line, sizeof(line), stdin);
	sscanf(line, " %d %d %d\n", &i, &j, &nononono);
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		if (i == 0 || j == 0 || nononono != NUMBER_NO_ONE_WOULD_THINK_OF) {
			printf("Invalid command\n");
		} else {
			if (img.format == 3 || img.format == 6) {
				printf("Black and white image needed\n");
			} else {
				float x = i, y = j;
				float freq[256] = {0}, freq_bins[256] = {0};
				float max_freq = 0;
				for (int i = 0; i < img.y2; i++)
					for (int j = 0; j < img.x2; j++)
						freq[(int)round(img.matrix[i][j].grey)]++;
				int i = 0, j = -1, aux, num_val = 256/y;
				int num_stars;
				while (i < 256) {
					j++;
					aux = num_val;
					while (aux > 0 && i < 256) {
						freq_bins[j] += freq[i];
						i++;
						aux--;
					}
					if(max_freq < freq_bins[j])
						max_freq = freq_bins[j];
				}
				printf("%d\n", j);
				for (i = 0; i < j + 1; i++) {
					num_stars = (int)((freq_bins[i] * x)/max_freq);
					printf("%d\t|\t", num_stars);
					for (int k = 0; k < num_stars; k++)
						printf("*");
					printf("\n");
				}
			}
		}
	}
}