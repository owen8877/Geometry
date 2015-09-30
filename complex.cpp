#include <math.h>
#include <stdio.h>
#include "element.h"

complex::complex(){
    x = 0.0;
    y = 0.0;
}

complex::complex(double _x, double _y){
    x = _x;
    y = _y;
}

void complex::setX(double _x){ x = _x; }
void complex::setY(double _y){ y = _y; }

double complex::getX(){ return x; }
double complex::getY(){ return y; }

complex complex::addtion(complex _c){
    return complex(x+_c.getX(), y+_c.getY());
}

complex complex::substraction(complex _c){
    return complex(x-_c.getX(), y-_c.getY());
}

complex complex::production(complex _c){
    return complex((x*_c.getX()-y*_c.getY()), (x*_c.getY()+y*_c.getX()));
}

complex complex::division(complex _c){
    double sqr =  _c.abs() * _c.abs();
    return complex(((x*_c.getX()+y*_c.getY())/sqr), ((y*_c.getX()-x*_c.getY())/sqr));
}

complex complex::reversion(){
    double sqr = x*x + y*y;
    return complex(x/sqr, -y/sqr);
}

complex complex::negative(){
    return complex(-x, -y);
}

double complex::abs(){ return sqrt(x*x+y*y); }
complex complex::conj(){ return complex(x, -y); }
void complex::print(){ printf("%f %f\n", x, y); }
