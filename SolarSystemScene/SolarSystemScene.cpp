#include "stdafx.h"
#include "TextureBuilder.h"
#include <glut.h>
#include <stdlib.h>
#include <math.h>
#define DEG2RAD(a) (a * 0.0174532925)
#pragma comment(lib, "legacy_stdio_definitions.lib")

GLuint texID1, texID2, texID3, texID4, texID5, texID6, texID7, texID8, texID9, texID10, texID11, texID12 ,texID13, texID14, texID15, texID16, texID17, texID18;
GLuint texID19, texID20, texID21, texID22, texID23;
GLuint texID24 , texID25, texID26;
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
int scene = 1;

//initialize opengl
void initOpenGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

//draw space means stars with texture stars
void drawSpace()
{
	glEnable(GL_TEXTURE_2D);
	if(scene == 1)
	glBindTexture(GL_TEXTURE_2D, texID1);
	else if (scene == 2) {
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, texID13);
	}
	else if (scene == 3)
	{
		glBindTexture(GL_TEXTURE_2D, texID19);
	}
	glPushMatrix();

	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);

	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 700, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
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
	glTranslatef(-620.0, 50.0, 0.0);
	glRotated(-90, 0, 1, 0);

	//glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);

	//gluSphere(quad, 150.0, 100, 100);
	gluDisk(quad, 0, 150, 100, 100);


	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw black hole2
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID24);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(700.0, 50.0, 0.0);
	glRotated(90, 0, 1, 0);

	//glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);

	//gluSphere(quad, 150.0, 100, 100);
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
	//glPushMatrix();

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texID11);

	//quad = gluNewQuadric();
	//gluQuadricTexture(quad, 5);
	//glRotated(n, 0, 1, 0);
	//glTranslatef(-250.0, 1.0, 100.0);
	//glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	//gluSphere(quad, 8.0, 100, 100);

	//glDisable(GL_TEXTURE_2D);

	//glPopMatrix();
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
	glTranslatef(-620.0, 50.0, 0.0);
	glRotated(90, 0, 1, 0);

	//glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);

	//gluSphere(quad, 150.0, 100, 100);
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
	glTranslatef(700.0, 50.0, 0.0);
	glRotated(-90, 0, 1, 0);

	//glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);

	//gluSphere(quad, 150.0, 100, 100);
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
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID14);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 50);
	glRotated(v, 0, 1, 0);
	glTranslatef(75.0, 0.0, 30.0);
	GLfloat lightIntensity2[] = { 1.0f, 0.5f, 0.8, 1.0f };
	GLfloat lightPosition2[] = { 0, 0.0f, 0, 1.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightIntensity2);
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

	////draw saturn
	//glPushMatrix();

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texID8);

	//quad = gluNewQuadric();
	//gluQuadricTexture(quad, 1);
	//glRotated(s, 0, 1, 0);
	//glTranslatef(300.0, 2.0, -360.0);
	//glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	//gluSphere(quad, 12.0, 100, 100);
	//glRotatef(90, 1.0, 0.0, 0.0);
	//gluDisk(quad, 20.0, 28.0, 80, 80);

	//glDisable(GL_TEXTURE_2D);

	//glPopMatrix();

	
}

//draw scene 3 planets
void drawPlanets3()
{
	GLUquadric *quad;

	//draw net1
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID25);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(-635.0, 50.0, 0.0);
	glRotated(90, 0, 1, 0);

	//glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);

	//gluSphere(quad, 150.0, 100, 100);
	gluDisk(quad, 0, 100, 100, 100);


	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw net2
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID25);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(742.0, 50.0, 0.0);
	glRotated(-90, 0, 1, 0);

	//glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);

	//gluSphere(quad, 150.0, 100, 100);
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


	//draw soccer ball
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
	//gluDisk(quad, 20.0, 28.0, 80, 80);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//draw sun and planets
void drawSunAndPlanets()
{
	
	GLUquadric *quad;
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	if (scene == 1)
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
		//glRotatef((GLfloat)sun, 0.0, 1.0, 0.0); //rotating sun as well as all planets to Y axis
		gluSphere(quad, 30.0, 100, 100);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glDisable(GL_TEXTURE_2D);
	}
	else if (scene == 2)
	{
		drawPlanets2();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texID16);
		//glDisable(GL_LIGHTING);
		//glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT2);
		quad = gluNewQuadric();
		gluQuadricTexture(quad, 40);
		glTranslatef(0.0, 0.0, 0.0);
		//glRotatef((GLfloat)sun, 0.0, 1.0, 0.0); //rotating sun as well as all planets to Y axis
		gluSphere(quad, 30.0, 100, 100);
		
		glDisable(GL_TEXTURE_2D);
	}
	else if (scene == 3)
	{
		drawPlanets3();
		glEnable(GL_TEXTURE_2D);
		/*glBindTexture(GL_TEXTURE_2D, texID16);*/
		//glDisable(GL_LIGHTING);
		//glDisable(GL_LIGHT2);
		glDisable(GL_LIGHTING);
		//glEnable(GL_LIGHT2);
		quad = gluNewQuadric();
		gluQuadricTexture(quad, 40);
		glTranslatef(0.0, 0.0, 0.0);
		//glRotatef((GLfloat)sun, 0.0, 1.0, 0.0); //rotating sun as well as all planets to Y axis
		gluSphere(quad, 30.0, 100, 100);

		glDisable(GL_TEXTURE_2D);
	}


	

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
	if (key == 's') {
		if (scene == 1)
			scene = 2;
		else if (scene == 2)
			scene = 1;
		glLoadIdentity();
		 X1 = -5.0, Z1 = 150.0;
		 X2 = 0.0, Z2 = -1.0;
		 Y = 35.0;
		 angle = 0.0;
		
		gluLookAt(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);

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
	

}

//reshape function
void reshape(int width, int height)
{
	if (height == 0)
		height = 1;

	width = width;
	height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(75, 1.0 * (width / height), 1, 1400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(X1, Y, Z1, X1 + X2, Y, Z1 + Z2, 0.0f, 1.0f, 0.0f);
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
	//setupCamera();
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
	glutReshapeFunc(reshape);
	loadTextures();
	initOpenGL();
	glutTimerFunc(0, rotatePlanets, 0);
	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
	glutMainLoop();
}
