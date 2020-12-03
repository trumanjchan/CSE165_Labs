#include <iostream>
#include "App.h"
#include <deque>

std::deque<Rect*> projectile;
static App* singleton;

bool moveUp;
bool moveLeft;
bool moveDown;
bool moveRight;
bool princessVisible;
bool mob1Visible;
bool mob2Visible;
bool mob3Visible;
bool gunVisible;
bool holdWeaponOut;
bool ammoVisible;
bool canNowShoot;

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

void mobTimer1(int id){
    singleton->mob1->mobAdvance();
    singleton->redraw();
    if (singleton->mob1->isDone()){
        singleton->mob1->reset();
    }
    glutTimerFunc(100, mobTimer1, id);
}
void mobTimer2(int id){
    singleton->mob2->mobAdvance();
    singleton->redraw();
    if (singleton->mob2->isDone()){
        singleton->mob2->reset();
    }
    glutTimerFunc(300, mobTimer2, id);
}
void mobTimer3(int id){
    singleton->mob3->mobAdvance();
    singleton->redraw();
    if (singleton->mob3->isDone()){
        singleton->mob3->reset();
    }
    glutTimerFunc(250, mobTimer3, id);
}

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){

    // Pushing different kinds of Shape in the collection
    bg = new TexRect("park_bg.png", -1.7, 1, 3.5, 2);                              // filename, x, y, w, h
    weapon = new TexRect("ak.png", -1.3, 0.05, 0.25, 0.125);
    ammunition = new TexRect("bullet.png", -0.8, -0.2, 0.095, 0.03);
    character = new Sprite("Character_Main.png", 3,6,  -1.65,-0.3,  0.3,0.3);
    holdWeapon = new TexRect("ak.png", -3, 0, 0.25, 0.125);
    princess = new Sprite("Character_Princess.png", 3,6,  1.4,-0.4,  0.3,0.3);     // filename, rows,cols, x,y, w,h
    mob1 = new Sprite("Slime_Green.png", 6,5,  0.7,-1.3,  0.5,0.5);
    mob2 = new Sprite("Slime_Green.png", 6,5,  0.2,1.3,  0.5,0.5);
    mob3 = new Sprite("Slime_Green.png", 6,5,  -0.3,-1.3,  0.5,0.5);

    mob1Visible = true;
    mob2Visible = true;
    mob3Visible = true;
    princessVisible = true;
    gunVisible = true;
    holdWeaponOut = false;     //Hold out gun only briefly when user clicks
    ammoVisible = true;
    canNowShoot = false;

    singleton = this;
    idleTimer(1);      // idle moving princess
    playerTimer(2);    // moving character

    mobTimer1(3);      //idle moving slimes
    mobTimer2(4);
    mobTimer3(5);
} 

void App::idle(){
    if (holdWeaponOut) {
        holdWeapon->setX( character->getX() + 0.09 );
        holdWeapon->setY( character->getY() - 0.165 );
    }

    if (mob1->getY() < 1.3) {
        mob1->setY( mob1->getY() + 0.0000072 );  //go up if your Y value is less than 1.3
    }
    else {
        if (mob1->getY() > 0) {
            mob1->setY( mob1->getY() - 3 );     //once at the top, teleport to bottom
        }
    }

    if (mob2->getY() > -1.3) {
        mob2->setY( mob2->getY() - 0.000005 );     //go down  if your Y value is more than -1.3
    }
    else {
        if (mob2->getY() < -1) {
            mob2->setY( mob2->getY() + 3 );        //once at the bottom, teleport to top
        }
    }

    if (mob3->getY() < 1.3) {
        mob3->setY( mob3->getY() + 0.000006 );
    }
    else {
        if (mob3->getY() > 0) {
            mob3->setY( mob3->getY() - 3 );
        }
    }

    for (int i = 0; i < projectile.size(); i++) {
        projectile[i]->setX( projectile[i]->getX() + 0.00003 );     //Speed: continuously set projectile[i]'s x-coord to (x-coord += 0.00005)
    }

    if (character->getY() > (weapon->getY() + 0.1) ) {     //SET HORIZON BORDER ------------------------------------------------------------------
        character->setY( character->getY() - 0.01);
    }
    if (character->getY() > (weapon->getY() - 0.2)) {     // Can't walk to the right unless on the road (can walk to get gun and ammo)
        if (character->getX() > (weapon->getX() + 0.5) ) {
            character->setX( character->getX() - 0.01);
            character->setY( character->getY() - 0.01); 
        }
    }
    if (character->getX() < (weapon->getX() - 0.5)) {     // Can't walk out of the map (left)
        character->setX( character->getX() + 0.01);
    }
    if (character->getX() > (weapon->getX() + 2.8)) {       // Can't walk out of the map (right)
        character->setX( character->getX() - 0.01);
    }
    if (character->getY() < (weapon->getY() - 0.8)) {     // Can't walk out of the map (bottom)
        character->setY( character->getY() + 0.01);
    }
}

void App::draw() const{
    bg->drawBG();
    character->draw();
    holdWeapon->draw();

    if (mob1Visible) {
        mob1->draw();
    }
    if (mob2Visible) {
        mob2->draw();
    }
    if (mob3Visible) {
        mob3->draw();
    }
    if (princessVisible) {
        princess->draw();
    }

    if (gunVisible) {
        weapon->draw();
    }
    if ( character->contains(weapon->getX(), weapon->getY()) ) {
        gunVisible = false;
    }

    if (ammoVisible) {
        ammunition->draw();
    }
    if ( character->contains(ammunition->getX(), ammunition->getY()) ) {
        ammoVisible = false;
    }

    if (gunVisible == false && ammoVisible == false) {
        canNowShoot = true;
    }

    for (int i = 0; i < projectile.size(); i++) {
        projectile[i]->draw();
        if ( mob1->contains(projectile[i]->getX(), projectile[i]->getY()) ) {     //Detects whether bullet touched mob or princess. If yes, they "die"
			mob1Visible = false;
		}
        if ( mob2->contains(projectile[i]->getX(), projectile[i]->getY()) ) {
			mob2Visible = false;
		}
        if ( mob3->contains(projectile[i]->getX(), projectile[i]->getY()) ) {
			mob3Visible = false;
		}
        if ( princess->contains(projectile[i]->getX(), projectile[i]->getY()) ) {
			princessVisible = false;
		}
    }
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
void App::leftMouseDown(float x, float y){     //if left mouse down, FIRE!
    if (canNowShoot) {
        holdWeaponOut = true;
        character->fire( character->getX() + 0.3, character->getY() - 0.2 );     //Start projectiles in front of the weapon
    }
}

App::~App(){
    delete princess;
    delete character;
    delete monster;
    delete mob1;
    delete mob2;
    delete mob3;
    delete weapon;
    delete ammunition;
    delete bg;

    for (int i = 0; i < projectile.size(); i++) {
        delete projectile[i];
    }
    std::cout << "Exiting..." << std::endl;
}
