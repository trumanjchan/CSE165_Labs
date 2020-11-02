#include "App.h"

int main(int argc, char** argv) {     //Responsible for running the App
    GlutApp* app = new App(argc, argv, 640, 640, "GLUT App");

    app->run();
}
