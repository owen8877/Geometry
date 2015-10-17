#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <GL/freeglut.h>
#ifdef _WIN32
#include <GL/glext.h>
#endif

#include "element.h"

using namespace std;

extern int screenSize;
extern int screenWidth;
extern int screenHeight;

const int MAX = 200;
const double TINY = 0.01;

extern vector<point> v;
extern vector<line> l;
extern vector<double> vr, vg, vb;
extern vector<double> lr, lg, lb;
extern vector<segment> s;
extern vector<double> sr, sg, sb;
extern transform t;

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

void glVertex2dp(point p){ glVertex2d(p.getX(), p.getY()); }

void drawCircle(point center, double radius){
    glBegin(GL_LINE_STRIP);
    double theta;
    for (int i = 0;i <= MAX;i++){
        theta = 2 * M_PI * i / MAX;
        glVertex2dp(radius*unit(theta)+center);
    }
    glEnd();
}

void drawArc(point center, double radius, double startarc, double endarc){
    int chord = (int)(MAX * radius * fabs(endarc - startarc) / 2) + 1;
    glBegin(GL_LINE_STRIP);
    double step = (endarc-startarc) / chord, theta = startarc;
    for (int i = 0; i <= chord; ++i){
        glVertex2dp(radius*unit(theta) + center);
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
    double middle = l.getCenter().arg() + M_PI;
    double deflection = atan(1/l.getRadius());
    double start = middle - deflection;
    double end = middle + deflection;
    drawArc(l.getCenter(), l.getRadius(), start, end);
}

void drawSegment(segment s){
    if (s.isDiameter()){
        glBegin(GL_LINE_STRIP);
        glVertex2d(s.getStart().getX(), s.getStart().getY());
        glVertex2d(s.getEnd().getX(), s.getEnd().getY());
        glEnd();
        return;
    }
    double middle = s.getCenter().arg() + M_PI;
    complex startdef = (s.getStart() - s.getCenter())*unit(-middle);
    complex enddef = (s.getEnd() - s.getCenter())*unit(-middle);
    drawArc(s.getCenter(), s.getRadius(), middle + startdef.arg(), middle + enddef.arg());
}

void drawPoint(point p){
    double size = 0.02*(1 - p.abs2());
    if (size * screenSize / 2 < 0.3) return;
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

void reshape(int width, int height){
    screenWidth = width;
    screenHeight = height;
    screenSize = (width < height ? width : height);
    glViewport (0, 0, width, height);
    glLoadIdentity ();
    glOrtho (-(GLfloat)width / screenSize, (GLfloat)width / screenSize,
            -(GLfloat)height / screenSize, (GLfloat)height / screenSize,
            -2.0f, 2.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void initDisplay(){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /*
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.5);
    */
    glEnable(GL_MULTISAMPLE);

    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void display(){
    //Clearing buffer
    //glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    glVertex2d(1.0f, 1.0f);
    glVertex2d(-1.0f, 1.0f);
    glVertex2d(-1.0f, -1.0f);
    glVertex2d(1.0f, -1.0f);
    glEnd();

    //Drawing objects
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(point(0.0, 0.0), 1.0);

    for (unsigned int i = 0; i < s.size(); ++i){
        glColor3d(sr[i], sg[i], sb[i]);
        drawSegment( t(s[i]) );
    }

    for (unsigned int i = 0; i < l.size(); ++i){
        glColor3d(lr[i], lg[i], lb[i]);
        drawLine( t(l[i]) );
    }

    for (unsigned int i = 0; i < v.size(); ++i){
        glColor3d(vr[i], vg[i], vb[i]);
        drawPoint( t(v[i]) );
    }

    //Drawing text infomation
    char str[257];
    sprintf(str, "FPS: %d\nEdges: %lu", getfps(), (unsigned long)s.size());
    glColor3f(1.0f, 1.0f, 0.5f);
    glRasterPos2d(-1, 1 - 24.0/screenSize);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char *)str);

    //Flush the drawing process
    glFlush();
}

