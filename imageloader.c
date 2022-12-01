/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	FILE *imagefile = fopen(filename, "rw");
	if (imagefile == NULL){
		printf("The imagefile %s is NULL and cannot be openned\n", filename);
		return NULL;
	}
	Image *img = (Image*)malloc(sizeof(Image));
	char format[3];
	int colorRange;
	fscanf(imagefile, "%s", format);
	if (format[0] != 'P' || format[1] != '3'){
		printf("Wrong format\n");
		return NULL;
	}
	fscanf(imagefile, "%u", &img->cols);
	fscanf(imagefile, "%u", &img->rows);
	fscanf(imagefile, "%u", &colorRange);
	if (img->cols < 0 || img->rows < 0 || colorRange != 255){
		printf("Wrong ppm format\n");
		return NULL;
	}
	int totpixels = img->cols * img->rows;
	img->image = (Color**)malloc(sizeof(Color*) * totpixels);
	for (int i = 0; i < totpixels; i++){
		*(img->image+i) = (Color*)malloc(sizeof(Color));
		Color *pixel = *(img->image+i);
		fscanf(imagefile, "%hhu %hhu %hhu", &pixel->R, &pixel->G, &pixel->B);
	}
	fclose(imagefile);
	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n%d %d\n255\n", image->cols, image->rows);
	Color **p = image->image;
	for (int i = 0; i < image->rows; i++){
		for (int j =0; j < image->cols - 1; j++){
			printf("%3hhu %3hhu %3hhu   ", (*p)->R, (*p)->G, (*p)->B);
			p++;
		}
		printf("%3hhu %3hhu %3hhu\n", (*p)->R, (*p)->G, (*p)->B);
		p++;
	}
}

//Frees an image
void freeImage(Image *image)
{
	int totpixels = image->cols * image->rows;
	for (int i = 0; i < totpixels; i++){
		free(*(image->image + i));
	}
	free(image->image);
	free(image);
}
