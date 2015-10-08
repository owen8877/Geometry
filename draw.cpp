#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <deque>
#include <time.h>
#include "element.h"

using namespace std;

extern int screenSize;
extern int screenWidth;
extern int screenHeight;

const int MAX = 100;
const double TINY = 0.01;

extern vector<point> v;
extern vector<line> l;
extern vector<int> vr, vg, vb;
extern vector<int> lr, lg, lb;
extern transform t;
extern deque<point> snake;
extern double snakeStep;
extern double boundRadius;
extern point food;

const double snakeWidth = snakeStep / 2.0;

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

void drawPoincareCircle(point center, double radius){
    glBegin(GL_LINE_LOOP);
    double D = (exp(radius) - 1) / (exp(radius) + 1);
    point centerToBeDrawn = point(center * ((D*D-1)/(center.abs2()*D*D-1)));
    double radiusToBeDrawn = D * (center.abs2() - 1) / (center.abs2()*D*D - 1);
    double theta;
    for (int i = 0;i < MAX;i++){
        theta = 2 * M_PI * i / MAX;
        glVertex2d(radiusToBeDrawn*cos(theta)+centerToBeDrawn.getX(), radiusToBeDrawn*sin(theta)+centerToBeDrawn.getY());
    }
    glEnd();
}

//The third argument indicates whether the circle is solid or not.
void drawPoincareCircle(point center, double radius, bool flagSolid){
    if (!flagSolid){
        drawPoincareCircle(center, radius);
        return;
    }
    glBegin(GL_POLYGON);
    double D = (exp(radius) - 1) / (exp(radius) + 1);
    point centerToBeDrawn = point(center * ((D*D-1)/(center.abs2()*D*D-1)));
    double radiusToBeDrawn = D * (center.abs2() - 1) / (center.abs2()*D*D - 1);
    double theta;
    for (int i = 0;i < MAX;i++){
        theta = 2 * M_PI * i / MAX;
        glVertex2d(radiusToBeDrawn*cos(theta)+centerToBeDrawn.getX(), radiusToBeDrawn*sin(theta)+centerToBeDrawn.getY());
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
    double size = 0.02*(1 - p.abs2()) + 0.003;
    glBegin(GL_POLYGON);
    glVertex2d(p.getX()-size, p.getY()-size);
    glVertex2d(p.getX()-size, p.getY()+size);
    glVertex2d(p.getX()+size, p.getY()+size);
    glVertex2d(p.getX()+size, p.getY()-size);
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
    //transform t(0.0);
 
    //Clearing buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Drawing objects
    glColor3f(1.0f, 1.0f, 1.0f);
    //drawCircle(point(0.0, 0.0), 1.0);

    //for (unsigned int i = 0; i < v.size(); ++i) drawPoint(t(v[i]));
    //for (unsigned int i = 0; i < l.size(); ++i) drawLine(t(l[i]));
    //drawPoincareCircle(t(v[0]), 1.0);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawPoincareCircle(t(point(0.0)), boundRadius);

    deque<point>::iterator it = snake.begin();
    glColor3f(0.3f, 1.0f, 0.3f);
    drawPoincareCircle(t(*it), snakeWidth * 1.5, true);
    glColor3f(0.0f, 0.7f, 0.0f);
    for (++it; it != snake.end(); ++it) drawPoincareCircle(t(*it), snakeWidth, true);

    glColor3f(1.0f, 0.5f, 1.0f);
    drawPoint(t(food));

    //Drawing text infomation
    char str[257];
    sprintf(str, "FPS: %d\n", getfps());
    glColor3f(1.0f, 1.0f, 0.5f);
    glRasterPos2d(-1, 1 - 24.0/screenSize);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char *)str);

    //Flush the drawing process
    glFlush();
}

