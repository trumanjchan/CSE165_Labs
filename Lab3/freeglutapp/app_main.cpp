#include <iostream>
#include <math.h>
#include <deque>
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


deque<Rect*> rects;
bool draggable = false;
//bool moveable = false;

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


	for (int i = 0; i < rects.size(); i++){
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

	for (deque<Rect*>::iterator i = rects.begin(); i != rects.end(); i++) {
		(*i)->deselect();
	}

	for (deque<Rect*>::iterator i = rects.begin(); i != rects.end(); i++) {
		if ( (*i)->contains(mx, my) || s == 1) {  // || s == 1
			(*i)->select();
			rects.erase(i);
			rects.push_front(*i);
			break;
		}
	}

	for (deque<Rect*>::iterator i = rects.begin(); i != rects.end(); i++) {
		if ( (*i)->contains(mx, my) && s == 0) {     // s == 0 : mouse-down
			draggable = true;
		}
	}

	if (s == 1) {
		draggable = false;
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

	if (draggable == true) {     //Allows dragging in the center of rectangles
		rects[0]->x = mx - rects[0]->w/2;
		rects[0]->y = my + rects[0]->h/2;
	}
	else {     //Allows resizing the selected, if dragging outside of the selected rectangle
		rects[0]->w = mx - rects[0]->x;
		rects[0]->h = ( (-1)*(my - rects[0]->y) );
	}


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
	// Define what should happen for a given key press 
	switch (key) {	
	// Escape was pressed. Quit the program
	case 27:
		exit(0);
		break;
	// More cases here if you need...
	}

	glutPostRedisplay();
}

void appKeyboardUpFunc(unsigned char key, int x, int y) {

}

void idle(){

}


int main(int argc, char** argv) {

	rects.push_back(new Rect(-0.5, 0.5, 0.5, 0.5, 0,0,1));
	rects.push_back(new Rect(-0.8, 0.8, 0.5, 0.5, 1,0,0));
	//rects.push_back(new Rect(0.5, -0.4, 0.4, 0.4, 0,1,0));


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
