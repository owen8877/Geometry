#include <GL/glut.h>
#include <math.h>
#include "element.h"

const int MAX = 100;
const double TINY = 0.02;
const double PAI = 3.1415926;

void drawCircle(point center, double radius){
    glBegin(GL_LINE_LOOP);
    double theta;
    for (int i = 0;i < MAX;i++){
        theta = 2 * PAI * i / MAX;
        glVertex2d(radius*cos(theta)+center.getX(), radius*sin(theta)+center.getY());
    }
    glEnd();
    glFlush();
}

void drawArc(point center, double radius, double startarc, double endarc){
    glBegin(GL_LINE_STRIP);
    double step = (endarc-startarc) / MAX;
    for (double theta = startarc;theta < endarc;theta+=step){
        glVertex2d(radius*cos(theta)+center.getX(), radius*sin(theta)+center.getY());
    }
    glEnd();
    glFlush();
}

void drawLine(line l){
    drawArc(l.getCenter(), l.getRadius(), l.getStartArc(), l.getEndArc());
}

void drawPoint(point p){
    glBegin(GL_POLYGON);
    glVertex2d(p.getX()-TINY, p.getY()-TINY);
    glVertex2d(p.getX()-TINY, p.getY()+TINY);
    glVertex2d(p.getX()+TINY, p.getY()+TINY);
    glVertex2d(p.getX()+TINY, p.getY()-TINY);
    glEnd();
    glFlush();
}

void drawPoint(point p, int r, int g, int b){
    glBegin(GL_POLYGON);
    glColor3i(r, g, b);
    glVertex2d(p.getX()-TINY, p.getY()-TINY);
    glVertex2d(p.getX()-TINY, p.getY()+TINY);
    glVertex2d(p.getX()+TINY, p.getY()+TINY);
    glVertex2d(p.getX()+TINY, p.getY()-TINY);
    glEnd();
    glFlush();
}
