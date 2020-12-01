#include "Sprite.h"
#include <iostream>
#include <deque>

extern std::deque<Sprite *> projectile;

Sprite::Sprite(const char *filename, int rows, int cols, float x, float y, float w, float h) : TexRect(filename, x, y, w, h){
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

void Sprite::draw(){
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(left, bottom);
    glVertex3f(x, y - h, 0);

    glTexCoord2f(left, top);
    glVertex3f(x, y, 0);

    glTexCoord2f(right, top);
    glVertex3f(x + w, y, 0);

    glTexCoord2f(right, bottom);
    glVertex3f(x + w, y - h, 0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

bool Sprite::isDone() const{
    return done;
}

void Sprite::reset(){     //Default reset
    curr_row = 1;
    curr_col = 1;
    done = false;
}
void Sprite::resetUp(){     //These are for resetting character frames when a movement key is pressed down
    curr_row = 2;
    curr_col = 1;
    done = false;
}
void Sprite::resetLeft(){
    curr_row = 1;
    curr_col = 1;
    done = false;
}
void Sprite::resetDown(){
    curr_row = 3;
    curr_col = 1;
    done = false;
}
void Sprite::resetRight(){
    curr_row = 1;
    curr_col = 1;
    done = false;
}

void Sprite::advance(){     //Princess waiting to be rescued
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
void Sprite::advanceUp(){     //Below are the frame advance loops for movement key-down for the player
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
void Sprite::advanceLeft(){
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
void Sprite::advanceDown(){
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
void Sprite::advanceRight(){
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


void Sprite::mobAdvance() {
    if (!done){
        if (curr_col < cols){
            curr_col++;
        }
        else{
            if (curr_col = cols){
                done = true;
                curr_row = 5;
                curr_col = 5;
            }
        }
        left = xinc * (curr_col - 1);
        right = xinc * curr_col;
        top = 1 - yinc * (curr_row - 1);
        bottom = 1 - yinc * curr_row;
    }
}

// void Sprite::fire(float x, float y) {
//     projectile.push_front( new Sprite("Character_Main.png", 3,6,  -1.65,0.15,  0.3,0.3) );     //creates new projectiles at location
// }

Sprite::~Sprite(){

}