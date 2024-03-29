#include <iostream>
#include <math.h>
#include <vector>
#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;


// Store the width and height of the window
int width = 640, height = 640;

extern vector<Rect*> rects;

bool singleplayer;

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (int i = 0; i < rects.size(); i++) {
		rects[i]->draw();
	}

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	// Your code here...

	for (int i = 0; i < rects.size(); i++) {     //Default: if left click,
		if (rects[i]->contains(mx,my)) {
			rects[i]->select();
			rects[i]->checkXWinner(rects);
			singleplayer = true;
			break;
		}
	}
	switch (b) {                                 //if right click,
	case GLUT_RIGHT_BUTTON:
		for (int i = 0; i < rects.size(); i++) {
			if (rects[i]->contains(mx,my)) {
				rects[i]->deselect();
				rects[i]->checkOWinner(rects);
				break;
			}
		}
	}

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	// Your code here...

	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {

	//bool singleplayer;

	// Define what should happen for a given key press 
	switch (key) {	
	case 32:                                         //Spacebar to restart round
		for (int i = 0; i < rects.size(); i++) {
			rects[i]->selected = false;
			rects[i]->deselected = false;
			rects[i]->start = false;
			rects[i]->WinnerX = false;
			rects[i]->WinnerO = false;
		}
		break;
		// More cases here if you need...

		case 13:                                     //Enters Player vs. AI mode, where AI plays first.
		for (int i = 0; i < rects.size(); i++) {     //Wipes the board
			rects[i]->selected = false;
			rects[i]->deselected = false;
			rects[i]->start = false;
			rects[i]->WinnerX = false;
			rects[i]->WinnerO = false;
			singleplayer = false;
		}
		rects[0]->deselect();
		if (singleplayer = true) {
			for (int i = 1; i < rects.size(); i++) {
				rects[i]->computerResponse(rects);
				singleplayer = false;
			}
		}
		// rects[0]->deselect();                        //AI plays first, and players alternate.
		// for (int i = 1; i < rects.size(); i++) {
		// 	if (singleplayer == false && rects[i]->contains(x,y)) {           //My turn
		// 		rects[i]->select();
		// 		singleplayer = true;
		// 		break;
		// 	}
		// 	if (singleplayer == true) {               //AI's turn
		// 		if (!rects[i]->selected) {
		// 			rects[i]->deselect();
		// 			singleplayer = false;
		// 			break;
		// 		}
		// 		else {
		// 			rects[i+1]->deselect();
		// 			singleplayer = false;
		// 			break;
		// 		}
		// 	}
		// }

	}

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}

void appKeyboardUpFunc(unsigned char key, int x, int y) {

}

void idle(){

}


int main(int argc, char** argv) {

	rects.push_back(new Rect(-0.8, 0.8, 0.5, 0.5));
	rects.push_back(new Rect(-0.2, 0.8, 0.5, 0.5));
	rects.push_back(new Rect(0.4, 0.8, 0.5, 0.5));

	rects.push_back(new Rect(-0.8, 0.2, 0.5, 0.5));
	rects.push_back(new Rect(-0.2, 0.2, 0.5, 0.5));
	rects.push_back(new Rect(0.4, 0.2, 0.5, 0.5));

	rects.push_back(new Rect(-0.8, -0.4, 0.5, 0.5));
	rects.push_back(new Rect(-0.2, -0.4, 0.5, 0.5));
	rects.push_back(new Rect(0.4, -0.4, 0.5, 0.5));

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	// Start with a slightly smaller window (bug in macOS Catalina)
	glutInitWindowSize(width-1, height-1);

	// Create the window
	glutCreateWindow("CSE165 OpenGL Demo");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);


	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
	glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);

	// This gets triggered when we release a keyboard key
	glutKeyboardUpFunc(appKeyboardUpFunc);
    
	// Resize your window to the desired size (bug in macOS Catalina)
    glutReshapeWindow(width, height);

	// Set the idle function. It gets called repeatedly all the time
	glutIdleFunc(idle);

	// Start the main loop
	glutMainLoop();
}
