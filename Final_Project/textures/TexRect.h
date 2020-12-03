#ifndef TexRect_h
#define TexRect_h

#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include "SOIL.h"
#else
#include <GL/freeglut.h>
#include "SOIL.h"
#endif

//Background from: https://opengameart.org/content/2d-cartoon-backgrounds-random-town-locations

class TexRect: public Rect {
protected:
    GLuint texture_id;
    
    int texwidth;
    int texheight;
    
public:
    TexRect(const char*, float, float, float, float);
    
    void draw(float z=0) const;
    void drawBG(float z=0) const;
    void drawBullets() const;

    bool contains(float, float) const;
};

#endif
