#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <lua.hpp>
#include "element.h"
#include "model.h"

using namespace std;

complex dx(0.03, 0);
complex dy(0, 0.03);
double rr = 0.05;

vector<point> v;
vector<line> l;
vector<segment> s;
vector<bool> sflag;
vector<double> sr, sg, sb;
vector<double> vr, vg, vb;
vector<double> lr, lg, lb;
transform t(0.0);
const size_t MAX_SEGS = 6000;
int head;

void new_point_in_v(){
    double ran = (double) rand()/RAND_MAX*2 - 1;
    vr.push_back((double)rand()/RAND_MAX);
    vg.push_back((double)rand()/RAND_MAX);
    vb.push_back((double)rand()/RAND_MAX);
    v.push_back(point(ran, ((double)rand()/RAND_MAX*2-1)*sqrt(1-ran*ran)));
}

void add_point(point _p){
    vr.push_back((double)rand()/RAND_MAX);
    vg.push_back((double)rand()/RAND_MAX);
    vb.push_back((double)rand()/RAND_MAX);
    v.push_back(_p);
}

void add_line(line _l){
    lr.push_back((double)rand()/RAND_MAX);
    lg.push_back((double)rand()/RAND_MAX);
    lb.push_back((double)rand()/RAND_MAX);
    l.push_back(_l);
}

void add_segment(segment _s){
    sr.push_back((double)rand()/RAND_MAX);
    sg.push_back((double)rand()/RAND_MAX);
    sb.push_back((double)rand()/RAND_MAX);
    s.push_back(_s);
}

void callLua(const char * luafile){
    int error = 0;

    // Initializing lua state
    lua_State *L = luaL_newstate();
    if (NULL == L) {
        printf("Error allocating memory for lua state.\n");
        return;
    }

    printf("Lua Version %.0lf\n", *lua_version(L));
    luaL_openlibs(L);

    // Loading lua script
    if ( (error = luaL_loadfile(L, luafile)) ){
        printf("Error loading file %s : ", luafile);
        switch (error){
            case LUA_ERRFILE:   printf("LUA_ERRFILE"); break;
            case LUA_ERRSYNTAX: printf("LUA_ERRSYNTAX"); break;
            case LUA_ERRMEM:    printf("LUA_ERRMEM"); break;
            case LUA_ERRGCMM:   printf("LUA_ERRGCMM"); break;
        }
        printf("\n");
        return;
    }

    // Running the script
    printf("\n");
    if ( (error = lua_pcall(L, 0, 0, 0)) ){
        printf("Error running script %s : ", luafile);
        switch (error){
            case LUA_ERRRUN:  printf("LUA_ERRRUN"); break;
            case LUA_ERRMEM:  printf("LUA_ERRMEM"); break;
            case LUA_ERRERR:  printf("LUA_ERRERR"); break;
            case LUA_ERRGCMM: printf("LUA_ERRGCMM"); break;
        }
        printf("\n");
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return;
    }

    // Closing lua state
    lua_close(L);
}

void initModel(){
    callLua("test.lua");

    double rad = sin(M_PI/42)/sqrt(( cos(2*M_PI/3)+cos(2*M_PI/7) )/2);
    for (int i = 0; i < 3; ++i){
        add_point(point(rad*unit(i*M_PI*2/3)));
    }
    for (int i = 0; i < 3; ++i){
        add_segment(segment(v[i], v[(i+1)%3]));
        sflag.push_back(true);
    }
    head = 0;
}

void updateModel(){
    point l, r, mid;
    bool flag = true;

    if (s.size() >= MAX_SEGS) return;

    while (!sflag[head]) ++head;
    r = (s[head]).getStart();
    l = (s[head]).getEnd();
    mid = rotateByPoint(r, l, M_PI*2/7);

    if (PoincareDistance(mid, s.back().getStart()) > 1e-6){
        add_segment(segment(r, mid));
        sflag.push_back(true);
    } else {
        sflag.back() = false;
        flag = false;
    }

    if (PoincareDistance(mid, s[++head].getEnd()) > 1e-6){
        add_segment(segment(mid, l));
        sflag.push_back(true);
    } else {
        ++head;
        flag = false;
    }

    if (flag) {
        add_point(mid);
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
        if (0 < v.size()) t = transform(0.0);
        kbstat['l'] = 0;
    }
    for (int i = 0; i < 100; ++i) updateModel();
}

double mousex = 0, mousey = 0;

void renewMouseStat(double x, double y, int button){
    static int button_old = 0;
    static double x_old = 0, y_old = 0;
    if (LEFT_MOUSE_BUTTON & button & button_old) {
        t = transform(-complex(x-x_old, y-y_old))*t;
    }
    button_old = button;
    x_old = x; y_old = y;
    mousex = x; mousey = y;
}
