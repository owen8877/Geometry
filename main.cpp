#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "element.h"
#include "draw.h"
#include <vector>

using namespace std;

const double MAX_LONG = 1073741824.0;
bool flag = false;
complex x(0.02, 0);
complex y(0, 0.02);
line l(1.0, 2.0);

vector<point> v;
vector<int> r;
vector<int> g;
vector<int> b;

void myinit(){
    //if (flag) return;
    //flag = true;
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle(point(0.0, 0.0), 1.0);
    for (int i = 0;i < 10;i++){
        double ran = rand()/MAX_LONG - 1;
        r.push_back(rand());
        g.push_back(rand());
        b.push_back(rand());
        v.push_back(point(ran, (rand()/MAX_LONG-1)*sqrt(1-ran*ran)));
        printf("%f %f %d\n", v[i].getX(), v[i].getY(), i);
        drawPoint(v[i], r[i], g[i], b[i]);
    }
}

void mobius(complex c){
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle(point(0.0, 0.0), 1.0);
    for (int i = 0;i < 10;i++){
        v[i] = v[i].mobius(c);
        v[i].print();
        drawPoint(v[i], r[i], g[i], b[i]);
    }
    l = l.mobius(c);
    drawLine(l);
    return;
}

void keyboardCallback(unsigned char key, int _x, int _y){
    switch (key) {
        case 'w' : mobius(y.negative()); break;
        case 's' : mobius(y); break;
        case 'a' : mobius(x); break;
        case 'd' : mobius(x.negative()); break;
        default : printf("Hey!\n");
    }
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Geometry");
    glutKeyboardFunc(&keyboardCallback);
    glutDisplayFunc(&myinit);
    glutMainLoop();
    return 0;
}
