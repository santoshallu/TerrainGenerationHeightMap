/*
* view.cpp
* Author : Srinivasa Santosh Kumar Allu
* A-number : A01900937
*/
#include "view.h"
#include <GL/glut.h>

// initializes camera angle and view position to look at
void view_init()
{
	float cam[3] = { 30, 30, 30 }; // camera angle
	float pos[3] = { 50, 0, 50 };// point to look at	
	gluLookAt(cam[0], cam[1], cam[2], pos[0], pos[1], pos[2], 0, 1, 0); // setting camera or eye postion and position at and setting upvector to one
}

// updates camera angle and view position to look at
void view_update(int viewx, int viewy, int viewz, int posx, int posy, int posz)
{	
	glLoadIdentity();
	gluLookAt(viewx, viewy, viewz, posx , posy, posz, 0, 1, 0); // setting camera or eye postion and position at and setting upvector to one
}
