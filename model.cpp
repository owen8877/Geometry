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
transform t(0.0), t1(0.0);

deque<point> snake;
size_t snakeend;
point food;
double snakeStep = 0.2;
double boundRadius = 2;
ideal northDir(1.0, 0.0);
int snakeDir = 0;
int snakeInc;
int score = 0;

int stepInterval = 5;

const ideal dirs[4] = {ideal(0.0, 1.0), ideal(-1.0, 0.0), ideal(0.0, -1.0), ideal(1.0, 0.0)};
point steps[8];

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
    for (int i = 4; i < 8; ++i) steps[i] = getPointByDistance(point(0.0), dirs[i-4], snakeStep/stepInterval);
    snake.clear();
    snake.push_back(point(0.0, 0.0));
    snakeend = 0;
    t = t1 = transform(0.0);
    northDir = ideal(1.0, 0.0);
    snakeDir = 0;
    snakeInc = 10;
    score = 0;
    while(PoincareDistance(complex(0.0), (food = randPoint())) >= boundRadius);
}

bool checkCollision(){
    if (PoincareDistance(complex(0.0), *snake.begin()) >= boundRadius){
        printf("You reached the boundary.\n");
        return true;
    }
    for (deque<point>::reverse_iterator it = snake.rbegin() + snakeend; it != snake.rend()-1; ++it){
        if (PoincareDistance(*snake.begin(), *it) >= snakeStep*.99) continue;
        printf("You ate yourself.\n");
        return true;
    }
    return false;
}

bool checkFood(){
    return (PoincareDistance(food, *snake.begin()) <= snakeStep);
}

point randFoodPoint(){
    static double C = cosh(boundRadius) - 1;
    return point(tanh(acosh(C*rand()/RAND_MAX + 1)/2) , 0.0).rotate(2 * M_PI * rand()/RAND_MAX);
}

void update(int kbstat[]){
    static int frameCount = stepInterval;
    static int snakeDirNext = 0;
    if (kbstat['w']) snakeDirNext = 0; 
    if (kbstat['a']) snakeDirNext = 1; 
    if (kbstat['s']) snakeDirNext = 2; 
    if (kbstat['d']) snakeDirNext = 3; 
    if (stepInterval == frameCount){
        
        if ((snakeDirNext + snakeDir)%2) snakeDir = snakeDirNext;
        snake.push_front(t.inversion()(steps[snakeDir]));
        t1 = transform(steps[snakeDir]) * t1;
        t = transform(steps[snakeDir+4]) * t;

        if (snakeInc > 0) snakeInc--;
        else snakeend++;

        if (checkCollision()){
            printf("You lose! Score: %d\n\n", score);
            fflush(stdout);
            initModel();
            frameCount = stepInterval;
            snakeDir = 0;
            snakeDirNext = 0;
            return;
        }
        
        if (checkFood()){
            snakeInc += 2;
            score++;
            while(PoincareDistance(complex(0.0), (food = randFoodPoint())) >= boundRadius);
        }
        frameCount = 0;
    } else t = transform(steps[snakeDir+4]) * t;
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
