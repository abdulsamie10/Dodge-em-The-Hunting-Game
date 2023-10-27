//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

float x = 250; 
float y = 40;
float user_x = 500; 
float user_y = 40; 
float xmove = 0, ymove = 0;
float square_x = 60;
float square_y = 65;
int gift[64] = {0};
int x1 = 0;
int yy1 = 0;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	DrawString( 50, 850, "Score=0", colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] );
	//Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(780,265,7,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 50 , colors[MISTY_ROSE] );
	
	
	
	int i = 0;
	for (square_x = 60; square_x <= 780.0; square_x += 100) {
		for (square_y = 65; square_y <= 770; square_y +=100) {
			if (gift[i] == 0) {
				if ((square_x+15)>=user_x && (square_x-50)<=user_x) {
					if ((square_y+25)>=user_y && (square_y-25)<=user_y) {
						gift[i] = 1;
					}
				}
			}
		
			if (gift[i] == 0) {
				DrawSquare(square_x, square_y, 10, colors[GREEN]);
			}
				i++;	
				}
		}
					
			/*	rawCircle(square_x, square_y, 5, colors[MISTY_ROSE]);
			if	 ((square_x > 160 && square_y > 270) && (square_x < 540 && square_y < 530)) {
					square_x = 470;	
					}
			if 	(square_x <= 260 || square_x >= 580) {
			 	square_x += 100;
			 
			else { 
				square_x += 110;
			}*/
	
	


	// Drawing opponent car 
	float width = 20; 
	float height = 10;
	float* color = colors[BLACK]; 
	float radius = 5.0;
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect
	
	// Drawing car
	float* color_me = colors[GREEN]; 
	DrawRoundRect(user_x + xmove,user_y,width,height,color_me,radius); // bottom left tyre
	DrawRoundRect(user_x+width*3 + xmove,user_y,width,height,color_me,radius); // bottom right tyre
	DrawRoundRect(user_x+width*3 + xmove,user_y+height*4,width,height,color_me,radius); // top right tyre
	DrawRoundRect(user_x + xmove,user_y+height*4,width,height,color_me,radius); // top left tyre
	DrawRoundRect(user_x + xmove, user_y+height*2, width, height, color_me, radius/2); // body left rect
	DrawRoundRect(user_x+width + xmove, user_y+height, width*2, height*3, color_me, radius/2); // body center rect
	DrawRoundRect(user_x+width*3 + xmove, user_y+height*2, width, height, color_me, radius/2); // body right rect
	//cout << user_x << "  " << user_y << endl; 
	

	// Drawing Arena
	int gap_turn = 100;
	int sx = 20;
	int sy = 10;
	int full_width = 800;
	int sheight = 10;
	float *scolor = colors[VIOLET];
	
	for (;sx <= 320;) {	
		int swidth = full_width/2 - gap_turn/2; // half width
		DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
		DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
		DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
		DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
		DrawRectangle(sx + swidth + gap_turn, sy+(full_width+10), swidth, sheight, scolor); // top left
		DrawRectangle(sx, sy+(full_width+10), swidth, sheight, scolor); // top right
		DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
		DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down
		sx += 100;
		sy += 100;
		full_width -= 200;
	}
	DrawSquare( 393 , 395 ,50,colors[BLACK]);
	
	/*Drawing last box
	int s4x = 320;
	int s4y = 310;
	int s4width = 200/2; // half width
	DrawRectangle(s4x s4y, s4width-50, sheight, scolor); // bottom left
	DrawRectangle(s4x + s4width+ s4y, s4width, sheight, scolor); // bottom right
	DrawRectangle(s4x+50+s4width*2, s4y+sheight, sheight*2, s4width, scolor); // right down                                                   
	DrawRectangle(s4x+s4width*2, s4y+sheight+s4width, sheight*2, s4width, scolor); // right up
	DrawRectangle(s4x + s4width, s4y+210, s4width-50, sheight, scolor); // top left
	DrawRectangle(s4x, s4y+210, s4width-50, sheight, scolor); // top right
	DrawRectangle(s4x-sheight*2, s4y+sheight+s4width-50, sheight*2, s4width, scolor); // left up
	DrawRectangle(s4x-sheight*2, s4y+sheight, sheight*2, s4width-50, scolor); // left down */
	
	
	/* Drawing Arena 2
	
	int s2x = 120;
	int s2y = 110;
	int swidth2 = 600/2 - gap_turn/2; // half width
	DrawRectangle(s2x, s2y, swidth2, sheight, scolor); // bottom left
	DrawRectangle(s2x + swidth2 + gap_turn, s2y, swidth2, sheight, scolor); // bottom right
	DrawRectangle(s2x+swidth2*2+gap_turn, s2y+sheight, sheight*2, swidth2, scolor); // right down
	DrawRectangle(s2x+swidth2*2+gap_turn, s2y+sheight+swidth2+gap_turn, sheight*2, swidth2, scolor); // right up
	DrawRectangle(s2x + swidth2 + gap_turn, s2y+610, swidth2, sheight, scolor); // top left
	DrawRectangle(s2x, s2y+610, swidth2, sheight, scolor); // top right
	DrawRectangle(s2x-sheight*2, s2y+sheight+swidth2+gap_turn, sheight*2, swidth2, scolor); // left up
	DrawRectangle(s2x-sheight*2, s2y+sheight, sheight*2, swidth2, scolor); // left down
	
	
	// Drawing Arena 3
	int s3x = 220;
	int s3y = 210;
	int s3width = 400/2 - gap_turn/2; // half width
	DrawRectangle(s3x, s3y, s3width, sheight, scolor); // bottom left
	DrawRectangle(s3x + s3width + gap_turn, s3y, s3width, sheight, scolor); // bottom right
	DrawRectangle(s3x+s3width*2+gap_turn, s3y+sheight, sheight*2, s3width, scolor); // right down
	DrawRectangle(s3x+s3width*2+gap_turn, s3y+sheight+s3width+gap_turn, sheight*2, s3width, scolor); // right up
	DrawRectangle(s3x + s3width + gap_turn, s3y+410, s3width, sheight, scolor); // top left
	DrawRectangle(s3x, s3y+410, s3width, sheight, scolor); // top right
	DrawRectangle(s3x-sheight*2, s3y+sheight+s3width+gap_turn, sheight*2, s3width, scolor); // left up
	DrawRectangle(s3x-sheight*2, s3y+sheight, sheight*2, s3width, scolor); // left down
	
	
	
	// Drawing Arena 5
	int s5x = 420;
	int s5y = 410;
	int s5width = gap_turn/2; // half width
	DrawRectangle(s5x, s5y, s5width, sheight, scolor); // bottom left
	DrawRectangle(s5x + s5width + gap_turn, s5y, s5width, sheight, scolor); // bottom right
	DrawRectangle(s5x+s5width*2+gap_turn, s5y+sheight, sheight*2, s5width, scolor); // right down
	DrawRectangle(s5x+s5width*2+gap_turn, s5y+sheight+s5width+gap_turn, sheight*2, s5width, scolor); // right up
	DrawRectangle(s5x + s5width + gap_turn, s5y+10, s5width, sheight, scolor); // top left
	DrawRectangle(s5x, s5y+10, s5width, sheight, scolor); // top right
	DrawRectangle(s5x-sheight*2, s5y+sheight+s5width+gap_turn, sheight*2, s5width, scolor); // left up
	DrawRectangle(s5x-sheight*2, s5y+sheight, sheight*2, s5width, scolor); // left down */
	
	
	


	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		if ((user_x == 735 || user_x == 115 || user_x == 635 || user_x == 215 || user_x ==535 || user_x==315)  && (user_y >= 360 && user_y <= 420)) {
			user_x -= 100;
		}

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if ((user_x == 15 || user_x == 635 || user_x == 115 || user_x == 535 || user_x==215 || user_x==435 || user_x==315 )  && (user_y >= 360 && user_y <= 420)) {
			user_x += 100;
		}

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
			if ((user_x >= 350 && user_x <= 430) && (user_y==40 || user_y == 655 || user_y == 140 || user_y == 555 || user_y==455 || user_y==240 ))
				user_y += 100;
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		if ((user_x >= 350 && user_x <= 430) && (user_y==755 || user_y == 140 || user_y == 655 || user_y == 240 || user_y==340 || user_y== 555))
			user_y -= 100;
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B')
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	
	/* if (key == 32) {
		if (user_y == 40)
			user_x += 5;
		else if (user_y == 755)
			user_x -= 5;
		else if (user_x == 735)
			user_y += 5;
		else if (user_x == 15)
			user_y -= 5;
	} */
			
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	if (user_x <= 730 && user_y == 40)
		user_x+=5;
	else if (user_x == 735 && user_y <= 750)
		user_y += 5;
	else if (user_x >= 20 && user_y == 755)
		user_x -=5;
	else if( user_x == 15 && user_y <= 755)
		user_y -=5;
	//2nd box
	else if (user_x == 635 && (user_y >= 140 && user_y <= 650))
		user_y += 5;
	else if (user_x >= 120 && (user_y==655 && user_x <= 635))
		user_x-=5;
	else if (user_x == 115 && (user_y >= 145 && user_y <= 655))
		user_y-=5;
	else if ((user_x >= 115 && user_x <= 630) && user_y == 140)
		user_x+=5;
	//3rd box
	else if ((user_x >= 215 && user_x <= 530) && user_y == 240)
		user_x += 5;
	else if (user_x == 535 && (user_y >= 240 && user_y <= 550))
		user_y += 5;
	else if ((user_x >= 220 && user_x <= 535) && user_y == 555)
		user_x-=5;
	else if (user_x == 215 && (user_y >= 245 && user_y <= 555))
		user_y -= 5;
	
	//4rd box
	else if ((user_x >= 315 && user_x <= 430) && user_y == 340)
		user_x += 5;
	else if (user_x == 435 && (user_y >= 340 && user_y <= 450))
		user_y += 5;
	else if ((user_x >= 320 && user_x <= 435) && user_y == 455)
		user_x-=5;
	else if (user_x == 315 && (user_y >= 345 && user_y <= 455))
		user_y -= 5;
	
	//opponent car
	if (x <= 735 && x >= 20 && y == 40)
		x-=5;
	else if (x == 15 && y <= 750)
		y += 5;
	else if (x >= 15 && x <= 730 && y == 755)
		x+=5;
	else if( x == 735 && y <= 755 && y >= 45)
		y-=5;
		
	if (x == user_x && y == user_y) {
		user_x = 500; 
		user_y = 40; 
		x = 250; 
		y = 40;
	}
	
	
	glutPostRedisplay();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(30, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 840, height = 900; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Centipede"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(30, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
