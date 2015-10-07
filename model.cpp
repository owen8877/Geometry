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

void new_point_in_v(){
    double ran = (double) rand()/RAND_MAX*2 - 1;
    vr.push_back(rand());
    vg.push_back(rand());
    vb.push_back(rand());
    v.push_back(point(ran, ((double)rand()/RAND_MAX*2-1)*sqrt(1-ran*ran)));
}

void new_point_in_v(point _p){
    vr.push_back(rand());
    vg.push_back(rand());
    vb.push_back(rand());
    v.push_back(_p);
}

void mobius(complex c){
    for (unsigned int i = 0; i < l.size(); ++i){
        l[i] = l[i].mobius(c);
    }
    for (unsigned int i = 0; i < v.size(); ++i){
        v[i] = v[i].mobius(c);
    }
    return;
}

void rotate(double phi){
    for (unsigned int i = 0; i < v.size(); ++i){
        v[i] = v[i]*unit(phi);
    }
    for (unsigned int i = 0; i < l.size(); ++i){
        l[i] = l[i].rotate(phi);
    }
    return;
}

void initModel(){
    for (int i = 0; i < 7; ++i){
        new_point_in_v(point(0.5*unit(i*M_PI*2/7)));
    }
    for (int i = 0; i < 7; ++i){
        lr.push_back(rand());
        lg.push_back(rand());
        lb.push_back(rand());
        l.push_back(line(v[i], v[(i+1)%7]));
        lr.push_back(rand());
        lg.push_back(rand());
        lb.push_back(rand());
        l.push_back(line(v[i], v[(i+2)%7]));
    }
}

void update(int kbstat[]){
    if (kbstat['w']) mobius(-dy);
    if (kbstat['s']) mobius(dy);
    if (kbstat['a']) mobius(dx);
    if (kbstat['d']) mobius(-dx);
    if (kbstat['q']) rotate(rr);
    if (kbstat['e']) rotate(-rr);
    if (kbstat['l']) {
        if (0 < v.size()) mobius(v[0]);
        kbstat['l'] = 0;
    }
}

void renewMouseStat(double x, double y, int button){
    static int button_old = 0;
    static double x_old = 0, y_old = 0;
    if (LEFT_MOUSE_BUTTON & button & button_old) {
        mobius(-complex(x-x_old, y-y_old));
    }
    button_old = button;
    x_old = x; y_old = y;
}
