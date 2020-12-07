#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Rect::Rect(){
	x = 0;
	y = 0;
	red = 1;
	green = 0;
	blue = 0;

	w = 0.2;
	h = 0.2;

	selected = false;
}

Rect::Rect(float x, float y, float w, float h){
	this->x = x;
	this->y = y;

	red = 1;
	green = 0;
	blue = 0;

	this->w = w;
	this->h = h;

	selected = false;
}

Rect::Rect(float x, float y, float w, float h, float red, float green, float blue){
	this->x = x;
	this->y = y;

	this->red = red;
	this->green = green;
	this->blue = blue;

	this->w = w;
	this->h = h;

	selected = false;
}

bool Rect::contains(float x, float y){
	return (x > this->x) && (x < this->x + this->w) && (y < this->y) && (y > this->y - this->h);
}

bool Rect::containsResizeCorner(float x, float y) {
	return (x > x+0.15) && (x < x+0.15 + 0.05) && (y < y-0.15) && (y > y-0.15 - 0.05);     //Not sure why this never worked
}


void Rect::moveUp(){
	y += 0.05;
}

void Rect::moveDown(){
	y -= 0.05;
}

void Rect::moveLeft(){
	x -= 0.05;
}

void Rect::moveRight(){
	x += 0.05;
}

void Rect::select(){
	selected = true;
}

void Rect::deselect(){
	selected = false;
}



void Rect::draw(){

	if (selected){

		glColor3f(1,1,1);
		glBegin(GL_LINES);     //Selection box effect

		glVertex3f(x, y, 0.1);
		glVertex3f(x+w, y, 0.1);

		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y, 0.1);

		glEnd();

		glColor3f(1, 1, 1);     //Draws resizeable box
		glBegin(GL_LINES);
		glVertex3f(x+w, y-h, 0.1);  //top left
		glVertex3f(x+w+0.05, y-h, 0.1);  //top right

		glVertex3f(x+w+0.05, y-h, 0.1);
		glVertex3f(x+w+0.05, y-h-0.05, 0.1);  //bottom right
		
		glVertex3f(x+w+0.05, y-h-0.05, 0.1);
		glVertex3f(x+w, y-h-0.05, 0.1);  //bottom left
		
		glVertex3f(x+w, y-h-0.05, 0.1);
		glVertex3f(x+w, y-h, 0.1);  //top left
		glEnd();
		
		glColor3f(red, green, blue);     //Redraws rectangles
		glBegin(GL_POLYGON);
		glVertex3f(x, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glEnd();
	}
	else{
		glColor3f(red, green, blue);

		glBegin(GL_POLYGON);     //Default draw rectangles with no selection box effect

		glVertex2f(x, y);
		glVertex2f(x+w, y);
		glVertex2f(x+w, y-h);
		glVertex2f(x, y-h);

		glEnd();
	}
}
