#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"
#include "save.h"
#include "histogram.h"

int check_decimals(float y)
{
	int aux;
	if ((float)((256.0/y) - (256/y)) != 0.)
		aux = 256/y + 1;
	else aux = 256/y;
	return aux;
}

void histogram_img(struct image img, int allocated)
{
	float x, y;
	//stelute binuri
	scanf("%f %f", &x, &y);
	if (allocated == 0) {
		printf("No image loaded\n");
	} else {
		if (img.format == 3 || img.format == 6) {
			printf("Black and white image needed\n");
		} else {
			float freq[256] = {0}, freq_bins[256] = {0};
			float max_freq = 0;
			for (int i = 0; i < img.y2; i++)
				for (int j = 0; j < img.x2; j++)
					freq[(int)round(img.matrix[i][j].grey)]++;
			int i = 0, j = -1, aux, num_val = check_decimals(y);
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
			for (i = 0; i <= j; i++) {
				num_stars = (int)((freq_bins[i] * x)/max_freq);
				printf("%d\t|\t", num_stars);
				for (int k = 0; k < num_stars; k++)
					printf("*");
				printf("\n");
			}
		}
	}
}