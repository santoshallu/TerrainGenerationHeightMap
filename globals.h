/*
* canvas.h
* Author : Srinivasa Santosh Kumar Allu
* A-number : A01900937
*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <GL/glut.h>

struct vertex
{
	GLfloat x, y, z;
};

struct textures
{
	GLfloat x, y;
};

struct normals
{
	GLfloat x, y, z;
};


 struct terrain {
	int width;
	int height;
	int *pixels;
} ;

# define PIXEL(tr,x,y)	 ((((tr).pixels[(x)+(tr).width*(y)])>> 0)&0xFF) //reading red color as it is a grey scale image so chose any of rgb
int readPPM(char *filename, struct terrain *ter); // reads the ppm file

#endif //end GLOBALS_H