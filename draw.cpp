#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <time.h>
#include "element.h"

using namespace std;

extern int screenSize;
extern int screenWidth;
extern int screenHeight;

const int MAX = 100;
const double TINY = 0.01;

extern line l;
extern point p;
extern vector<point> v;
extern vector<int> r;
extern vector<int> g;
extern vector<int> b;

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

void drawCircle(point center, double radius){
    glBegin(GL_LINE_LOOP);
    double theta;
    for (int i = 0;i < MAX;i++){
        theta = 2 * M_PI * i / MAX;
        glVertex2d(radius*cos(theta)+center.getX(), radius*sin(theta)+center.getY());
    }
    glEnd();
}

void drawArc(point center, double radius, double startarc, double endarc){
    glBegin(GL_LINE_STRIP);
    double step = (endarc-startarc) / MAX, theta = startarc;
    for (int i = 0; i <= MAX; ++i){
        glVertex2d(radius*cos(theta) + center.getX(), radius*sin(theta) + center.getY());
        theta += step;
    }
    glEnd();
}

void drawLine(line l){
    if (l.isDiameter()){
        glBegin(GL_LINE_STRIP);
        glVertex2d(l.getLeft().getX(), l.getLeft().getY());
        glVertex2d(l.getRight().getX(), l.getRight().getY());
        glEnd();
        return;
    }
    double middle = atan2(l.getCenter().getY(), l.getCenter().getX()) + M_PI;
    double deflection = atan(1/l.getRadius());
    double start = middle - deflection;
    double end = middle + deflection;
    drawArc(l.getCenter(), l.getRadius(), start, end);
}

void drawPoint(point p){
    glBegin(GL_POLYGON);
    glVertex2d(p.getX()-TINY, p.getY()-TINY);
    glVertex2d(p.getX()-TINY, p.getY()+TINY);
    glVertex2d(p.getX()+TINY, p.getY()+TINY);
    glVertex2d(p.getX()+TINY, p.getY()-TINY);
    glEnd();
}

void drawPoint(point p, double size){
    glBegin(GL_POLYGON);
    glVertex2d(p.getX()-size, p.getY()-size);
    glVertex2d(p.getX()-size, p.getY()+size);
    glVertex2d(p.getX()+size, p.getY()+size);
    glVertex2d(p.getX()+size, p.getY()-size);
    glEnd();
}

void drawPoint(point p, int r, int g, int b){
    glBegin(GL_POLYGON);
    glColor3i(r, g, b);
    glVertex2d(p.getX()-TINY, p.getY()-TINY);
    glVertex2d(p.getX()-TINY, p.getY()+TINY);
    glVertex2d(p.getX()+TINY, p.getY()+TINY);
    glVertex2d(p.getX()+TINY, p.getY()-TINY);
    glEnd();
}

void reshape(int width, int height){
    screenWidth = width;
    screenHeight = height;
    screenSize = (width < height ? width : height);
    glViewport (0, 0, width, height);
    glLoadIdentity ();
    glOrtho (-(GLfloat)width / screenSize, (GLfloat)width / screenSize,
            -(GLfloat)height / screenSize, (GLfloat)height / screenSize,
            -2.0f, 2.0f);
}

void initDisplay(){
    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
}

void display(){
    //Clearing buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Drawing objects
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(point(0.0, 0.0), 1.0);

    glColor3f(0.0f, 1.0f, 1.0f);
    drawLine(l);
    drawPoint(p, 0.02*(1 - p.abs2()) + 0.003 );
    point so_magic = getPointByDistance(p, l.getRight(), l, 1.0);
    glColor3i(r[0], g[0], b[0]);
    drawPoint(so_magic, 0.02*(1 - so_magic.abs2()) + 0.003 );
    drawLine(getLineByAngle(p, so_magic, v[0], 0.7));

    for (unsigned int i = 0; i < v.size(); ++i){
        glColor3i(r[i], g[i], b[i]);
        drawPoint(v[i], 0.02*(1 - v[i].abs2()) + 0.003 );
    }

    //Drawing text infomation
    char str[257];
    sprintf(str, "FPS: %d\n", getfps());
    glColor3f(1.0f, 1.0f, 0.5f);
    glRasterPos2d(-1, 1-0.03);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char *)str);

    //Flush the drawing process
    glFlush();
}

