#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <deque>
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

deque<point> snake;
point food;
double snakeStep = 0.2;
double boundRadius = 3;
ideal northDir(1.0, 0.0);
int snakeDir = 0;
int snakeInc;
int score = 0;

const ideal dirs[4] = {ideal(0.0, 1.0), ideal(-1.0, 0.0), ideal(0.0, -1.0), ideal(1.0, 0.0)};
point steps[4];

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
    for (int i = 0; i < 4; ++i) steps[i] = getPointByDistance(point(0.0), dirs[i], snakeStep);
    snake.clear();
    snake.push_back(point(0.0, 0.0));
    t = transform(0.0);
    northDir = ideal(1.0, 0.0);
    snakeDir = 0;
    snakeInc = 10;
    score = 0;
    while(PoincareDistance(complex(0.0), (food = randPoint())) >= boundRadius);
}

bool checkCollision(){
    if (PoincareDistance(complex(0.0), *snake.begin()) >= boundRadius){
        printf("You reached the boundary. You lose!!!\n");
        return true;
    }
    for (deque<point>::iterator it = ++snake.begin(); it != snake.end(); ++it){
        if (PoincareDistance(*snake.begin(), *it) >= snakeStep*.99) continue;
        printf("You ate yourself. You lose!!!\n");
        return true;
    }
    return false;
}

bool checkFood(){
    return (PoincareDistance(food, *snake.begin()) <= snakeStep*1.5);
}


void update(int kbstat[]){
    static int stepInterval = 5 ,frameCount = 1;
    static int snakeDirNext = 0;
    if (kbstat['w']) snakeDirNext = 0; 
    if (kbstat['a']) snakeDirNext = 1; 
    if (kbstat['s']) snakeDirNext = 2; 
    if (kbstat['d']) snakeDirNext = 3; 
    if (stepInterval == frameCount){
        
        if ((snakeDirNext + snakeDir)%2) snakeDir = snakeDirNext;
        snake.push_front(t.inversion()(steps[snakeDir]));
        t = transform(steps[snakeDir]) * t;

        if (snakeInc > 0) snakeInc--;
        else snake.pop_back();

        if (checkCollision()){
            initModel();
            frameCount = 0;
            snakeDirNext = 0;
        }
        
        if (checkFood()){
            snakeInc += 2;
            score++;
            while(PoincareDistance(complex(0.0), (food = randPoint())) >= boundRadius);
        }
        frameCount = 0;
    }
    ++frameCount;
}

void renewMouseStat(double x, double y, int button){
    /*
    static int button_old = 0;
    static double x_old = 0, y_old = 0;
    if (LEFT_MOUSE_BUTTON & button & button_old) {
        t = transform(-complex(x-x_old, y-y_old))*t;
    }
    button_old = button;
    x_old = x; y_old = y;
    */
}
