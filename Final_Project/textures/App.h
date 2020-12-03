#ifndef App_h
#define App_h

#include <vector>
#include "GlutApp.h"
#include "Rect.h"
#include "Circle.h"
#include "TexRect.h"
#include "Sprite.h"
#include <string>

class App: public GlutApp {

Sprite* character;
Sprite* princess;
Sprite* monster;
Sprite* mob1;
Sprite* mob2;
Sprite* mob3;
TexRect* weapon;
TexRect* holdWeapon;
TexRect* ammunition;
TexRect* bg;

unsigned int interval;

public:
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw() const;
    
    void keyDown(unsigned char key, float x, float y);
    void keyUp(unsigned char key, float x, float y);

    friend void idleTimer(int id);
    friend void playerTimer(int id);

    friend void mobTimer1(int id);
    friend void mobTimer2(int id);
    friend void mobTimer3(int id);

    void idle();
    void leftMouseDown(float, float);

    void renderText(std::string text, float x, float y, void* font, float r, float g, float b) const;
    
    ~App();
};

#endif
