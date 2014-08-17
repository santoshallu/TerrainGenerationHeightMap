
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "globals.h"

#include "display.h"
#include "view.h"


// Initializes rendering
void initRendering()
{
	glClearColor(0, 0, 0, 1);// setting background to black
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);    // Enable Lighting
	glEnable(GL_LIGHT0);      // first light source 
	//glEnable(GL_LIGHT1);   // second light source 
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE); //Automatically normalizes
	glEnable(GL_TEXTURE_2D);

}

//drawing scence
static void initDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	displayDraw(); // calls displaydraw in display class
	glutSwapBuffers();
}

//keyboard controls
static void initkeyboard(unsigned char key, int x, int y)
{
	switch (key) {
		/* rotates in positive and negative x direction */
	case 'x':
		displayRotatex(-1);
		break;
	case 'X':
		displayRotatex(1);
		break;
		/* rotates in positive and negative y direction */
	case 'y':
		displayRotatey(-1);
		break;
	case 'Y':
		displayRotatey(1);
		break;
		/* rotates in positive and negative z direction */
	case 'z':
		displayRotatez(-1);
		break;
	case 'Z':
		displayRotatez(1);
		break;
	}

	glutPostRedisplay();
}


//special controls which are on right side of key board
static void initSpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		displayLightz(-1);
		break;
	case GLUT_KEY_RIGHT:
		displayLightz(1);
		break;
	case GLUT_KEY_UP:
		displayLighty(1);
		break;
	case GLUT_KEY_DOWN:
		displayLighty(-1);
		break;
	case GLUT_KEY_PAGE_UP:
		displayLightx(1);
		break;
	case GLUT_KEY_PAGE_DOWN:
		displayLightx(-1);
		break;
	}
	glutPostRedisplay();
}


void initControl()
{
	glutSpecialFunc(initSpecial);
	glutKeyboardFunc(initkeyboard);
}

int main() {

	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cs5400: final project");	
	initControl();	
	initRendering();
	loadPPM();
	glutDisplayFunc(initDisplay);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}


