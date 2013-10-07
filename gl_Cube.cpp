/**
* Rendering a three dimensional cube using openGL 
* @author Luis Palacios
*/

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

//static variables 
const float cubeSize = 7.0f;
float deltaAngle = 0;

/**
 * Give user a way to exit window
 */
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: 
			exit(0);
	}
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	
}

/**
 * Handles a possible change in window dimensions
 */
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

/**
 * Draws a cube with a given size and sets its rotation 
 */
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -20.0f);
	
    	glRotatef(-deltaAngle, 1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
	
	//TopQuad
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(0.0, 1.0f, 0.0f);
    	glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    	glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
    	glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    	glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	
	//BottomQuad
	glColor3f(1.0f, 0.0f, 1.0f);
	glNormal3f(0.0, -1.0f, 0.0f);
    	glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    	glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    	glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    	glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
	
	//LeftQuad
	glNormal3f(-1.0, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
    	glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    	glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
	glColor3f(0.0f, 0.0f, 1.0f);
    	glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
    	glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	
	//RightQuad
	glNormal3f(1.0, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
    	glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    	glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	glColor3f(0.0f, 1.0f, 0.0f);
    	glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    	glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
	
	//FrontQuad
	glNormal3f(0.0, 0.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
    	glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    	glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
	glColor3f(1.0f, 1.0f,0.0f);
    	glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    	glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
	
	//BackQuad
	glNormal3f(0.0, 0.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
    	glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    	glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	glColor3f(1.0f, 1.0f, 0.0f);
    	glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    	glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
	
	glEnd();
	glutSwapBuffers();
}

/**
 * Function that updates the rotation degree and sets itself to be called again
 */
void update(int value) {
    deltaAngle += 1.0f;
    if (deltaAngle > 360) {
        deltaAngle -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

/**
 * Initializes the window to be used as well as keyboard and timer functions
 */
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
    	glutCreateWindow("Demo");
	glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();
	return 0;
}

