#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//gl lib
#include <deque>
#include <GL/glut.h>
//data structure to represnt snake
 std::deque< std::deque<float> > part_coords;
 float map_half_length = 30.0f;
//display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // The vertex order is clockwise
    // The side order is front, back, left, right, top, bottom (if applicable)

    // Loop over snake size and draw each part at it's respective coordinates
    for(unsigned int a = 0; a < part_coords.size(); a++){
        glLoadIdentity();
        glTranslatef(part_coords[a][0], part_coords[a][1], -40.0f);
        glColor3f(0.0f, 1.0f, 0.0f);

        glBegin(GL_POLYGON);
            glVertex2d( 1.0f,  1.0f);
            glVertex2d( 1.0f, -1.0f);
            glVertex2d(-1.0f, -1.0f);
            glVertex2d(-1.0f,  1.0f);
        glEnd();
    }



    glutSwapBuffers();
}
//keyboard function
void keyboard(int key, int x, int y){
    UNUSED(x);
    UNUSED(y);

    switch(key){
        case GLUT_KEY_UP:{
            if(direction == LEFT || direction == RIGHT){
                moved = true;

                moveSnake(UP);
            }

            break;
        }

        case GLUT_KEY_DOWN:{
            if(direction == LEFT || direction == RIGHT){
                moved = true;

                moveSnake(DOWN);
            }

            break;
        }

        case GLUT_KEY_LEFT:{
            if(direction == UP || direction == DOWN){
                moved = true;

                moveSnake(LEFT);
            }

            break;
        }

        case GLUT_KEY_RIGHT:{
            if(direction == UP || direction == DOWN){
                moved = true;

                moveSnake(RIGHT);
            }

            break;
        }
    }

    glutPostRedisplay();
}


//main function
int main(int argc, char** argv)
{
	/* code */
	int windowWidth=600;
	int windowHeight=600;
	int initSize = 3;

    // Specify the coordinates to each part of the snake
    for(int a = 1; a <= initSize; a++){
        std::deque<float> row;

        row.push_back(0.0f);
        row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));

        part_coords.push_front(row);
    }
    for(int i=0;i<3;i++)
    std::cout<<"-"<<part_coords[i][0]<<" "<<part_coords[i][1];

	///glut functions
	glutInit(&argc, argv);// take -lgl ,lglu ,lglut from commend
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); // use single render frame,init rcb buffer
	glutInitWindowSize(600, 600);//height,width
	glutInitWindowPosition(0,0 );
	glutCreateWindow("Snake");  //to create window with title
    glutDisplayFunc(display);  //calls function to draw
    glutSpecialFunc(keyboard);

    glViewport( 0, 0, windowWidth, windowHeight );
    glMatrixMode( GL_PROJECTION );//GL_PROJECTION - for camera positioning 
    gluPerspective(75.0f, 1, 0.0f, 35.0f);;// angle,ascpt ratio,camera from near cliping,camera from far cliping plan

    glutMainLoop();  //repeat main loop infinity
	return 0;
}