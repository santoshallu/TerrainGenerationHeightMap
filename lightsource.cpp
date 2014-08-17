#include "lightsource.h"
#define PI 3.14
// Draw axis, w/specified length
void drawLightsource() {


	

	GLfloat vertices[720];
	for (int i = 0; i < 720; i += 2) {
		// x value
		vertices[i] = (cos((i / 2 * (PI / 180))) * 0.4); // x=r *cos(theta)
		// y value
		vertices[i + 1] = (sin((i / 2 * (PI / 180))) * 0.6);// y= r*sin(theta)
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
}
