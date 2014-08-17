#include "display.h"

#include "view.h"

const int terrainHeight = 512;
const int terrainWidth = 512;

terrain mountain;
terrain bGround;




int  viewx = 0, viewy = 30, viewz = 0;
float lightx = 30, lighty = 30, lightz = 30;


vertex *vertice = new vertex[1572864];       //512 * 512 * 6
textures *textured = new textures[1572864];  //512 * 512 * 6
normals *norms = new normals[1572864];       //512 * 512 * 6

float vertices[terrainHeight][terrainWidth][3];
float faceNormal1[terrainHeight][terrainWidth][3];
float faceNormal2[terrainHeight][terrainWidth][3];
float vertexNormals[terrainHeight][terrainWidth][3];



void displayLightx(int direction)
{
	lightx += direction;
}

void displayLighty(int direction)
{
	lighty += direction;
}

void displayLightz(int direction)
{
	lightz += direction;
}


void displayRotatex(int move)
{
	viewx += move;
}

void displayRotatey(int move)
{
	viewy += move;
}

void displayRotatez(int move)
{
	viewz += move;
}





void normalize(float* v)
{
	float length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] /= length;
	v[1] /= length;
	v[2] /= length;
}

float* normal(float* p1, float* p2, float* p3)
{

	float va[3], vb[3];

	/* calculate Vector1 and Vector3 */
	for (int i = 0; i < 3; i++)
	{
		va[i] = p3[i] - p1[i];
	}

	/* calculate Vector2 and Vector3 */
	for (int i = 0; i < 3; i++)
	{
		vb[i] = p2[i] - p1[i];
	}

	float norm[3];

	/* cross product */
	norm[0] = va[1] * vb[2] - vb[1] * va[2];
	norm[1] = vb[0] * va[2] - va[0] * vb[2];
	norm[2] = va[0] * vb[1] - vb[0] * va[1];
	normalize(norm);

	return norm;
}



void calNormal()
{
	float *trianglesplit1, *trianglesplit2;
	int xcooord[2] = { 0, 1 };

	for (int x = 0; x < mountain.width - 1; ++x){
		for (int y = 0; y < mountain.height - 1; ++y){
			/*
			computing two triangles
			p1-------p2
			| \      |
			|   \    |
			|     \  |
			|       \|
			p3-------p4
			*/

			//storing vertices and scaling the mountains
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; j++)
				{
					vertices[x + i][y + j][0] = (x + i) / 15.0;
					vertices[x + i][y + j][1] =PIXEL(mountain, x+i, y+j) / 15.0;
					vertices[x + i][y + j][2] = (y + j) / 15.0;
				}
			}

			trianglesplit1 = normal(vertices[x][y], vertices[x + 1][y], vertices[x + 1][y + 1]);

			faceNormal1[x][y][0] = trianglesplit1[0];
			faceNormal1[x][y][1] = trianglesplit1[1];
			faceNormal1[x][y][2] = trianglesplit1[2];

			trianglesplit2 = normal(vertices[x][y], vertices[x + 1][y + 1], vertices[x][y + 1]);

			faceNormal2[x][y][0] = trianglesplit2[0];
			faceNormal2[x][y][1] = trianglesplit2[1];
			faceNormal2[x][y][2] = trianglesplit2[2];


			/*Calculating normals for vertices

			|/   |/   |/   |/
			...--+----U----UR---+--...
			/|   /| 2 /|   /|           Y
			/ |  / |  / |  / |           ^
			| /  | /  | /  | /         |
			|/ 1 |/ 3 |/   |/          |
			...--L----P----R----+--...      +-----> X
			/| 6 /| 4 /|   /|
			/ |  / |  / |  / |
			| /5 | /  | /  | /
			|/   |/   |/   |/
			...--DL---D----+----+--...
			/|   /|   /|   /|

			*/
			vertexNormals[x][y][0] = faceNormal1[x][y][0] + faceNormal2[x][y][0] + faceNormal2[x][y - 1][0] + faceNormal1[x][y - 1][0] + faceNormal1[x - 1][y - 1][0] + faceNormal2[x - 1][y - 1][0] + faceNormal2[x - 1][y][0];
			vertexNormals[x][y][1] = faceNormal1[x][y][1] + faceNormal2[x][y][1] + faceNormal2[x][y - 1][1] + faceNormal1[x][y - 1][1] + faceNormal1[x - 1][y - 1][1] + faceNormal2[x - 1][y - 1][1] + faceNormal2[x - 1][y][1];
			vertexNormals[x][y][2] = faceNormal1[x][y][2] + faceNormal2[x][y][2] + faceNormal2[x][y - 1][2] + faceNormal1[x][y - 1][2] + faceNormal1[x - 1][y - 1][2] + faceNormal2[x - 1][y - 1][2] + faceNormal2[x - 1][y][2];

		}
	}
}



void drawMountain()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);

	glTexCoordPointer(2, GL_FLOAT, 0, textured);
	glVertexPointer(3, GL_FLOAT, 0, vertice);
	glNormalPointer(GL_FLOAT, 0, norms);
	glDrawArrays(GL_TRIANGLES, 0, 3 * 524288);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
	glDisable(GL_TEXTURE_2D);
}

void loadMountain()
{

	int count = 0;
	glEnable(GL_TEXTURE_2D);
	for (int x = 0; x < mountain.width - 1; ++x)
	{
		for (int y = 0; y < mountain.height - 1; ++y)
		{

			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; j++)
				{
					if (i == 0 && j == 1)
					{
						continue;
					}
					textured[count].x = (float)(x + i) / (float)512;
					textured[count].y = (float)(y + j) / (float)512;


					vertice[count].x = vertices[x + i][y + j][0];
					vertice[count].y = vertices[x + i][y + j][1];
					vertice[count].z = vertices[x + i][y + j][2];

					norms[count].x = vertexNormals[x + i][y + j][0];
					norms[count].y = vertexNormals[x + i][y + j][1];
					norms[count].z = vertexNormals[x + i][y + j][2];

					count++;
				}
			}


			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; j++)
				{
					if (i == 1 && j == 0)
					{
						continue;
					}
					textured[count].x = (float)(x + i) / (float)512;
					textured[count].y = (float)(y + j) / (float)512;


					vertice[count].x = vertices[x + i][y + j][0];
					vertice[count].y = vertices[x + i][y + j][1];
					vertice[count].z = vertices[x + i][y + j][2];

					norms[count].x = vertexNormals[x + i][y + j][0];
					norms[count].y = vertexNormals[x + i][y + j][1];
					norms[count].z = vertexNormals[x + i][y + j][2];

					count++;
				}
			}

		}
	}

}


void lightingEffects()
{

	// Adding Ambient light
	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.3, 0.3, 0.3)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Adding positioned light

	GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat lightPosition[] = { lightx, lighty, lightz, 1.0f }; // positioned at based on user input
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	/*
	float diffuseLight1[] = { 0.8f, 0.4f, 0.4f, 1 };
	float lightPosition1[] = { -300, 100, -100, 1 };

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);*/
}
void displayDraw() {

	view_update(viewx, viewy, viewz, 50, 0, 50);
	lightingEffects();

	calNormal();
	
	loadMountain();
	drawMountain();


	// for smoother animation
}

void loadTexture(terrain pix) {
	GLuint texture;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pix.width, pix.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pix.pixels);

	// repeating the pixels
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//displaying in block level instead of blur
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


void resize(int width, int height)
{

	glViewport(0, 0, width, height);// change view port after resize based on height and width
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, width / height, 1, 500); // setting view angle to 100 and distance from view to 500 and aspect ratio to size of screen width to screen height
	glMatrixMode(GL_MODELVIEW);
}


void loadPPM()
{
	std::string heightmap, theme;
	terrain height;
	std::cout << "enter heightmap ...\n\n" << std::endl;
	std::cin >> heightmap;
	heightmap += ".ppm";

	char *filename = new char[heightmap.length() + 1];
	strcpy(filename, heightmap.c_str());
	readPPM(filename, &height);

	terrain texture;
	std::cout << "enter texture ...\n\n" << std::endl;
	std::cin >> theme;
	theme += ".ppm";
	char *filename2 = new char[theme.length() + 1];
	strcpy(filename2, theme.c_str());
	readPPM(filename2, &texture);

	loadTexture(texture);
	mountain = height;
	bGround = texture;

}


