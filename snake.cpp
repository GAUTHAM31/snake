#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//gl lib
#include <deque> //for data structure
#include <GL/glut.h>

//direction
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4
//data structure to represnt snake
 std::deque< std::deque<float> > part_coords;
 float map_half_length = 30.0f;
 int direction = DOWN;
 bool moved = false;
 bool food_available = false;
 int food_coords[2];
 int move_speed = 100;
 int growth_stage = 0;//
int growth = 2;//
//display function
void food(){//to create food 
    if(!food_available){
        while(true){
            bool collides = false;

            // Produce a temporary random coordinate
            int temp_food_coords[2] = { food_coords[0] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length,
                                        food_coords[1] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length };

            // Does it collide with the snake?
            for(unsigned int a = 0; a < part_coords.size(); a++){
                if(temp_food_coords[0] == part_coords[a][0] &&
                   temp_food_coords[1] == part_coords[a][1]){
                    collides = true;
                }
            }

            // If it doesn't collide with the snake, then make it the real food coordinates
            if(collides == false){
                food_coords[0] = temp_food_coords[0];
                food_coords[1] = temp_food_coords[1];

                food_available = true;

                break;
            }
        }
    }

    glLoadIdentity();
    glTranslatef(food_coords[0], food_coords[1], -40.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2d( 1.0f,  1.0f);
        glVertex2d( 1.0f, -1.0f);
        glVertex2d(-1.0f, -1.0f);
        glVertex2d(-1.0f,  1.0f);
    glEnd();
}

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
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_POLYGON);
            glVertex2d( 1.0f,  1.0f);
            glVertex2d( 1.0f, -1.0f);
            glVertex2d(-1.0f, -1.0f);
            glVertex2d(-1.0f,  1.0f);
        glEnd();
    }


    food();
    glutSwapBuffers();
}
void moveSnake(int new_direction)
{
direction = new_direction;

    int last_part = part_coords.size() - 1;
    std::deque<float> new_head = part_coords[last_part];//to find head (-_-)

    if(direction == UP){
        // Did we hit ourself?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(part_coords[0][0]        == part_coords[a][0] &&
               part_coords[0][1] + 2.0f == part_coords[a][1]){
                exit(0);
            }
        }

        // Did we hit a wall?
        if(part_coords[0][1] == map_half_length){
            exit(0);
        }

        // Did we get food?
        if(part_coords[0][0]        == food_coords[0] &&
           part_coords[0][1] + 2.0f == food_coords[1]){
            growth_stage++;
            food_available = false;
        }

        new_head[1] = part_coords[0][1] + 2.0f;//moving
    } else if(direction == DOWN){
        // Did we hit ourself?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(part_coords[0][0]        == part_coords[a][0] &&
               part_coords[0][1] - 2.0f == part_coords[a][1]){
                exit(0);
            }
        }

        // Did we hit a wall?
        if(part_coords[0][1] == -map_half_length){
            exit(0);
        }

        // Did we get food?
        if(part_coords[0][0]        == food_coords[0] &&
           part_coords[0][1] - 2.0f == food_coords[1]){
            growth_stage++;
            food_available = false;
        }

        new_head[1] = part_coords[0][1] - 2.0f;
    } else {
        new_head[1] = part_coords[0][1];
    }

    if(direction == LEFT){
        // Did we hit ourself?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(part_coords[0][0] - 2.0f == part_coords[a][0] &&
               part_coords[0][1]        == part_coords[a][1]){
                exit(0);
            }
        }

        // Did we hit a wall?
        if(part_coords[0][0] == -map_half_length){
            exit(0);
        }

        // Did we get food?
        if(part_coords[0][0] - 2.0f == food_coords[0] &&
           part_coords[0][1]        == food_coords[1]){
            growth_stage++;
            food_available = false;
        }

        new_head[0] = part_coords[0][0] - 2.0f;
    } else if(direction == RIGHT){
        // Did we hit ourself?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(part_coords[0][0] + 2.0f == part_coords[a][0] &&
               part_coords[0][1]        == part_coords[a][1]){
                exit(0);
            }
        }

        // Did we hit a wall?
        if(part_coords[0][0] == map_half_length){
            exit(0);
        }

        // Did we get food?
        if(part_coords[0][0] + 2.0f == food_coords[0] &&
           part_coords[0][1]        == food_coords[1]){
            growth_stage++;
            food_available = false;
        }

        new_head[0] = part_coords[0][0] + 2.0f;
    } else {
        new_head[0] = part_coords[0][0];
    }

    part_coords.push_front(new_head);//adds new head

   if(!growth_stage){
        part_coords.pop_back();//pop head if it is no growth
    } else if(growth_stage == growth){
        growth_stage = 0;
    } else {
        growth_stage++;
    }

    glutPostRedisplay();
}
//keyboard function
void keyboard(int key, int x, int y){


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
void moveSnakeAuto(int value){
    if(!moved){

        if(direction == UP){
            moveSnake(UP);
        } else if(direction == DOWN){
            moveSnake(DOWN);
        } else if(direction == LEFT){
            moveSnake(LEFT);
        } else if(direction == RIGHT){
            moveSnake(RIGHT);
        }
    } else {
        moved = false;

    }
     glutTimerFunc(move_speed, moveSnakeAuto, 0);
}

//main function
int main(int argc, char** argv)
{
	/* code */
	int windowWidth=600;
	int windowHeight=600;
	//to make snake at first 
	int initSize = 3;

    // Specify the coordinates to each part of the snake
    for(int a = 1; a <= initSize; a++){
        std::deque<float> row;

        row.push_back(0.0f);//x
        row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));//y

        part_coords.push_front(row);
    }

	///glut functions
	glutInit(&argc, argv);// take -lgl ,lglu ,lglut from commend
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); // use single render frame,init rcb buffer
	glutInitWindowSize(600, 600);//height,width
	glutInitWindowPosition(0,0 );
	glutCreateWindow("Snake");  //to create window with title
    glutDisplayFunc(display);  //calls function to draw
    glutSpecialFunc(keyboard);
    glutTimerFunc(move_speed, moveSnakeAuto, 0);

    glViewport( 0, 0, windowWidth, windowHeight );
    glMatrixMode( GL_PROJECTION );//GL_PROJECTION - for camera positioning 
    gluPerspective(75.0f, 1, 0.0f, 35.0f);;// angle,ascpt ratio,camera from near cliping,camera from far cliping plan

    glutMainLoop();  //repeat main loop infinity
	return 0;
}