#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include "element.h"
#include "draw.h"

using namespace std;

complex x(0.03, 0);
complex y(0, 0.03);
complex rr = unit(0.05);
line l(0.7, 0.8);
point p(0.1, 0.3);

vector<point> v;
vector<int> r;
vector<int> g;
vector<int> b;

int kbstat[256] = {0};

void new_point_in_v(){
    double ran = (double) rand()/RAND_MAX*2 - 1;
    r.push_back(rand());
    g.push_back(rand());
    b.push_back(rand());
    v.push_back(point(ran, ((double)rand()/RAND_MAX*2-1)*sqrt(1-ran*ran)));
}

void new_point_in_v(point _p){
    r.push_back(rand());
    g.push_back(rand());
    b.push_back(rand());
    v.push_back(_p);
}

void mobius(complex c){
    for (unsigned int i = 0; i < v.size(); ++i){
        v[i] = v[i].mobius(c);
    }
    l = l.mobius(c);
    return;
}

void rotate(complex c){
    for (unsigned int i = 0; i < v.size(); ++i){
        v[i] = v[i]*c;
    }
    l = l*c;
    return;
}

int getfps(){
    static int count = 0, fps = 0;
    static time_t t1 = time(NULL);
    time_t t = time(NULL);
    if (t > t1) {
        fps = count/(t-t1);
        t1 = t;
        count = 0;
    }else ++count;
    return fps;
}

void init(){
    printf("--------Geometry test 0.0.0--------\n");
    printf("OpenGL Version %s\n\n", glGetString(GL_VERSION));

    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

    for (int i = 0;i < 10;i++){
        new_point_in_v();
        printf("%f %f %d\n", v[i].getX(), v[i].getY(), i);
    }
    new_point_in_v(p);
    new_point_in_v(unit(l.getStartArc()));
    //getPointByDistance(p, l, true, 1.0).print();
}

void update(int kbstat[]){
    if (kbstat['w']) mobius(y.negative());
    if (kbstat['s']) mobius(y);
    if (kbstat['a']) mobius(x);
    if (kbstat['d']) mobius(x.negative());
    if (kbstat['q']) rotate(rr);
    if (kbstat['e']) rotate(rr.conj());
}

void display(){
    //Clearing buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Drawing objects
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(point(0.0, 0.0), 1.0);

    glColor3f(0.0f, 1.0f, 1.0f);
    drawLine(l);
    drawPoint(getPointByDistance(p, l, true, 1.0), r[0], g[0], b[0]);

    for (unsigned int i = 0; i < v.size(); ++i){
        drawPoint(v[i], r[i], g[i], b[i]);
    }

    //Drawing text infomation
    char str[257];
    sprintf(str, "FPS: %d\n", getfps());
    glColor3f(1.0f, 1.0f, 0.5f);
    glRasterPos2d(-1, 1-0.06);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char *)str);

    //Flush the drawing process
    glFlush();
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
        case 'm' :
            double temp_1, temp_2;
            scanf("%lf %lf", &temp_1, &temp_2);
            mobius(complex(temp_1, temp_2));
            break;
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
    glutInitWindowSize(400, 400);
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
