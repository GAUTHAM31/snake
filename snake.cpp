#include <stdio.h>
#include <stdlib.h>
//gl lib
#include <GL/glut.h>

//display function
void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();//load identity matrix
   glTranslatef(0,5, -20);//glTranslatef(x, y, z) moves along the X, Y and Z axis, in that order.

   glBegin(GL_POLYGON); 
   glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2d( 1.0f,  1.0f);
    glVertex2d( 1.0f, -1.0f);
    glVertex2d(-1.0f, -1.0f);
    glVertex2d(-1.0f,  1.0f);
   glEnd();
   glutSwapBuffers();

}

//main function
int main(int argc, char** argv)
{
	/* code */
	int windowWidth=600;
	int windowHeight=600;
	glutInit(&argc, argv);// take -lgl ,lglu ,lglut from commend
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // use single render frame,init rcb buffer
	glutInitWindowSize(600, 600);//height,width
	glutInitWindowPosition(0,0 );
	glutCreateWindow("Snake");  //to create window with title
    glutDisplayFunc(display);  //calls function to draw

    glViewport( 0, 0, windowWidth, windowHeight );
    glMatrixMode( GL_PROJECTION );//GL_PROJECTION - for camera positioning 
    glEnable( GL_DEPTH_TEST );
    gluPerspective(75.0f, 1, 0.0f, 35.0f);;// angle,ascpt ratio,camera from near cliping,camera from far cliping plan
    glMatrixMode( GL_MODELVIEW );//change mode to GL_MODELVIEW - for various transformations

    glutMainLoop();  //repeat main loop infinity
	return 0;
}