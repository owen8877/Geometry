#include <cstdio>
#include <GL/freeglut.h>

#include "element.h"
#include "draw.h"
#include "model.h"

using namespace std;

int kbstat[256] = {0};
int mouseButton = 0;
int screenSize = 600;
int screenWidth = 600;
int screenHeight = 600;

// Initialization
void init(){
    printf("--------Geometry test 0.0.0--------\n");
    printf("OpenGL Version %s\n", glGetString(GL_VERSION));
    initDisplay();
    initModel();
    fflush(stdout);
}

// Timer Callback
void timerCallback(int index){
    switch (index) {
        case 0:
            glutTimerFunc(33, &timerCallback, 0);
            update(kbstat);
            glutPostRedisplay();
            break;
    }
}

// Keyboard Callback
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

// Mouse Callback
void mouseKey(int button, int state, int x, int y){
    if (GLUT_DOWN == state) switch (button) {
        case GLUT_LEFT_BUTTON:
            mouseButton |= LEFT_MOUSE_BUTTON;
            break;
        case GLUT_MIDDLE_BUTTON:
            mouseButton |= MIDDLE_MOUSE_BUTTON;
            break;
        case GLUT_RIGHT_BUTTON:
            mouseButton |= RIGHT_MOUSE_BUTTON;
            break;
    }
    else switch (button) {
        case GLUT_LEFT_BUTTON:
            mouseButton &= ~LEFT_MOUSE_BUTTON;
            break;
        case GLUT_MIDDLE_BUTTON:
            mouseButton &= ~MIDDLE_MOUSE_BUTTON;
            break;
        case GLUT_RIGHT_BUTTON:
            mouseButton &= ~RIGHT_MOUSE_BUTTON;
            break;
    }
    renewMouseStat((double) (x - screenWidth/2.0)/screenSize,
                (double) (screenHeight/2.0 - y)/screenSize,
                mouseButton);
}

void mouseMotion(int x, int y){
    renewMouseStat((double) (x - screenWidth/2.0)/screenSize,
                (double) (screenHeight/2.0 - y)/screenSize,
                mouseButton);
}

int main(int argc, char *argv[]){
    //Window Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_MULTISAMPLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Geometry");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    //Callback function registry
    glutDisplayFunc(&display);
    glutReshapeFunc(&reshape);

    glutKeyboardFunc(&keyboardCallback);
    glutKeyboardUpFunc(&keyboardUpCallback);

    glutMouseFunc(&mouseKey);
    glutMotionFunc(&mouseMotion);
    glutPassiveMotionFunc(&mouseMotion);

    glutTimerFunc(0, &timerCallback, 0);

    //Initialization
    init();

    //Main loop
    glutMainLoop();

    return 0;
}
