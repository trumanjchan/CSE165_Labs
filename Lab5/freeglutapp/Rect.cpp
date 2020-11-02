#include "Rect.h"
#include <deque>
#include <iostream>
#include <math.h>
#include <string>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

std::deque<Rect *> rects;
std::deque<Rect *> projectile;

Rect::Rect(){
	x = -1;
	y = -0.8;
	red = 0;
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

void Rect::moveUp(){
	y += 0.1;
}
void Rect::moveDown(){
	y -= 0.1;
}
void Rect::moveLeft(){
	x -= 0.1;
}
void Rect::moveRight(){
	x += 0.1;
}
void Rect::fire(float x, float y){
	projectile.push_front(new Rect( x, y, 0.1, 0.1,  1,1,1));     //White bullets
	drawProjectile();
}
void Rect::drawProjectile(){
	for (int i = 0; i < projectile.size(); i++){
		projectile[i]->draw();
	}
}

void Rect::select(){
	selected = true;
}
void Rect::deselect(){
	selected = false;
}

void Rect::drawRect(){
	for (int i = 0; i < rects.size(); i++){
		rects[i]->draw();
	}
}
void Rect::draw(){
	if (selected) {
		glColor3f(0, 1, 1);    //cyan border effect
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


		glColor3f(red, green, blue); //Rectangles

		glBegin(GL_POLYGON);

		glVertex3f(x, y, 1);
		glVertex3f(x + w, y, 1);
		glVertex3f(x + w, y - h, 1);
		glVertex3f(x, y - h, 1);

		glEnd();
	}
	else {
		glColor3f(red, green, blue); //Rectangles

		glBegin(GL_POLYGON);

		glVertex3f(x, y, 1);
		glVertex3f(x + w, y, 1);
		glVertex3f(x + w, y - h, 1);
		glVertex3f(x, y - h, 1);

		glEnd();
	}
}
