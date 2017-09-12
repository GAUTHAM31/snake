#include <stdio.h>
#include <stdlib.h>
//gl lib
#include <GL/glut.h>

//main function
int main(int argc, char** argv)
{
	/* code */
	glutInit(&argc, argv);// take -lgl ,lglu ,lglut from commend
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // use single render frame,init rcb buffer
	glutInitWindowSize(600, 600);//height,width
	glutInitWindowPosition(0,0 );
	glutCreateWindow("Snake");  //to create window with title
   // glutDisplayFunc(display);  
    glutMainLoop();  //repeat main loop infinity
	return 0;
}