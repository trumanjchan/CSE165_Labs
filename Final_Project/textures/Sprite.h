#pragma once

#include "TexRect.h"

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
    Sprite(const char* filename, int rows, int cols, float x, float y, float w, float h): TexRect(filename, x, y, w, h){
		this->rows = rows;
		this->cols = cols;

		xinc = 1.0 / cols;
		yinc = 1.0 / rows;

		curr_row = 1;
		curr_col = 1;

		right = xinc * (curr_col - 1);
		left = xinc * curr_col;
		top = 1 - yinc * (curr_row - 1);
		bottom = 1 - yinc * curr_row;

		done = false;
	}

	void draw(float z = 0){
		glBindTexture( GL_TEXTURE_2D, texture_id );
		glEnable(GL_TEXTURE_2D);
		
		glBegin(GL_QUADS);
		glColor4f(1, 1, 1, 1);
		glTexCoord2f(left, bottom);
		glVertex3f(x, y - h, z);
		
		glTexCoord2f(left, top);
		glVertex3f(x, y, z);
		
		glTexCoord2f(right, top);
		glVertex3f(x+w, y, z);
		
		glTexCoord2f(right, bottom);
		glVertex3f(x+w, y - h, z);
		
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
	}
	
	bool isDone () const {
		return done;
	}


	void reset(){       //Default reset
		curr_row = 1;
		curr_col = 1;
		done = false;
	}
	void resetUp(){     //These are for resetting character frames when a movement key is pressed down
		curr_row = 2;
		curr_col = 1;
		done = false;
	}
	void resetLeft(){
		curr_row = 1;
		curr_col = 1;
		done = false;
	}
	void resetDown(){
		curr_row = 3;
		curr_col = 1;
		done = false;
	}
	void resetRight(){
		curr_row = 1;
		curr_col = 1;
		done = false;
	}


	void advance(){     //Princess waiting to be rescued
		if (!done){
			if (curr_col < 2){
				curr_col++;
			}
			else{
				done = true;
				curr_row = 1;
				curr_col = 1;
			}
			left = xinc * (curr_col - 1);
			right = xinc * curr_col;
			top = 1 - yinc * (curr_row - 1);
			bottom = 1 - yinc * curr_row;
		}
	}
	void advanceUp(){     //Below are the frame advance loops for movement key-down for the player
		if (!done){
			if (curr_col < cols){
				curr_col++;
			}
			else{
				if (curr_col = cols){
					done = true;
					curr_row = 2;
					curr_col = 1;
				}
			}
			left = xinc * (curr_col - 1);
			right = xinc * curr_col;
			top = 1 - yinc * (curr_row - 1);
			bottom = 1 - yinc * curr_row;
		}
	}
	void advanceLeft(){
		if (!done){
			if (curr_col < cols){
				curr_col++;
			}
			else{
				if (curr_col = cols){
					done = true;
					curr_row = 1;
					curr_col = 1;
				}
			}
			left = xinc * (curr_col - 1);
			right = xinc * curr_col;
			top = 1 - yinc * (curr_row - 1);
			bottom = 1 - yinc * curr_row;
		}
	}
	void advanceDown(){
		if (!done){
			if (curr_col < cols){
				curr_col++;
			}
			else{
				if (curr_col = cols){
					done = true;
					curr_row = 3;
					curr_col = 1;
				}
			}
			left = xinc * (curr_col - 1);
			right = xinc * curr_col;
			top = 1 - yinc * (curr_row - 1);
			bottom = 1 - yinc * curr_row;
		}
	}
	void advanceRight(){
		if (!done){
			if (curr_col < cols){
				curr_col++;
			}
			else{
				if (curr_col = cols){
					done = true;
					curr_row = 1;
					curr_col = 1;
				}
			}
			right = xinc * (curr_col - 1);     //Swapped this and next line together, to change facing orientation
			left = xinc * curr_col;
			top = 1 - yinc * (curr_row - 1);
			bottom = 1 - yinc * curr_row;
		}
	}

	~Sprite(){

	}
};
