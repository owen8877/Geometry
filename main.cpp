#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include "element.h"
#include "draw.h"
#include <vector>

using namespace std;

const double MAX_LONG = 1073741824.0;
bool flag = false;
complex x(0.01, 0);
complex y(0, 0.01);
complex rr = unit(0.01);
line l(1.25, 0.0);
point p(0.5, 0.0);

vector<point> v;
vector<int> r;
vector<int> g;
vector<int> b;

void new_point_in_v(){
    double ran = rand()/MAX_LONG - 1;
    r.push_back(rand());
    g.push_back(rand());
    b.push_back(rand());
    v.push_back(point(ran, (rand()/MAX_LONG-1)*sqrt(1-ran*ran)));
}

void new_point_in_v(point _p){
    r.push_back(rand());
    g.push_back(rand());
    b.push_back(rand());
    v.push_back(_p);
}

void init(){
    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
    for (int i = 0;i < 10;i++){
        new_point_in_v();
        printf("%f %f %d\n", v[i].getX(), v[i].getY(), i);
    }
    new_point_in_v(p);
    new_point_in_v(unit(l.getStartArc()));
    //getPointByDistance(p, l, true, 1.0).print();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(point(0.0, 0.0), 1.0);
    for (unsigned int i = 0; i < v.size(); ++i){
        drawPoint(v[i], r[i], g[i], b[i]);}
    glColor3f(1.0f, 1.0f, 0.0f);
    drawLine(l);
    drawPoint(getPointByDistance(p, l, true, 1.0), r[0], g[0], b[0]);
    glFlush();
}

void mobius(complex c){
    for (unsigned int i = 0;i < v.size();i++){
        v[i] = v[i].mobius(c);
        v[i].print();
    }
    l = l.mobius(c);
    p = p.mobius(c);
    return;
}

void rotate(complex c){
    for (unsigned int i = 0;i < v.size();i++){
        v[i] = v[i]*c;
        v[i].print();
    }
    l = l*c;
    p = p*c;
    return;
}

void keyboardCallback(unsigned char key, int _x, int _y){
    switch (key) {
        case 'w' : mobius(y.negative()); break;
        case 's' : mobius(y); break;
        case 'a' : mobius(x); break;
        case 'd' : mobius(x.negative()); break;
        case 'q' : rotate(rr); break;
        case 'e' : rotate(rr.conj()); break;
        case 'm' :
                double temp_1, temp_2;
                scanf("%lf %lf", &temp_1, &temp_2);
                mobius(complex(temp_1, temp_2));
                break;
        case '\x1B' : glutLeaveMainLoop(); break;
        default : printf("Hey!\n");
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]){
    //Window Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Geometry");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutKeyboardFunc(&keyboardCallback);
    glutDisplayFunc(&display);

    init();
    glutMainLoop();

    return 0;
}
