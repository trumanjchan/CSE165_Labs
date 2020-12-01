#include <iostream>
#include "App.h"

static App* singleton;

bool moveUp;
bool moveLeft;
bool moveDown;
bool moveRight;


void idleTimer(int id){
    singleton->princess->advance();
    singleton->redraw();
    if (singleton->princess->isDone()){
        singleton->princess->reset();
    }
    glutTimerFunc(1200, idleTimer, id);
}
void playerTimer(int id){
    if (moveUp) {
        singleton->character->advanceUp();
        singleton->redraw();
        if (singleton->character->isDone()){
            singleton->character->resetUp();
        }
    }
    if (moveLeft) {
        singleton->character->advanceLeft();
        singleton->redraw();
        if (singleton->character->isDone()){
            singleton->character->resetLeft();
        }
    }
    if (moveDown) {
        if (singleton->character->isDone()){
            singleton->character->resetDown();
        }
        singleton->character->advanceDown();
        singleton->redraw();
    }
    if (moveRight) {
        singleton->character->advanceRight();
        singleton->redraw();
        if (singleton->character->isDone()){
            singleton->character->resetRight();
        }
    }
    glutTimerFunc(56, playerTimer, id);
}

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){

    // Pushing different kinds of Shape in the collection
    princess = new Sprite("Character_Princess.png", 3,6,  1.4,0.15,  0.3,0.3);     // filename, rows,cols, x,y, w,h
    character = new Sprite("Character_Main.png", 3,6,  -1.65,0.15,  0.3,0.3);
    monster = new Sprite("Slime_Green.png", 6,5,  -0.1,-0.1,  0.2,0.2);

    singleton = this;
    idleTimer(1);      // idle moving princess
    playerTimer(2);    // moving character
} 

void App::draw() const {
    princess->draw();
    character->draw();
    monster->draw();
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 'w'){
        moveUp = !moveUp;
        character->setY( character->getY() + 0.03 );
    }
    if (key == 'a'){
        moveLeft = !moveLeft;
        character->setX( character->getX() - 0.03 );
    }
    if (key == 's'){
        moveDown = !moveDown;
        character->setY( character->getY() - 0.03 );
    }
    if (key == 'd'){
        moveRight = !moveRight;
        character->setX( character->getX() + 0.03 );
    }
    if (key == 27){
        exit(0);
    }
}
void App::keyUp(unsigned char key, float x, float y){
    if (key == 'w'){
        moveUp = !moveUp;
    }
    if (key == 'a'){
        moveLeft = !moveLeft;
    }
    if (key == 's'){
        moveDown = !moveDown;
    }
    if (key == 'd'){
        moveRight = !moveRight;
    }
}

App::~App(){
    delete princess;
    delete character;
    delete monster;
    std::cout << "Exiting..." << std::endl;
}
