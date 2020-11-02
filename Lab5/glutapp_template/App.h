#ifndef App_h
#define App_h

#include <string> //Added

#include "GlutApp.h"
#include "Rect.h"

class App: public GlutApp {     //App is a child of GlutApp. Inherits from GlutApp.

    Rect* player;
    Rect* enemy;

public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw();
    
    void keyDown(unsigned char key, float x, float y);

    void renderText(std::string text, float x, float y, void* font, float r, float g, float b); //From Lab 4
    void fire(float x, float y);

    ~App();
    
};

#endif
