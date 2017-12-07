#include "stdafx.h"
#include "TextureBuilder.h"
#include <glut.h>
#include <stdlib.h>
#include <math.h>

#pragma comment(lib, "legacy_stdio_definitions.lib")

GLuint texID1, texID2, texID3, texID4, texID5, texID6, texID7, texID8, texID9, texID10, texID11, texID12;
static float sun = 0.0;
int sec = 10;
static float planet = 0.0;

float _Angle = 0.0;
float _moveLeftRight = 0.0;
float X = -5.0, Z = 150.0;
float X_2 = 0.0, Z_2 = -1.0;
float Y = 3.0;
int _moveForeBack = 0;
int moveUp = 0;
int _width, _height;
float fb = 0.8;

//delete data from created texture
void FreeCreatedTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}


//initialize opengl
void Init_OpenGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}


//draw space means stars with texture stars
void Draw_Space()
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

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

}


//draw all planets using gluSphere() method & also setting textures
void Draw_Planets()
{
	GLUquadric *quad;

	//////////////////////////////////////////////////////////////////////////
	//draw mercury

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID2);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glTranslatef(-55.0, 0.0, 0.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.0, 60, 60);
	glDisable(GL_TEXTURE_2D);

	//FreeCreatedTexture(texID);

	glPopMatrix();


	//////////////////////////////////////////////////////////////////
	//draw venus
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID3);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 50);
	glTranslatef(75.0, 0.0, 30.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.5, 40, 40);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	/////////////////////////////////////////////////////////
	//draw earth
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID4);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glTranslatef(0.0, 0.0, 120.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 5.0, 70, 70);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//draw earth's moon
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID5);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glTranslatef(5.0, 0.0, 133.0);
	gluSphere(quad, 1.5, 40, 40);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	//////////////////////////////////////////////////////////////
	//draw mars
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID6);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glTranslatef(-60.0, 0.5, 180.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 4.0, 40, 40);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	//////////////////////////////////////////////////////////////////
	//draw jupiter
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID7);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 10);
	glTranslatef(-100.0, 0.0, -280.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 20.0, 100, 100);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	///////////////////////////////////////////////////////////////
	//draw saturn
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID8);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glTranslatef(300.0, 2.0, -360.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 12.0, 100, 100);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluDisk(quad, 20.0, 28.0, 80, 80);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	/////////////////////////////////////////////////////////////
	//draw uranus
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID9);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	glTranslatef(50.0, 1.0, -360.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 8.0, 100, 100);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	/////////////////////////////////////////////////////////
	//draw neptune
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID10);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 50);
	glTranslatef(250.0, 1.0, 100.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 8.0, 100, 100);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	//////////////////////////////////////////////////
	//draw pluto
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID11);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 5);
	glTranslatef(-250.0, 1.0, 100.0);
	glRotatef((GLfloat)planet, 0.0, 1.0, 0.0);
	gluSphere(quad, 8.0, 100, 100);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

//function that moves you to left & right direction
void Moving_Left_Right_Direction(float angle)
{
	X_2 = sin(angle);
	Z_2 = -cos(angle);
	glLoadIdentity();
	gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
}

//function that moves you to forward & backward direction
void Moving_Foreword_Backword_Direction(int loc)
{
	X = X + loc*(X_2)*fb;
	Z = Z + loc*(Z_2)*fb;
	glLoadIdentity();
	gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
}


//display scene
void Display_Scene()
{

	if (_moveForeBack)
	{
		Moving_Foreword_Backword_Direction(_moveForeBack);
	}

	if (_moveLeftRight)
	{
		_Angle += _moveLeftRight;
		Moving_Left_Right_Direction(_Angle);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Draw_Space();

	GLUquadric *quad;

	glPushMatrix();

	///////////////////////////////////////////////////////////
	//draw sun
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID12);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 40);

	glTranslatef(0.0, 0.0, 0.0);

	//rotating sun as well as all planets to Y axis
	glRotatef((GLfloat)sun, 0.0, 1.0, 0.0);
	gluSphere(quad, 30.0, 100, 100);

	//FreeCreatedTexture(texID);
	glDisable(GL_TEXTURE_2D);

	Draw_Planets();

	glPopMatrix();

	glutSwapBuffers();

	sun += 0.04f;
	planet += 0.5f;
}


//keyboard key function
void Keyboard_function(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(EXIT_SUCCESS);
	}
	else if (key == 'w')
	{
		Y += 2.0;
		glLoadIdentity();
		gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
		glutPostRedisplay();
	}
	else if (key == 's')
	{
		Y -= 2.0;
		glLoadIdentity();
		gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
		glutPostRedisplay();
	}
}

//keyboard key pressed function
void Key_Pressed(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		_moveLeftRight = -0.09;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		_moveLeftRight = 0.09;
	}
	else if (key == GLUT_KEY_UP)
	{
		_moveForeBack = 8;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		_moveForeBack = -8;
	}
	else if (key == GLUT_KEY_UP && key == GLUT_KEY_LEFT)
	{
		_moveLeftRight = 0.07;
	}
	else if (key == GLUT_KEY_UP && key == GLUT_KEY_RIGHT)
	{
		_moveLeftRight = 0.07;
	}

}


//keyboard key released function
void Key_Released(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (_moveLeftRight < 0.0f)
			_moveLeftRight = 0.0f;
		break;

	case GLUT_KEY_RIGHT:
		if (_moveLeftRight > 0.0f)
			_moveLeftRight = 0.0f;
		break;

	case GLUT_KEY_UP:
		if (_moveForeBack > 0)
			_moveForeBack = 0;

		break;

	case GLUT_KEY_DOWN:
		if (_moveForeBack < 0)
			_moveForeBack = 0;
		break;
	}
}


//timer function that rotate planets
void RotatePlanets(int value)
{
	glutPostRedisplay();
	glutTimerFunc(sec, RotatePlanets, 0);
}

void loadAssets() {
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

//reshape function
void Reshape_Function(int width, int height)
{
	if (height == 0)
		height = 1;

	_width = width;
	_height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, _width, _height);
	gluPerspective(45, 1.0*(width / height), 1.0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);

}


//main method
void main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3D Solar System");
	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(Display_Scene);
	glutKeyboardFunc(Keyboard_function);
	glutSpecialFunc(Key_Pressed);
	glutSpecialUpFunc(Key_Released);
	glutReshapeFunc(Reshape_Function);
	loadAssets();
	Init_OpenGL();
	glutTimerFunc(0, RotatePlanets, 0);
	/* you can use glutFullScreen()
	function here to go to full screen mode
	*/
	glutMainLoop();
}


