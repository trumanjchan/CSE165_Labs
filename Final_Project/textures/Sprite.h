#pragma once

#include "TexRect.h"

//Using Sprite Sheets from: https://opengameart.org/content/pixel-characters-tiles-ai

class Sprite: public TexRect {
	int rows;
	int cols;

	float xinc;
	float yinc;

	int curr_row;
	int curr_col;

	float left;
	float right;
	float top;
	float bottom;

	bool done;
    
public:
    Sprite(const char* filename, int rows, int cols, float x, float y, float w, float h);

	void draw();
	
	bool isDone () const;

	void reset();
	void resetUp();
	void resetLeft();
	void resetDown();
	void resetRight();

	void advance();
	void advanceUp();
	void advanceLeft();
	void advanceDown();
	void advanceRight();

	void mobAdvance();

	//void fire(float, float);

	~Sprite();
};
