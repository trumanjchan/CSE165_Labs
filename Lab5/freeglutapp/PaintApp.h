#ifndef PAINTAPP_H
#define PAINTAPP_H

#include <string>


struct PaintApp{
	float x;
	float y;

	float r;
	float g;
	float b;

    PaintApp();     //Default constructor
	PaintApp(float x, float y, float r, float g, float b);     //Custom constructor

	void renderText(std::string text, float x, float y, void* font, float r, float g, float b);

	void playerClick(float mx, float my);
	void enemyClick(float mx, float my);
	void eraserClick(float, float);

	void drawPoint();
	void draw();
};


#endif