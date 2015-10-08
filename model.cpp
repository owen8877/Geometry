#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "element.h"
#include "model.h"

using namespace std;

extern int screenSize;
extern int screenWidth;
extern int screenHeight;

complex dx(0.03, 0);
complex dy(0, 0.03);
double rr = 0.05;

vector<point> v;
vector<line> l;
vector<int> vr, vg, vb;
vector<int> lr, lg, lb;
transform t(0.0);

void new_point_in_v(){
    double ran = (double) rand()/RAND_MAX*2 - 1;
    vr.push_back(rand());
    vg.push_back(rand());
    vb.push_back(rand());
    v.push_back(point(ran, ((double)rand()/RAND_MAX*2-1)*sqrt(1-ran*ran)));
}

void add_point(point _p){
    vr.push_back(rand());
    vg.push_back(rand());
    vb.push_back(rand());
    v.push_back(_p);
}

void add_line(line _l){
    lr.push_back(rand());
    lg.push_back(rand());
    lb.push_back(rand());
    l.push_back(_l);
}

void initModel(){
    double a = sin(M_PI/42)/sqrt(( cos(2*M_PI/3)+cos(2*M_PI/7) )/2);
    for (int i = 0; i < 3; ++i){
        add_point(point(a*unit(i*M_PI*2/3)));
    }
    for (int i = 2; i < 7; ++i){
        add_point(rotateByPoint(v[i], v[0], 2*M_PI/7));
    }
    for (int i = 0; i < 7; ++i){
        add_line(line(v[0], v[i+1]));
        add_line(line(v[i+1], v[(i+1)%7+1]));
    }
}

void update(int kbstat[]){
    if (kbstat['w']) t = transform(-dy) * t;
    if (kbstat['s']) t = transform(dy) * t;
    if (kbstat['a']) t = transform(dx) * t;
    if (kbstat['d']) t = transform(-dx) * t;
    if (kbstat['q']) t = transform(rr) * t;
    if (kbstat['e']) t = transform(-rr) * t;
    if (kbstat['l']) {
        if (0 < v.size()) t = transform(v[0]);
        kbstat['l'] = 0;
    }
}

void renewMouseStat(double x, double y, int button){
    static int button_old = 0;
    static double x_old = 0, y_old = 0;
    if (LEFT_MOUSE_BUTTON & button & button_old) {
        t = transform(-complex(x-x_old, y-y_old))*t;
    }
    button_old = button;
    x_old = x; y_old = y;
}
