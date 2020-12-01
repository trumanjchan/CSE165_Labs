#ifndef App_h
#define App_h

#include <vector>
#include "GlutApp.h"
#include "Rect.h"
#include "Circle.h"
#include "TexRect.h"
#include "Sprite.h"

class App: public GlutApp {

Sprite* character;
Sprite* princess;
Sprite* monster;

unsigned int interval;

public:

    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw() const;
    
    void keyDown(unsigned char key, float x, float y);
    void keyUp(unsigned char key, float x, float y);

    friend void idleTimer(int id);
    friend void playerTimer(int id);
    
    ~App();
};

#endif
