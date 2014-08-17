/*
* display.h
* Author : Srinivasa Santosh Kumar Allu
* A-number : A01900937
*/

#ifndef DISP_H
#define DISP_H



#include <iostream>
#include <string>
#include "globals.h"
#include "lightsource.h"
#include <GL/glut.h>



// functions to move light source
void displayLightx(int displacement);
void displayLighty(int displacement);
void displayLightz(int displacement);

// functions to move the model
void displayRotatex(int direction);
void displayRotatey(int direction);
void displayRotatez(int direction);

void displayDraw();// function which draws ply model
void displayInit();// functions which selects and initalizes ply model

void instructions();// displays instructions in console on how to use the model

void loadTerrain();
void loadTextureMap(terrain tex);
void resize(int width, int height);
void loadPPM();


#endif /* DISP_H */