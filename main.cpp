#include <GL/freeglut.h>
#include <stdio.h>
#include "element.h"
#include "draw.h"
#include "model.h"

using namespace std;

int kbstat[256] = {0};
const int _SCREEN_SIZE_ = 600;

void init(){
    printf("--------Geometry test 0.0.0--------\n");
    printf("OpenGL Version %s\n\n", glGetString(GL_VERSION));
    initDisplay();
    initModel();
}

void mouse(int _mousex, int _mousey){
    _mousex -= _SCREEN_SIZE_ / 2;
    _mousey -= _SCREEN_SIZE_ / 2;
    _mousey = -_mousey;
    double sq = sqrt(_mousex*_mousex+_mousey*_mousey);
    complex _magic(_mousex/sq, _mousey/sq);
    //magic.print();
    //_magic.print();
    point d = getPointByDistance(complex(0.0, 0.0), line(_magic, complex(0.0, 0.0)), sq/200.0);
    //d.print();
    _magic = complex(d.getX(), d.getY());
    _magic = -_magic;
    mobius(-magic);
    mobius(_magic);
    //_magic.print();
    magic = _magic;
}

void timerCallback(int index){
    switch (index) {
        case 0:
            glutTimerFunc(33, &timerCallback, 0);
            update(kbstat);
            glutPostRedisplay();
            break;
    }
}

void keyboardCallback(unsigned char key, int _x, int _y){
    switch (key) {
        case '\x0D' :
        case '\x1B' :
            glutLeaveMainLoop();
            break;
    }
    kbstat[key] = 1;
}

void keyboardUpCallback(unsigned char key, int x, int y){
    kbstat[key] = 0;
}

int main(int argc, char *argv[]){
    //Window Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(_SCREEN_SIZE_, _SCREEN_SIZE_);
    glutCreateWindow("Geometry");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    //Callback function registry
    glutKeyboardFunc(&keyboardCallback);
    glutKeyboardUpFunc(&keyboardUpCallback);
    glutDisplayFunc(&display);
    glutPassiveMotionFunc(&mouse);
    glutTimerFunc(0, &timerCallback, 0);
    //Initialization
    init();

    //Main loop
    glutMainLoop();

    return 0;
}
