#include "PaintApp.h"
#include <iostream>
#include <math.h>
#include <string>

#include <deque>     //added

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

std::deque<PaintApp*> points;

PaintApp::PaintApp(){     //Default Constructor
	x = 0;
	y = 0;

	r = 1;
	g = 0;
	b = 0;
}

PaintApp::PaintApp(float x, float y, float r, float g, float b) {     //Custom Constructor
    this->x = x;
    this->y = y;

    this->r = r;
    this->g = g;
    this->b = b;
}

void PaintApp::renderText(std::string text, float x, float y, void* font, float r, float g, float b) {
	int width = 640, height = 640;

    glColor3f(r, g, b);
    float offset = 0;
    for (int i = 0; i < text.length(); i++) {
        glRasterPos3f(x+offset, y, 1);
        glutBitmapCharacter(font, text[i]);
        int w = glutBitmapWidth(font, text[i]);
        offset += ((float)w / width)*2;
    }
}

void PaintApp::click(float mx, float my) {          //Default: on click, purple paint for brush
	points.push_front(new PaintApp(mx, my, 1, 0, 1));
}
void PaintApp::eraserClick(float mx, float my) {    //on click, white paint for eraser
	points.push_front(new PaintApp(mx, my, 1, 1, 1));
}
void PaintApp::redClick(float mx, float my) {       //on click, red paint for brush
	points.push_front(new PaintApp(mx, my, 1, 0, 0));
}
void PaintApp::greenClick(float mx, float my) {     //on click, green paint for brush
	points.push_front(new PaintApp(mx, my, 0, 1, 0));
}
void PaintApp::blueClick(float mx, float my) {      //on click, blue paint for brush
	points.push_front(new PaintApp(mx, my, 0, 0, 1));
}

void PaintApp::drawPoint(){
    for(int i = 0; i < points.size(); i++) {
		points[i]->draw();
	}
}
void PaintApp::draw(){
    glColor3f(r, g, b);
	glPointSize(10);

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
