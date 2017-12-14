#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <stdlib.h>
#include <math.h>

#pragma comment(lib, "legacy_stdio_definitions.lib")

#define DEG2RAD(a) (a * 0.0174532925)

GLuint texID1, texID2, texID3, texID4, texID5, texID6, texID7,
texID8, texID9, texID10, texID11, texID12, texID13, texID14,
texID15, texID16, texID17, texID18, texID19, texID20, texID21,
texID22, texID23, texID24, texID25, texID26;
Model_3DS model_rocket;
//static float sun = 0.0;
static float planet = 0.0;
float angle = 0.0;
int forwardBackward = 0;
float leftRight = 0.0;
float X1 = -5.0, Z1 = 150.0;
float X2 = 0.0, Z2 = -1.0;
float Y = 35.0;
float n, u, s, j, m, e, v, me; //for planet rotation speed around sun
float xRocket, zRocket;
int width, height;
int scene = 0;
bool firstPerson = false;
float thirdPersonAngle = 0;
float rotateThirdPerson = 0;

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

	Camera(float eyeX = 0.0f, float eyeY = 50.0, float eyeZ = 0.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 0.0f, float upZ = -1.0f) {
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
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera cameraFirst = Camera(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
Camera cameraThird = Camera(0, 200, 400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

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
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	GLint texID = scene == 0 ? texID1 : (scene == 1 ? texID13 : texID19);
	glBindTexture(GL_TEXTURE_2D, texID);
	if (scene != 0) {
		glDisable(GL_LIGHTING);
	}

	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 700, 100, 100);
	gluDeleteQuadric(qobj);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//draw all planets using gluSphere() method & also setting textures
void drawPlanets1()
{
	GLUquadric *quad;

	//draw black hole1
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID24);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(-680.0, 50.0, 0.0);
	glRotated(-90, 0, 1, 0);
	gluDisk(quad, 0, 150, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	//draw black hole2
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID24);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(680.0, 50.0, 0.0);
	glRotated(90, 0, 1, 0);
	gluDisk(quad, 0, 150, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

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
	/*glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID11);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glRotated(n, 0, 1, 0);
	glTranslatef(-250.0, 1.0, 100.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 8.0, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();*/
}


//draw scene 2 planets 
void drawPlanets2()
{
	GLUquadric *quad;

	//draw ice hole1
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID26);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(-680.0, 50.0, 0.0);
	glRotated(90, 0, 1, 0);

	glDisable(GL_LIGHTING);

	gluDisk(quad, 50, 150, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glColor3d(1, 1, 1);
	gluDisk(quad, 0, 150, 100, 100);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	//draw ice hole2
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID26);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(680.0, 50.0, 0.0);
	glRotated(-90, 0, 1, 0);

	glDisable(GL_LIGHTING);

	gluDisk(quad, 50, 150, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glColor3d(1, 1, 1);
	gluDisk(quad, 0, 150, 100, 100);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	//draw str
	glPushMatrix();

	glDisable(GL_LIGHTING);
	// glDisable(GL_LIGHT2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID14);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 50);
	glRotated(v, 0, 1, 0);
	glTranslatef(75.0, 0.0, 30.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.5, 40, 40);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw choc
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID15);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glRotated(e, 0, 1, 0);
	glTranslatef(0.0, 0.0, 120.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 5.0, 70, 70);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	//draw van
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID18);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glRotated(m, 0, 1, 0);
	glTranslatef(-60.0, 0.5, 180.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.0, 40, 40);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw mango
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID17);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glRotated(j, 0, 1, 0);
	glTranslatef(-100.0, 0.0, -280.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 20.0, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//draw scene 3 planets
void drawPlanets3()
{
	GLUquadric *quad;

	//draw net1
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID25);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(-690, 50.0, 0.0);
	glRotated(90, 0, 1, 0);
	gluDisk(quad, 0, 100, 100, 100);

	glDisable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING);

	glPopMatrix();

	//draw net2
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID25);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(690, 50.0, 0.0);
	glRotated(-90, 0, 1, 0);
	gluDisk(quad, 0, 100, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw tennis
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID23);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glRotated(me, 0, 1, 0);
	glTranslatef(-55.0, 0.0, 0.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.0, 60, 60);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw baseball
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID20);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glRotated(m, 0, 1, 0);
	glTranslatef(-60.0, 0.5, 180.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.0, 60, 60);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw basketball
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID21);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glRotated(j, 0, 1, 0);
	glTranslatef(-100.0, 0.0, -280.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 20.0, 100, 100);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw soccerball
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID22);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glRotated(s, 0, 1, 0);
	glTranslatef(300.0, 2.0, -360.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 12.0, 100, 100);
	glRotatef(90, 1.0, 0.0, 0.0);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//draw sun and planets
void drawSunAndPlanets()
{
	GLUquadric *quad;

	glPushMatrix();

	if (scene == 0)
	{
		drawPlanets1();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texID12);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT0);

		quad = gluNewQuadric();
		gluQuadricTexture(quad, 40);
		glTranslatef(0.0, 0.0, 0.0);
		gluSphere(quad, 30.0, 100, 100);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT0);
		glDisable(GL_TEXTURE_2D);
	}
	else if (scene == 1)
	{
		drawPlanets2();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texID16);
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT2);

		quad = gluNewQuadric();
		gluQuadricTexture(quad, 40);
		glTranslatef(0.0, 0.0, 0.0);
		gluSphere(quad, 30.0, 100, 100);

		glDisable(GL_TEXTURE_2D);
	}
	else if (scene == 2)
	{
		glDisable(GL_LIGHT2);

		drawPlanets3();

		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		quad = gluNewQuadric();
		gluQuadricTexture(quad, 40);
		glTranslatef(0.0, 0.0, 0.0);
		gluSphere(quad, 30.0, 100, 100);

		glDisable(GL_TEXTURE_2D);
	}

	glPopMatrix();
}

// draw rocket
void drawRocket()
{
	if (!firstPerson)
	{
		glPushMatrix();
		glColor3d(1, 1, 1);
		glTranslated(X1 + X2, Y, Z1 + Z2);
		glRotated(-angle*57.3, 0, 1, 0);
		glScaled(5, 5, 5);
		model_rocket.Draw();
		glPopMatrix();
	}
}

//keyboard key function
void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(EXIT_SUCCESS);
	}

	switch (key) {

	case 'a':
		rotateThirdPerson = -0.005;
		break;
	case 'd':
		rotateThirdPerson = 0.005;
		break;
	case 's':
		scene = (scene + 1) % 3;
		break;
	case 'c':
		firstPerson = !firstPerson;
		break;
	}
	glutPostRedisplay();
}

//keyboard up function
void keyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		rotateThirdPerson = 0;
		break;
	case 'd':
		rotateThirdPerson = 0;
		break;
	}
	glutPostRedisplay();
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
		forwardBackward = 1;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		forwardBackward = -1;
	}
	glutPostRedisplay();
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
	n += 0.04f;
	u += 0.05;
	s += 0.07;
	j += 0.096;
	m += 0.177;
	e += 0.22;
	v += 0.258;
	me += 0.352;
	planet += 0.5f;

	glutPostRedisplay();
	glutTimerFunc(10, rotatePlanets, 0);

}

void loadAssets()
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

	loadBMP(&texID13, "textures/ice.bmp", true);
	loadBMP(&texID14, "textures/str.bmp", true);
	loadBMP(&texID15, "textures/choc.bmp", true);
	loadBMP(&texID16, "textures/mix.bmp", true);
	loadBMP(&texID17, "textures/mango.bmp", true);
	loadBMP(&texID18, "textures/van.bmp", true);

	loadBMP(&texID19, "textures/grd.bmp", true);
	loadBMP(&texID20, "textures/base.bmp", true);
	loadBMP(&texID21, "textures/basket.bmp", true);
	loadBMP(&texID22, "textures/soc.bmp", true);
	loadBMP(&texID23, "textures/tennis.bmp", true);
	loadBMP(&texID24, "textures/blackhole.bmp", true);

	loadBMP(&texID25, "textures/net.bmp", true);
	loadBMP(&texID26, "textures/ice.bmp", true);

	model_rocket.Load("Models/rocket/tiefighter.3ds");
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1.0 * (1500 / 700), 1, 1400);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (firstPerson)
	{
		cameraFirst.look();
	}
	else
	{
		cameraThird.look();
	}
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

	GLfloat lightIntensity1[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat lightPosition1[] = { 0, 0.0f, 0, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity1);

	GLfloat lightIntensity2[] = { 1.0f, 0.5f, 0.8, 1.0f };
	GLfloat lightPosition2[] = { 0, 0.0f, 0, 1.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightIntensity2);
}

//display scene
void display()
{
	setupCamera();
	setupLights();
	if (forwardBackward != 0)
	{
		int tempX1 = X1 + forwardBackward * (X2);
		int tempZ1 = Z1 + forwardBackward * (Z2);

		if (tempX1 >= 680)
		{
			scene = ((scene + 1) % 3);

			X1 = -5.0, Z1 = 150.0, X2 = 0.0, Z2 = -1.0;
			angle = 0;
			cameraFirst = Camera(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
		}
		if (tempX1 <= -680)
		{
			scene = ((scene + 2) % 3);
			X1 = -5.0, Z1 = 150.0, X2 = 0.0, Z2 = -1.0;
			angle = 0;
			cameraFirst = Camera(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
		}
		if (tempX1*tempX1 + tempZ1*tempZ1 < 695 * 695)
		{
			X1 = X1 + forwardBackward * (X2);
			Z1 = Z1 + forwardBackward * (Z2);
			cameraFirst.eye.x = X1;
			cameraFirst.eye.z = Z1;
			cameraFirst.center.x = X1 + X2;
			cameraFirst.center.z = Z1 + Z2;
		}
	}
	if (leftRight != 0)
	{
		angle += leftRight;
		X2 = sin(angle);
		Z2 = -cos(angle);
		cameraFirst.center.x = X1 + X2;
		cameraFirst.center.z = Z1 + Z2;
	}
	if (rotateThirdPerson != 0)
	{
		thirdPersonAngle += rotateThirdPerson;
		if (thirdPersonAngle >= 360 || thirdPersonAngle <= -360)
		{
			thirdPersonAngle = 0;
		}
		cameraThird.eye.z = 400 * cos(thirdPersonAngle);
		cameraThird.eye.x = 400 * sin(thirdPersonAngle);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawSpace();
	drawSunAndPlanets();
	drawRocket();
	glutSwapBuffers();

}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1500, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3D Space");
	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(keyPressed);
	glutSpecialUpFunc(keyReleased);
	loadAssets();
	initOpenGL();
	glutTimerFunc(0, rotatePlanets, 0);
	glutMainLoop();
}
