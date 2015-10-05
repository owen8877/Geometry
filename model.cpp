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

complex x(0.03, 0);
complex y(0, 0.03);
complex rr = unit(0.05);
line l(1.0, 1.0);
point p(0.2928, 0.2928);
complex magic(0.0);

vector<point> v;
vector<int> r;
vector<int> g;
vector<int> b;

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
    p = p.mobius(c);
    return;
}

void rotate(complex c){
    for (unsigned int i = 0; i < v.size(); ++i){
        v[i] = v[i]*c;
    }
    l = l.rotate(c);
    p = p*c;
    return;
}

void initModel(){
    for (int i = 0;i < 1;i++){
        new_point_in_v();
        printf("%f %f %d\n", v[i].getX(), v[i].getY(), i);
    }
    new_point_in_v(p);
    new_point_in_v(l.getLeft());
    new_point_in_v(l.getRight());
    //getPointByDistance(p, l, true, 1.0).print();
}

void update(int kbstat[]){
    if (kbstat['w']) mobius(-y);
    if (kbstat['s']) mobius(y);
    if (kbstat['a']) mobius(x);
    if (kbstat['d']) mobius(-x);
    if (kbstat['q']) rotate(rr);
    if (kbstat['e']) rotate(rr.conj());
    if (kbstat['m']) {
        double temp_1, temp_2;
        scanf("%lf %lf", &temp_1, &temp_2);
        mobius(complex(temp_1, temp_2));
        kbstat['m'] = 0;
    }
    if (kbstat['l']) {
        mobius(p);
        kbstat['l'] = 0;
    }
}

void mouse(int mousex, int mousey){
    mousex -= screenSize / 2;
    mousey -= screenSize / 2;
    mousey = -mousey;
    double sq = sqrt(mousex*mousex + mousey*mousey);
    complex _magic(mousex/sq, mousey/sq);
    //magic.print();
    //_magic.print();
    point d = getPointByDistance(complex(0.0, 0.0), line(_magic, complex(0.0, 0.0)), sq/200.0);
    //d.print();
    _magic = complex(d.getX(), d.getY());
    _magic = -_magic;
    mobius(-magic);
    mobius(_magic);
    //_magic.print();
    magic = _magic;
}

