#ifndef RECT_H
#define RECT_H

#include <vector>

struct Rect {
	float x;
	float y;

	float red;
	float green; 
	float blue;

	float w;
	float h;

	bool selected;
	bool deselected;
	bool start;        //Starts

	bool WinnerX;      //X Wins!
	bool WinnerO;      //O Wins!

	Rect(); // This is a default constructor (takes no parameters)

	Rect(float x, float y, float w, float h);

	Rect(float x, float y, float w, float h, float red, float green, float blue);

	void draw();

	bool contains(float x, float y);

	void select();     //Left click: Red X
	void deselect();   //Right click: Green O

	bool checkXWinner(std::vector<Rect*> rects);     //Called every time someone makes a move, to see if that player has 3 in a row.
	bool checkOWinner(std::vector<Rect*> rects);     //Called every time someone makes a move, to see if that player has 3 in a row.

	bool computerResponse(std::vector<Rect*> rects);
};


#endif
