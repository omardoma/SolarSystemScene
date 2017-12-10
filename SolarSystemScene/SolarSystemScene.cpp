#include "stdafx.h"
#include "TextureBuilder.h"
#include <glut.h>
#include <stdlib.h>
#include <math.h>

#pragma comment(lib, "legacy_stdio_definitions.lib")

#define DEG2RAD(a) (a * 0.0174532925)

GLuint texID1, texID2, texID3, texID4, texID5, texID6, texID7, texID8, texID9, texID10, texID11, texID12;
static float sun = 0.0;
static float planet = 0.0;
int sec = 10;
float angle = 0.0;
float leftRight = 0.0;
float X1 = -5.0, Z1 = 150.0;
float X2 = 0.0, Z2 = -1.0;
float Y = 35.0;
float n, u, s, j, m, e, v, me;
int forwardBackward = 0;
int moveUp = 0;
int width, height;
float fb = 0.8;

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
	}
};
Camera camera;

//initialize opengl
void initOpenGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
}

//draw space means stars with texture stars
void drawSpace()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID1);

	//top
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-500.0, 300.0, -500.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(500.0, 300.0, -500.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(500.0, 300.0, 500.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-500.0, 300.0, 500.0);
	glEnd();

	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-500.0, 300.0, -500.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(500.0, 300.0, -500.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(500.0, -300.0, -500.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-500.0, -300.0, -500.0);
	glEnd();

	//left
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-500.0, 300.0, -500.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-500.0, 300.0, 500.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-500.0, -300.0, 500.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-500.0, -300.0, -500.0);
	glEnd();

	//right
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(500.0, 300.0, -500.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(500.0, 300.0, 500.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(500.0, -300.0, 500.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(500.0, -300.0, -500.0);
	glEnd();

	//back
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-500.0, 300.0, 500.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(500.0, 300.0, 500.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(500.0, -300.0, 500.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-500.0, -300.0, 500.0);
	glEnd();

	//bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-500.0, -300.0, -500.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(500.0, -300.0, -500.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(500.0, -300.0, 500.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-500.0, -300.0, 500.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

//draw all planets using gluSphere() method & also setting textures
void drawPlanets()
{
	GLUquadric *quad;

	//draw mercury
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID2);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glRotated(me, 0, 1, 0);
	glTranslatef(-55.0, 0.0, 0.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.0, 60, 60);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw venus
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID3);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 50);
	glRotated(v, 0, 1, 0);
	glTranslatef(75.0, 0.0, 30.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.5, 40, 40);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw earth
	glPushMatrix();
	glEnable(GL_LIGHT1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID4);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glRotated(e, 0, 1, 0);
	glTranslatef(0.0, 0.0, 120.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 5.0, 70, 70);
	glDisable(GL_LIGHT1);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw earth's moon
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID5);


	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glRotated(e, 0, 1, 0);
	glTranslatef(5.0, 0.0, 133.0);
	GLfloat lightIntensity1[] = { 1.0f, 1.0f, 1.0, 1.0f };
	/*float moonX = 133 * sin(sun);
	float moonZ = 133 * cos(sun);*/
	GLfloat lightPosition1[] = { 0, 0.0f, 0, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity1);
	gluSphere(quad, 1.5, 40, 40);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw mars
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID6);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glRotated(m, 0, 1, 0);
	glTranslatef(-60.0, 0.5, 180.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.0, 40, 40);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw jupiter
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID7);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glRotated(j, 0, 1, 0);
	glTranslatef(-100.0, 0.0, -280.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 20.0, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw saturn
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID8);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glRotated(s, 0, 1, 0);
	glTranslatef(300.0, 2.0, -360.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 12.0, 100, 100);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluDisk(quad, 20.0, 28.0, 80, 80);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw uranus
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID9);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glRotated(u, 0, 1, 0);
	glTranslatef(50.0, 1.0, -360.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 8.0, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw neptune
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID10);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 50);
	glRotated(n, 0, 1, 0);
	glTranslatef(250.0, 1.0, 100.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 8.0, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw pluto
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID11);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glRotated(n, 0, 1, 0);
	glTranslatef(-250.0, 1.0, 100.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 8.0, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//draw sun and planets
void drawSunAndPlanets()
{
	GLUquadric *quad;
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID12);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	quad = gluNewQuadric();
	gluQuadricTexture(quad, 40);
	glTranslatef(0.0, 0.0, 0.0);
	//glRotatef((GLfloat)sun, 0.0, 1.0, 0.0); //rotating sun as well as all planets to Y axis
	gluSphere(quad, 30.0, 100, 100);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);

	drawPlanets();

	glPopMatrix();
}

//function that moves you to left & right direction
void moveLeftRight(float angle)
{
	X2 = sin(angle);
	Z2 = -cos(angle);
	glLoadIdentity();
	gluLookAt(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
}

//function that moves you to forward & backward direction
void moveForwardBackward(int loc)
{
	X1 = X1 + loc * (X2)*fb;
	Z1 = Z1 + loc * (Z2)*fb;
	glLoadIdentity();
	gluLookAt(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
}


//keyboard key function
void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(EXIT_SUCCESS);
	}
	/*else if (key == 'w')
	{
	Y += 2.0;
	glLoadIdentity();
	gluLookAt(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
	glutPostRedisplay();
	}
	else if (key == 's')
	{
	Y -= 2.0;
	glLoadIdentity();
	gluLookAt(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
	glutPostRedisplay();
	}*/
}

//keyboard key pressed function
void keyPressed(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		leftRight = -0.02;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		leftRight = 0.02;
	}
	else if (key == GLUT_KEY_UP)
	{
		forwardBackward = 2;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		forwardBackward = -2;
	}
	else if (key == GLUT_KEY_UP && key == GLUT_KEY_LEFT)
	{
		leftRight = 0.007;
	}
	else if (key == GLUT_KEY_UP && key == GLUT_KEY_RIGHT)
	{
		leftRight = 0.007;
	}
}

//keyboard key released function
void keyReleased(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (leftRight < 0.0f)
			leftRight = 0.0f;
		break;

	case GLUT_KEY_RIGHT:
		if (leftRight > 0.0f)
			leftRight = 0.0f;
		break;

	case GLUT_KEY_UP:
		if (forwardBackward > 0)
			forwardBackward = 0;

		break;

	case GLUT_KEY_DOWN:
		if (forwardBackward < 0)
			forwardBackward = 0;
		break;
	}
}

//timer function that rotate planets
void rotatePlanets(int value)
{
	glutPostRedisplay();
	glutTimerFunc(sec, rotatePlanets, 0);
}

void loadTextures()
{
	loadBMP(&texID1, "textures/stars.bmp", true);
	loadBMP(&texID2, "textures/mercury.bmp", true);
	loadBMP(&texID3, "textures/venus.bmp", true);
	loadBMP(&texID4, "textures/earth.bmp", true);
	loadBMP(&texID5, "textures/moon.bmp", true);
	loadBMP(&texID6, "textures/mars.bmp", true);
	loadBMP(&texID7, "textures/jupiter.bmp", true);
	loadBMP(&texID8, "textures/saturn.bmp", true);
	loadBMP(&texID9, "textures/uranus.bmp", true);
	loadBMP(&texID10, "textures/neptune.bmp", true);
	loadBMP(&texID11, "textures/pluto.bmp", true);
	loadBMP(&texID12, "textures/sun.bmp", true);
}

void setupCamera(int width, int height) {
	if (height == 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0 * (width / height), 1, 1000);
	//gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void setupLights() {
	GLfloat ambient[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

//display scene
void display()
{
	setupLights();
	if (forwardBackward)
	{
		moveForwardBackward(forwardBackward);
	}
	if (leftRight)
	{
		angle += leftRight;
		moveLeftRight(angle);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawSpace();
	drawSunAndPlanets();
	glutSwapBuffers();
	n += 0.04f;
	u += 0.05;
	s += 0.07;
	j += 0.096;
	m += 0.177;
	e += 0.22;
	v += 0.258;
	me += 0.352;
	planet += 0.5f;
}


void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3D Space");
	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyPressed);
	glutSpecialUpFunc(keyReleased);
	glutReshapeFunc(setupCamera);
	loadTextures();
	initOpenGL();
	glutTimerFunc(0, rotatePlanets, 0);
	glutMainLoop();
}
