//Coded by Tyler Hennig, Abraham Solis, Rafael Amaro, Daniel Rodriguez
//Computer Graphics Project

#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

enum pages {MAIN, DIFF, GAME};
enum difficulty {EASY, HARD};
enum color {RED, GREEN, BLUE, YELLOW};
enum shape {CUBE, PYRAMID, SPHERE};

char title[] = "Final Project";  // Windowed mode's title
int windowWidth = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX = 50;      // Windowed mode's top-left corner x
int windowPosY = 50;      // Windowed mode's top-left corner y
int refreshMillis = 30;      // Refresh period in milliseconds
bool fullScreenMode = true; // Full-screen or windowed mode?
bool isSequenceComplete = false;

int currentShape = CUBE;
int shapeID = CUBE;
int currentColor = RED;
int colorID = 0;
int currentPage = MAIN;
int currentDiff = EASY;
int num;
int roundNum = 1;
int frames = 0;
int colorVIndex = 0;
int shapeVIndex = 0;
vector<int> colorV;
vector<int> shapeV;
vector<int> selectionV;

#define PI 3.1415927
int lastMouseX;
int lastMouseY;
bool mouseDown = false;
GLfloat angleCubeX = 0.0f;     // Rotational angle for cube
GLfloat angleCubeY = 0.0f;     // Rotational angle for cube
int selectIndex = 1;
int indexSkin = 0;
GLfloat selectPos = 0;
int i, x, y;
GLfloat skin[3][3] = { 1.0f, 0.0f, 0.0f,		//red
					  0.0f, 1.0f, 0.0f,		//green
					  0.0f, 0.0f, 1.0f };	//blue
GLfloat angleIdle = 0.0f;
GLfloat transIdle = 0.0f;
int screenIndex = 0;
int selectedIndex = 1;



void gameDisplay();
void gameEasyDisplay();
void gameHardDisplay();
void drawCube();
void drawPyramid();
void drawSphere();
void dispCube();
void dispSphere();
void dispPyramid();
void dispSquare();

void sequenceComplete();

void generateRandomVector() {
	srand(time(0));
	colorV.clear();
	for (int i = 0; i < roundNum; i++) {
		num = rand() % 4 + 1;
		colorV.push_back(num);
	}
}

void generateShapeVector() {
	shapeV.clear();
	for (int i = 0; i < roundNum; i++) {
		num = colorV.at(i);
		num = num * 1234;
		num = num % 3 + 1;
		shapeV.push_back(num);
	}
}

void resetVectors() {
	colorV.clear();
	shapeV.clear();
	selectionV.clear();
}
void resetGame() {
	resetVectors();
	roundNum = 1;
	isSequenceComplete = false;
	frames = 0;
	int colorVIndex = 0;
	int shapeVIndex = 0;
}

void newGame() {
	cout << "RUNNING NEW GAME CODE" << endl;
	frames = 65;
	colorVIndex = 0;
	roundNum = 1;
	generateRandomVector();
	generateShapeVector();

	colorID = colorV[0];
	shapeID = shapeV[0];

	cout << "First color/shape is:  " << colorID << " " << shapeID << endl;
}

void updateColor() {
	switch (currentColor) {
	case RED:
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case GREEN:
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case BLUE:
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case YELLOW:
		glColor3f(1.0f, 1.0f, 0.0f);
		break;
	}
}


void updateShape() {
	switch (currentShape) {
	case CUBE:
		drawCube();
		break;
	case PYRAMID:
		drawPyramid();
		break;
	case SPHERE:
		drawSphere();
		break;
	}
}

void drawCube() {
	glTranslatef(0.0f, -2.0f, -7.0f);  // Move right and into the screen

	glBegin(GL_QUADS);
	glVertex2f(0.2f, 0.2f);
	glVertex2f(-0.2f, 0.2f);
	glVertex2f(-0.2f, -0.2f);
	glVertex2f(0.2f, -0.2f);
	glEnd();

}
void drawPyramid() {
	glTranslatef(0.0f, -2.0f, -7.0f);  // Move right and into the screen

	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.25f);
	glVertex2f(-0.2f, -0.15f);
	glVertex2f(0.2f, -0.15f);
	glEnd();
}
void drawSphere() {
	glTranslatef(0.0f, -2.0f, -7.0f);  // Move right and into the screen

	glutWireSphere(0.25, 25, 25);
}

void dispCube() {
	glTranslatef(0.0f, 1.5f, -7.0f);  // Move right and into the screen
	glRotatef(30.0f, 1.0f, 1.0f, 0.0f); // Rotate 30 degrees
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		// Top face (y = 1.0f)
		// Define vertices in counter-clockwise (CCW) order with normal pointing out
	switch (colorID-1)
	{
	case 0:
	{
		glColor3f(0.9f, 0.0f, 0.1f);     // Red
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// Bottom face (y = -1.0f)
		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Front face  (z = 1.0f)
		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Back face (z = -1.0f)
		glColor3f(1.0f, 0.0f, 0.5f);     // Red
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		// Left face (x = -1.0f)
		glColor3f(0.5f, 0.0f, 0.1f);     // Red
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// Right face (x = 1.0f)
		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();  // End of drawing color-cube
	}
	break;
	case 1:
	{
		glColor3f(0.1f, 0.9f, 0.f);     // Green
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// Bottom face (y = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);     // Green
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Front face  (z = 1.0f)
		glColor3f(0.1f, 1.0f, 0.0f);     // Green
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Back face (z = -1.0f)
		glColor3f(0.0f, 1.0f, 0.0f);     // Green
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		// Left face (x = -1.0f)
		glColor3f(0.1f, 0.5f, 0.0f);     // Green
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// Right face (x = 1.0f)
		glColor3f(0.0f, 1.0f, 0.0f);     // Green
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();  // End of drawing color-cube
	}
	break;
	case 2:
	{
		glColor3f(0.1f, 0.0f, 0.9f);     // Blue
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// Bottom face (y = -1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Front face  (z = 1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Back face (z = -1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		// Left face (x = -1.0f)
		glColor3f(0.1f, 0.0f, 0.5f);     // Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// Right face (x = 1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();  // End of drawing color-cube
	}
	break;
	case 3:
	{
		glColor3f(0.9f, 0.9f, 0.0f);     // Yellow
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// Bottom face (y = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Front face  (z = 1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Back face (z = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		// Left face (x = -1.0f)
		glColor3f(0.8f, 0.9f, 0.0f);     // Yellow
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// Right face (x = 1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();  // End of drawing color-cube
	}
	break;
	}
}
void dispSphere()
{
	glTranslatef(0.0f, 1.5f, -7.0f);  // Move into the screen
	switch (colorID-1)
	{
	case 0:
	{
		glColor3f(1.0f, 0.0f, 0.0f);       // Red
		glRotatef(30.0f, 1.0f, 1.0f, 0.0f); // Rotate 30 degree
		glutWireSphere(1.0, 25, 25);
	}
	break;
	case 1:
	{
		glColor3f(0.0f, 1.0f, 0.0f);       // Green
		glRotatef(30.0f, 1.0f, 1.0f, 0.0f); // Rotate 30 degree
		glutWireSphere(1.0, 25, 25);
	}
	break;
	case 2:
	{
		glColor3f(0.0f, 0.0f, 1.0f);       // Blue
		glRotatef(30.0f, 1.0f, 1.0f, 0.0f); // Rotate 30 degree
		glutWireSphere(1.0, 25, 25);
	}
	break;
	case 3:
	{
		glColor3f(1.0f, 1.0f, 0.0f);       // Yellow
		glRotatef(30.0f, 1.0f, 1.0f, 0.0f); // Rotate 30 degree
		glutWireSphere(1.0, 25, 25);
	}
	break;
	}
}
void dispPyramid() {
	glTranslatef(0.0f, 1.5f, -7.0f);  // Move into the screen
	switch (colorID-1)
	{
	case 0:
	{

		glRotatef(10.0f, 1.0f, 1.0f, 0.0f); // Rotate 
		glRotatef(10.0f, 0.0f, 1.0f, 0.0f); // Rotate 
		glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
		// Front
		glColor3f(1.f, 0.0f, 0.0f);     // red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Bottom
		glColor3f(1.0f, 0.0f, 0.0f);     // red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Back
		glColor3f(1.0f, 0.0f, 0.0f);     // red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// Left
		glColor3f(0.9f, 0.0f, 0.1f);       // red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();   // Done drawing the pyramid		
	}
	break;
	case 1:
	{
		glRotatef(10.0f, 1.0f, 1.0f, 0.0f); // Rotate 
		glRotatef(10.0f, 0.0f, 1.0f, 0.0f); // Rotate 
		glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
		// Front
		glColor3f(0.0f, 1.0f, 0.0f);     // green
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Right
		glColor3f(0.0f, 1.0f, 0.0f);     // green
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Back
		glColor3f(0.0f, 1.0f, 0.0f);     // green
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// Left
		glColor3f(0.0f, 0.9f, 0.1f);       // green
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();   // Done drawing the pyramid
	}
	break;
	case 2:
	{
		glRotatef(10.0f, 1.0f, 1.0f, 0.0f); // Rotate 
		glRotatef(10.0f, 0.0f, 1.0f, 0.0f); // Rotate 
		glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
		// Front
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Right
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Back
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// Left
		glColor3f(0.0f, 0.1f, 0.9f);       // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();   // Done drawing the pyramid		
	}
	break;
	case 3:
	{
		glRotatef(10.0f, 1.0f, 1.0f, 0.0f); // Rotate 
		glRotatef(10.0f, 0.0f, 1.0f, 0.0f); // Rotate 
		glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
		// Front
		glColor3f(1.0f, 1.0f, 0.0f);     // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Right
		glColor3f(1.0f, 1.0f, 0.0f);     // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Back
		glColor3f(1.0f, 1.0f, 0.0f);     // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// Left
		glColor3f(0.8f, 0.8f, 0.0f);       // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();   // Done drawing the pyramid		
	}
	break;
	}
}
void dispSquare() {

	switch (colorID-1)
	{
	case 0:
	{

		glTranslatef(0.0f, 1.5f, -7.0f);  // Move right and into the screen
		glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex2f(-1.0f, -1.0f);     // Define vertices in counter-clockwise (CCW) order
		glVertex2f(-1.0f, 1.0f);     //  so that the normal (front-face) is facing you
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glEnd();
	}
	break;
	case 1:
	{

		glTranslatef(0.0f, 1.5f, -7.0f);  // Move right and into the screen
		glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex2f(-1.0f, -1.0f);     // Define vertices in counter-clockwise (CCW) order
		glVertex2f(-1.0f, 1.0f);     //  so that the normal (front-face) is facing you
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glEnd();
	}
	break;
	case 2:
	{

		glTranslatef(0.0f, 1.5f, -7.0f);  // Move right and into the screen
		glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex2f(-1.0f, -1.0f);     // Define vertices in counter-clockwise (CCW) order
		glVertex2f(-1.0f, 1.0f);     //  so that the normal (front-face) is facing you
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glEnd();
	}
	break;
	case 3:
	{

		glTranslatef(0.0f, 1.5f, -7.0f);  // Move right and into the screen
		glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glVertex2f(-1.0f, -1.0f);     // Define vertices in counter-clockwise (CCW) order
		glVertex2f(-1.0f, 1.0f);     //  so that the normal (front-face) is facing you
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glEnd();
	}
	break;
	}
}



void drawCircle(void) {

	double twicePi = 2.0 * 3.142;
	x = 0, y = 0;
	double radius = 0.49;

	glTranslatef(0.0f, 0.46f, 0.0f);
	glColor3f(skin[indexSkin][0], skin[indexSkin][1], skin[indexSkin][2]);
	glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= 20; i++) {
		glVertex2f(
			(x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
		);
	}
	glEnd(); //END
}

void drawTriangle(void) {
	glTranslatef(-1.05f, -0.42f, 2.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(skin[indexSkin][0], skin[indexSkin][1], skin[indexSkin][2]);
	glVertex3f(-0.3f, -0.2f, 1.0f);
	glVertex3f(0.3f, -0.2f, 1.0f);
	glVertex3f(0.0f, 0.3f, 1.0f);
	glEnd();
}

void drawSquare(void) {
	glTranslatef(0.0f, 0.45f, 0.0f);
	glBegin(GL_QUADS);
	//draws square
	glColor3f(skin[indexSkin][0], skin[indexSkin][1], skin[indexSkin][2]);
	glVertex3f(0.45f, 0.45f, 0.0f);
	glVertex3f(-0.45f, 0.45f, 0.0f);
	glVertex3f(-0.45f, -0.45f, 0.0f);
	glVertex3f(0.45f, -0.45f, 0.0f);
	glEnd();
}

void drawRectangle(void) {
	glBegin(GL_QUADS);
	// Front face  (z = 1.0f)
	glColor3f(0.827f, 0.827f, 0.827f);     // Red
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.2f, 0.0f);
	glVertex3f(1.0f, 0.2f, 0.0f);
	glEnd();
}

void drawRectangle2(void) {
	glBegin(GL_QUADS);
	// Front face  (z = 1.0f)
	glColor4f(1.0f, 0.0f, 0.0f, 0.2f);     // Red
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.2f, 0.0f);
	glVertex3f(1.0f, 0.2f, 0.0f);
	glEnd();
}

void draw_cylinder(GLfloat radius,
	GLfloat height)
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glColor3f(skin[indexSkin][0], skin[indexSkin][1], skin[indexSkin][2]);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glColor3f(skin[indexSkin][0], skin[indexSkin][1], skin[indexSkin][2]);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();

}

void drawCube2(void) {
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face (y = 1.0f)
	glColor3f(skin[indexSkin][0], skin[indexSkin][1], skin[indexSkin][2]);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube 
}

void drawPyramid2(void) {
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	  // Bottom face (y = -1.0f)
	glColor3f(skin[indexSkin][0], skin[indexSkin][1], skin[indexSkin][2]);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	// Render a pyramid consists of 4 triangles
	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	   // Front
	glColor3f(skin[indexSkin][0], skin[indexSkin][1], skin[indexSkin][2]);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();   // Done drawing the pyramid
}

void drawBackground(void) {
	// Render a color-cube consisting of 6 quads with different colors
	glPushMatrix();
	glTranslatef(transIdle + 3, transIdle, -16.0f);
	glRotatef(angleCubeX + angleIdle, 0.0f, 1.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	glRotatef(angleCubeY + angleIdle, 1.0f, 0.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	drawCube2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-transIdle - 3, transIdle + 4, -16.0f);
	glRotatef(angleCubeX + angleIdle, 0.0f, 1.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	glRotatef(angleCubeY + angleIdle, 1.0f, 0.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	drawPyramid2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-transIdle - 4, -transIdle - 2, -16.0f);
	glRotatef(angleCubeX + angleIdle, 0.0f, 1.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	glRotatef(-angleCubeY + angleIdle, 1.0f, 0.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	drawCube2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(transIdle + 2, -transIdle - 4, -16.0f);
	glRotatef(angleCubeX + angleIdle, 0.0f, 1.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	glRotatef(angleCubeY + angleIdle, 1.0f, 0.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	drawPyramid2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(transIdle + 1, transIdle + 4, -16.0f);
	glRotatef(-angleCubeX + angleIdle, 0.0f, 1.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	glRotatef(angleCubeY + angleIdle, 1.0f, 0.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	drawCube2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-transIdle - 3, transIdle, -16.0f);
	glRotatef(angleCubeX + angleIdle, 0.0f, 1.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	glRotatef(-angleCubeY + angleIdle, 1.0f, 0.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	drawPyramid2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(transIdle, transIdle, -16.0f);
	glRotatef(angleCubeX + angleIdle, 0.0f, 1.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	glRotatef(angleCubeY + angleIdle, 1.0f, 0.0f, 0.0f);  // Rotate about (1,1,1)-axis [NEW]
	drawCube2();
	glPopMatrix();

	//resets background
	angleIdle += 0.05f;
	transIdle += 0.001f;
	if (transIdle > 4) {
		transIdle = 0;
	}
}

void indexSelector3(int a) {
	switch (a) {
	case 0:    
		a = 1; break;
	case 1:    
		selectPos = 0.0; break;
	case 2:    // Right: increase x speed
		selectPos = -1.0;break;
	case 3:     // Left: decrease x speed
		selectPos = -2.0;break;
		//case 4:    // F1: Toggle between full-screen and windowed mode
		//	 a = 3; break;
	}

}

void indexSelector2(int a) {
	switch (a) {
	case 0:    // F1: Toggle between full-screen and windowed mode
		a = 1; break;
	case 1:    // Right: increase x speed
		selectPos = -1.0;break;
	case 2:     // Left: decrease x speed
		selectPos = -2.0;break;
		//case 3:    // F1: Toggle between full-screen and windowed mode
		//	 a = 2; break;
	}

}

void drawMainMenu(void) {

	drawBackground();

	indexSelector3(selectIndex);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -7.0f);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	drawRectangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);
	drawRectangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -2.0f, 0.0f);
	drawRectangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, selectPos, 0.0f);
	drawRectangle2();
	glPopMatrix();
	glPopMatrix();


}

void drawDifficulty(void) {
	drawBackground();
	indexSelector2(selectedIndex);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -7.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	drawRectangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -1.5f, 0.0f);
	drawRectangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glTranslatef(0.0f, selectPos, 0.0f);
	drawRectangle2();
	glPopMatrix();
	glPopMatrix();
}





void nextRound() {
	resetVectors();
	generateRandomVector();
	generateShapeVector();

	generateShapeVector();
	for (int i = 0; i < roundNum; i++) {
		cout << colorV[i] << " " << endl;
	}
	cout << "SIZE: " << colorV.size() << endl;


	isSequenceComplete = false;
	frames = 65;
	colorVIndex = 0;
	shapeVIndex = 0;


}


void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void Timer(int value) {
	glutPostRedisplay();      // Post re-paint request to activate display()
	glutTimerFunc(refreshMillis, Timer, 0); // next Timer call milliseconds later
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity();                 // Reset the model-view matrix
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	// Render a color-cube consisting of 6 quads with different colors
	
	switch (screenIndex) {
	case 0:
		screenIndex = 1; break;
	case 1:
		currentPage = MAIN;
		drawMainMenu();
		break;
	case 2:
		switch (selectIndex) {
		case 1:
			currentPage = DIFF;
			drawDifficulty();
			break;
		case 2:
			drawBackground();
			glTranslatef(0.0f, -0.5f, -2.0f);
			drawRectangle();
			if (screenIndex == 3) {
				screenIndex = 2;
			}
			break;
		case 3:
			drawBackground();
			glTranslatef(0.0f, -0.5f, -2.0f);
			drawRectangle();
			break;
		}
		break;
	case (3):
		switch (selectedIndex) {
		case 1:
			
			currentDiff = EASY;
			gameDisplay();
			//glTranslatef(0.0f, 0.0f, -7.0f);
			//drawCube();
			break;
		case 2:
			
			currentDiff = HARD;
			gameDisplay();
			//glTranslatef(0.0f, 0.0f, -7.0f);
			//drawPyramid();
			break;
		}

		break;
	}


	switch (indexSkin) {
	case -1:
		indexSkin = 2; break;
	case 3:
		indexSkin = 0; break;
	}


	
	glutSwapBuffers();
}



void gameDisplay() {
	if (colorV.size() == 0) {
		newGame();
	}
	glLoadIdentity();                  // Reset the model-view matrix
	glTranslatef(0.0f, -0.5f, 0.0f);
	updateColor();
	updateShape();
	if (!isSequenceComplete) {
	frames++;
	}
	
	switch (currentDiff) {

	case 0:
		//cout << "going to easy display" << endl;
		currentPage = GAME;
		gameEasyDisplay();
		break;
	case 1:
		currentPage = GAME;
		gameHardDisplay();
		break;
	}
	
}

void gameEasyDisplay() {
	
	if (!isSequenceComplete && frames < 65) {
		dispSquare();
	}

	if (frames == 70) {
		
		if (colorVIndex + 1 <= colorV.size())
		{
			colorID = colorV[colorVIndex];
			cout << "COLOR INDEX: " << colorVIndex << "   COLOR IS: " << colorID << endl;
			colorVIndex++;
			
		}
		else
		{
			colorVIndex = 0;
			cout << "SEQUENCE COMPLETE" << endl;
			sequenceComplete();
		}
		frames = 0;
	}

}


void gameHardDisplay() {

	if (!isSequenceComplete && frames < 65) {
		switch (shapeID - 1) {
		case CUBE:
			dispCube();
			break;

		case PYRAMID:
			dispPyramid();
			break;

		case SPHERE:
			dispSphere();
			break;
		}
	}

	if (frames == 70) {
		
		if (colorVIndex + 1 <= colorV.size())
		{
			shapeID = shapeV[colorVIndex];
			colorID = colorV[colorVIndex];
			cout << "Index is: " << colorVIndex << endl;
			cout << "SHAPE IS: " << shapeID << "   COLOR IS: " << colorID << endl;
			colorVIndex++;

		}
		else
		{
			colorVIndex = 0;
			cout << "SEQUENCE COMPLETE" << endl;
			sequenceComplete();
		}
		frames = 0;
	}
}

void sequenceComplete() {
	isSequenceComplete = true;

}

void checkWin() {
	if (currentDiff == HARD) {
		
		for (int i = 0; i < roundNum; i = i + 2) {
			cout << "Color Guess: " << selectionV[i] << "   Shape Guess: " << selectionV[i + 1] << endl;
			cout << "Actual Color: " << colorV[i] << "   Shape: " << shapeV[i] << endl;
			if (colorV[i / 2] == selectionV[i] && shapeV[i / 2] == selectionV[i + 1]) {
				cout << i + 1 << " Guess is correct" << endl;
			}
			else {
				cout << "GUESS FAILED" << endl;
				roundNum = 1;
				currentPage--;
				resetGame();
				screenIndex = 1;
				return;
			}

		}
	}
	else {

		if(currentPage == GAME) for (int i = 0; i < roundNum; i = i + 2) {
			cout << "COLORV SIZE:  " << colorV.size() << endl;
			cout << "COLOR: " << colorV[i / 2] << endl;
			cout << "Selected Color" <<  selectionV[i] << endl;
			if (colorV[i / 2] == selectionV[i]) {
				cout << "Guess is correct" << endl;
			}
			else {
				cout << "GUESS FAILED" << endl;
				roundNum = 1;
				currentPage--;
				resetGame();
				screenIndex = 1;
				return;
			}

		}
		
	}
		cout << "!!!NEXT ROUND!!!" << endl;
		roundNum++;
		nextRound();
	

}


void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 13:	//Enter key
		if (currentPage != GAME) {
			screenIndex++;
		}
		else {
			cout << "ENTER GUESS: " << currentColor + 1 << " " << currentShape + 1 << endl;
			if (isSequenceComplete == true) {
				selectionV.push_back(currentColor + 1);
				selectionV.push_back(currentShape + 1);
				if (selectionV.size() == roundNum * 2) {
					cout << "checking win!" << endl;
					checkWin();
				}
			}
		}
		break;
	case 8:	//Backspace Key
		if (currentPage == GAME) {
			currentPage--;
		}
		resetGame();
		screenIndex--; break;
	case 27:     // ESC key
		exit(0);
		break;
	}
	

}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseDown = true;
	}
}

void mouseMove(int x, int y) {

	if ((lastMouseX - x) > 0) {
		lastMouseX = x;
		angleCubeX -= (1.0f);
		if ((lastMouseY - y) > 0) {
			lastMouseY = y;
			angleCubeY -= (1.0f);
		}
		else {
			lastMouseY = y;
			angleCubeY += (1.0f);
		}
	}
	else {
		lastMouseX = x;
		angleCubeX += (1.0f);
		if ((lastMouseY - y) > 0) {
			lastMouseY = y;
			angleCubeY -= (1.0f);
		}
		else {
			lastMouseY = y;
			angleCubeY += (1.0f);
		}
	}
}

void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode
		fullScreenMode = !fullScreenMode;         // Toggle state
		if (fullScreenMode) {                     // Full-screen mode
			windowPosX = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
			windowPosY = glutGet(GLUT_WINDOW_Y);
			windowWidth = glutGet(GLUT_WINDOW_WIDTH);
			windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();                      // Switch into full screen
		}
		else {                                         // Windowed mode
			glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
			glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
		}
		break;
	case GLUT_KEY_RIGHT:    // Right: increase x speed
		if (currentPage == GAME) {
			if (currentShape == 2) {
				currentShape = 0;
			}
			else {
				currentShape++;
			}
			glutPostRedisplay();
		}else indexSkin++; 
	break;

	case GLUT_KEY_LEFT:     // Left: decrease x speed
		if (currentPage == GAME) {
			if (currentShape == 0) {
				currentShape = 2;
			}
			else {
				currentShape--;
			}
			glutPostRedisplay();

			
		} else indexSkin--; 
	break;
	case GLUT_KEY_UP:   
		if (currentPage == GAME) {
			if (currentColor == 3) {
				currentColor = 0;
			}
			else {
				currentColor++;
			}
			glutPostRedisplay();
		}
		else {
			switch (screenIndex) {
			case 1:
				selectIndex--;
				switch (selectIndex) {
				case 0:
					selectIndex = 1; break;
				case 4:
					selectIndex = 3; break;
				}
				break;
			case 2:
				selectedIndex--;
				switch (selectedIndex) {
				case 0:
					selectedIndex = 1; break;
				case 3:
					selectedIndex = 2; break;
				}
				break;
			}
		}
		break;
	case GLUT_KEY_DOWN:     // Left: decrease x speed

		if (currentPage == GAME) {
			if (currentColor == 0) {
				currentColor = 3;
			}
			else {
				currentColor--;
			}
			glutPostRedisplay();
		}
		else {
			switch (screenIndex) {
			case 1:
				selectIndex++;
				switch (selectIndex) {
				case 0:
					selectIndex = 1; break;
				case 4:
					selectIndex = 3; break;
				}
				break;
			case 2:
				selectedIndex++;
				switch (selectedIndex) {
				case 0:
					selectedIndex = 1; break;
				case 3:
					selectedIndex = 2; break;
				}
				break;
			}
			break;
		}
	
	}
}
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}




int main(int argc, char** argv) {
	
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(640, 480);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutTimerFunc(0, Timer, 0);
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}
