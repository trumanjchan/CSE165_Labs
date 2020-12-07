#include "Rect.h"
#include <math.h>
#include <vector>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <Windows.h>
#else
#include <GL/freeglut.h>
#include <unistd.h>     //Can use sleep()
#endif

Rect::Rect(){
	x = 0;
	y = 0;
	red = 1;
	green = 0;
	blue = 0;

	w = 0.2;
	h = 0.2;
}

Rect::Rect(float x, float y, float w, float h){
	this->x = x;
	this->y = y;

	red = 1;     //default white squares
	green = 1;
	blue = 1;

	this->w = w;
	this->h = h;

	selected = false;
	deselected = false;
	start = false;

	WinnerX = false;
	WinnerO = false;
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
	deselected = false;
	start = false;

	WinnerX = false;
	WinnerO = false;
}

bool Rect::contains(float x, float y) {
	return (x > this->x) && (x < this->x + this->w) && (y < this->y) && (y > this->y - this->h);
}

void Rect::select() {
	selected = true;
	deselected = false;
	start = true;

	WinnerX = false;
	WinnerO = false;
}
void Rect::deselect() {
	selected = false;
	deselected = true;
	start = true;

	WinnerX = false;
	WinnerO = false;
}

std::vector<Rect*> rects;
bool Rect::checkXWinner(std::vector<Rect*> rects) {
	if (rects[0]->selected && rects[1]->selected && rects[2]->selected) {     //These three to check horizontally
		WinnerX = true;
	}
	else if (rects[3]->selected && rects[4]->selected && rects[5]->selected) {
		WinnerX = true;
	}
	else if (rects[6]->selected && rects[7]->selected && rects[8]->selected) {
		WinnerX = true;
	}
	else if (rects[0]->selected && rects[3]->selected && rects[6]->selected) {     //These three to check vertically
		WinnerX = true;
	}
	else if (rects[1]->selected && rects[4]->selected && rects[7]->selected) {
		WinnerX = true;
	}
	else if (rects[2]->selected && rects[5]->selected && rects[8]->selected) {
		WinnerX = true;
	}
	else if (rects[0]->selected && rects[4]->selected && rects[8]->selected) {     //These two to check diagonally
		WinnerX = true;
	}
	else if (rects[2]->selected && rects[4]->selected && rects[6]->selected) {
		WinnerX = true;
	}
}
bool Rect::checkOWinner(std::vector<Rect*> rects) {
	if (rects[0]->deselected && rects[1]->deselected && rects[2]->deselected) {     //These three to check horizontally
		WinnerO = true;
	}
	else if (rects[3]->deselected && rects[4]->deselected && rects[5]->deselected) {
		WinnerO = true;
	}
	else if (rects[6]->deselected && rects[7]->deselected && rects[8]->deselected) {
		WinnerO = true;
	}
	else if (rects[0]->deselected && rects[3]->deselected && rects[6]->deselected) {     //These three to check vertically
		WinnerO = true;
	}
	else if (rects[1]->deselected && rects[4]->deselected && rects[7]->deselected) {
		WinnerO = true;
	}
	else if (rects[2]->deselected && rects[5]->deselected && rects[8]->deselected) {
		WinnerO = true;
	}
	else if (rects[0]->deselected && rects[4]->deselected && rects[8]->deselected) {     //These two to check diagonally
		WinnerO = true;
	}
	else if (rects[2]->deselected && rects[4]->deselected && rects[6]->deselected) {
		WinnerO = true;
	}
}

bool Rect::computerResponse(std::vector<Rect*> rects) {
	for (int i = 1; i < rects.size(); i++) {
		if (!rects[i]->selected) {     
			rects[i]->deselect();
			break;
		}
		else {
			rects[i+1]->deselect();
			break;
		}
	}
}

void Rect::draw(){
	if (selected == true && start == true && WinnerX == false && WinnerO == false) {

		glColor3f(1,1,1);     //draws white outline box, but squares disappear
		glBegin(GL_LINES);
		glVertex3f(x, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y, 0.1);
		glEnd();

		glColor3f(1, 0, 0);     //draws X's with red color
		glBegin(GL_LINES);
		glVertex2f(x+0.15, y-0.15);
		glVertex2f(x+w-0.15, y-h+0.15);
		glEnd();
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(x+w-0.15, y-0.15);
		glVertex2f(x+0.15, y-h+0.15);
		glEnd();
	}
	else if (deselected == true && start == true && WinnerX == false && WinnerO == false) {
		glColor3f(1,1,1);     //draws white outline box, but squares disappear
		glBegin(GL_LINES);
		glVertex3f(x, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y, 0.1);
		glEnd();

		glColor3f(0, 1, 0);     //draws O's with green color
		glBegin(GL_LINES);
		glVertex2f(x+0.15, y-0.15);
		glVertex2f(x+w-0.15, y-0.15);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x+w-0.15, y-0.15);
		glVertex2f(x+w-0.15, y-h+0.15);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x+w-0.15, y-h+0.15);
		glVertex2f(x+0.15, y-h+0.15);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x+0.15, y-h+0.15);
		glVertex2f(x+0.15, y-0.15);
		glEnd();
	}
	else if (WinnerX == true) {     //X Wins!
		glColor3f(1,1,1);           //draws white outline box, but squares disappear
		glBegin(GL_LINES);
		glVertex3f(x, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y, 0.1);
		glEnd();

		glColor3f(1, 0, 0);      //draws an "x" with red color
		glBegin(GL_LINES);
		glVertex2f(x+0.20, y-0.20);
		glVertex2f(x+w-0.20, y-h+0.20);
		glEnd();
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(x+w-0.20, y-0.20);
		glVertex2f(x+0.20, y-h+0.20);
		glEnd();

		glColor3f(1, 1, 1);      //left "W" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.07, y-0.32);
		glVertex2f(x+w-0.40, y-h+0.10);
		glEnd();
		glColor3f(1, 1, 1);      //left mid-"W" segment
		glBegin(GL_LINES);
		glVertex2f(x+w-0.40, y-h+0.10);
		glVertex2f(x+0.15, y-0.35);
		glEnd();
		glColor3f(1, 1, 1);      //right mid-"W" segment
		glBegin(GL_LINES);
		glVertex2f(x+0.15, y-0.35);
		glVertex2f(x+w-0.30, y-h+0.10);
		glEnd();
		glColor3f(1, 1, 1);      //Right "W" segment
		glBegin(GL_LINES); 
		glVertex2f(x+w-0.30, y-h+0.10);
		glVertex2f(x+0.23, y-0.32);
		glEnd();
		glColor3f(1, 1, 1);      //Top "I" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.26, y-0.32);
		glVertex2f(x+0.33, y-0.32);
		glEnd();
		glColor3f(1, 1, 1);      //Bottom "I" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.26, y-0.40);
		glVertex2f(x+0.33, y-0.40);
		glEnd();
		glColor3f(1, 1, 1);      //Middle "I" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.295, y-0.32);
		glVertex2f(x+0.295, y-0.40);
		glEnd();
		glColor3f(1, 1, 1);      //Left "N" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.36, y-0.40);
		glVertex2f(x+0.38, y-0.32);
		glEnd();
		glColor3f(1, 1, 1);      //Middle "N" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.38, y-0.32);
		glVertex2f(x+0.42, y-0.40);
		glEnd();
		glColor3f(1, 1, 1);      //Right "N" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.42, y-0.40);
		glVertex2f(x+0.44, y-0.32);
		glEnd();
	}
	else if (WinnerO == true) {     //O Wins!
		glColor3f(1,1,1);           //draws white outline box, but squares disappear
		glBegin(GL_LINES);
		glVertex3f(x, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x+w, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y-h, 0.1);
		glVertex3f(x, y, 0.1);
		glEnd();

		glColor3f(0, 1, 0);     //draws O's with green color
		glBegin(GL_LINES);
		glVertex2f(x+0.20, y-0.20);
		glVertex2f(x+w-0.20, y-0.20);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x+w-0.20, y-0.20);
		glVertex2f(x+w-0.20, y-h+0.20);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x+w-0.20, y-h+0.20);
		glVertex2f(x+0.20, y-h+0.20);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x+0.20, y-h+0.20);
		glVertex2f(x+0.20, y-0.20);
		glEnd();

		glColor3f(1, 1, 1);      //left "W" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.07, y-0.32);
		glVertex2f(x+w-0.40, y-h+0.10);
		glEnd();
		glColor3f(1, 1, 1);      //left mid-"W" segment
		glBegin(GL_LINES);
		glVertex2f(x+w-0.40, y-h+0.10);
		glVertex2f(x+0.15, y-0.35);
		glEnd();
		glColor3f(1, 1, 1);      //right mid-"W" segment
		glBegin(GL_LINES);
		glVertex2f(x+0.15, y-0.35);
		glVertex2f(x+w-0.30, y-h+0.10);
		glEnd();
		glColor3f(1, 1, 1);      //Right "W" segment
		glBegin(GL_LINES); 
		glVertex2f(x+w-0.30, y-h+0.10);
		glVertex2f(x+0.23, y-0.32);
		glEnd();
		glColor3f(1, 1, 1);      //Top "I" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.26, y-0.32);
		glVertex2f(x+0.33, y-0.32);
		glEnd();
		glColor3f(1, 1, 1);      //Bottom "I" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.26, y-0.40);
		glVertex2f(x+0.33, y-0.40);
		glEnd();
		glColor3f(1, 1, 1);      //Middle "I" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.295, y-0.32);
		glVertex2f(x+0.295, y-0.40);
		glEnd();
		glColor3f(1, 1, 1);      //Left "N" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.36, y-0.40);
		glVertex2f(x+0.38, y-0.32);
		glEnd();
		glColor3f(1, 1, 1);      //Middle "N" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.38, y-0.32);
		glVertex2f(x+0.42, y-0.40);
		glEnd();
		glColor3f(1, 1, 1);      //Right "N" segment
		glBegin(GL_LINES); 
		glVertex2f(x+0.42, y-0.40);
		glVertex2f(x+0.44, y-0.32);
		glEnd();
	}
	else {     //(selected == false && deselected == false && start == false && WinnerX == false && WinnerO = false)
		glColor3f(red, green, blue);     //default squares with no outline. Line 26.
		glBegin(GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x+w, y);
		glVertex2f(x+w, y-h);
		glVertex2f(x, y-h);
		glEnd();
	}
}