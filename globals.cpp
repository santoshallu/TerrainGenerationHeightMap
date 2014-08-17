#include <stdlib.h>
#include <stdio.h>
#include "globals.h"

int readPPM(char *filename, struct terrain *terr)
{
	FILE *input = fopen(filename, "rb");
    int width, height, size;
	int *buffer;

	fscanf(input, "P6\n");
	fscanf(input, "%d", &width);
	fscanf(input, "%d", &height);
    fscanf(input, "%*d\n");
	size = width * height;
	terr->width = width;
	terr->height = height;
	terr->pixels = new int[size];

	buffer = terr->pixels;
	for (int i = 0; i < size; i++, buffer++) {
		fread(buffer, 1, 3, input);
    }

    return 0;
}


