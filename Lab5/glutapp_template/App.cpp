#include <iostream>
#include "App.h"

#include <deque>

std::deque<Rect*> projectile;
bool win;
bool lose;

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    player = new Rect();
    enemy = new Rect(-0.2, 0.8, 0.4, 0.4,  1,0,0);
}

void App::draw(){

    player->draw();
    enemy->draw();

    for (int i = 0; i < projectile.size(); i++) {
        projectile[i]->draw();
        projectile[i]->y += 0.05;
        redraw();
        if (enemy->contains(projectile[i]->x, projectile[i]->y) || enemy->contains(projectile[i]->x + 0.1, projectile[i]->y) ) { //Detects top left and top right of Projectile on Enemy.
			win = true;
			lose = false;
		}
    }
	if (enemy->contains( player->x + 0.05, player->y) || enemy->contains( player->x + 0.2, player->y) || enemy->contains( player->x + 0.2, player->y - 0.2) || enemy->contains( player->x + 0.05, player->y - 0.2)) { //Detects mid top, top right corner, bottom right corner, and mid bot of Player on Enemy.
		lose = true;
		win = false;
	}
	if (win) {
		renderText("YOU WIN!", -0.5, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, 0,1,0);     //Renders text in green
	}
	if (lose) {
		renderText("GAME OVER", 0.1, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, 1,0,0);     //Renders text in red
	}

}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){           //ESC key to exit.
        exit(0);
    }
    else if (key == 'w'){     //W key
        player->setY( player->getY() + 0.1 );
    }
    else if (key == 'a'){     //A key
        player->setX( player->getX() - 0.1 );
    }
    else if (key == 's'){     //S key
        player->setY( player->getY() - 0.1 );
    }
    else if (key == 'd'){     //D key
        player->setX( player->getX() + 0.1 );
    }
    else if (key == ' '){     //Spacebar key
        //projectile->setY( projectile->getY() + 0.2);
        player->fire( player->getX() + 0.05, player->getY() );
    }
    redraw();
}

void App::renderText(std::string text, float x, float y, void* font, float r, float g, float b) {
	int width = 640, height = 640;

    glColor3f(r, g, b);
    float offset = 0;
    for (int i = 0; i < text.length(); i++) {
        glRasterPos3f(x+offset, y, 1);
        glutBitmapCharacter(font, text[i]);
        int w = glutBitmapWidth(font, text[i]);
        offset += ((float)w / width)*2;
    }
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
    delete player;
    delete enemy;
}
