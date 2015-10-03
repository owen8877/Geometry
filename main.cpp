#include <GL/freeglut.h>
#include <stdio.h>
#include "element.h"
#include "draw.h"
#include "model.h"

using namespace std;

int kbstat[256] = {0};

void init(){
    printf("--------Geometry test 0.0.0--------\n");
    printf("OpenGL Version %s\n\n", glGetString(GL_VERSION));
    initDisplay();
    initModel();
}

void timerCallback(int index){
    switch (index) {
        case 0:
            glutTimerFunc(32, &timerCallback, 0);
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
    glutInitWindowSize(600, 600);
    glutCreateWindow("Geometry");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    //Callback function registry
    glutKeyboardFunc(&keyboardCallback);
    glutKeyboardUpFunc(&keyboardUpCallback);
    glutDisplayFunc(&display);
    glutTimerFunc(0, &timerCallback, 0);
    //Initialization
    init();

    //Main loop
    glutMainLoop();

    return 0;
}
