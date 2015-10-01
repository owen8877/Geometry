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
const double complex::getX()const{ return x; }
const double complex::getY()const{ return y; }

complex complex::addtion(complex _c){ return complex(x+_c.getX(), y+_c.getY()); }
complex complex::substraction(complex _c){ return complex(x-_c.getX(), y-_c.getY()); }
complex complex::production(complex _c){ return complex((x*_c.getX()-y*_c.getY()), (x*_c.getY()+y*_c.getX())); }
complex complex::division(complex _c){ return complex(((x*_c.getX()+y*_c.getY())/_c.sqr()), ((y*_c.getX()-x*_c.getY())/_c.sqr())); }
complex complex::reversion(){ return complex(x/sqr(), -y/sqr()); }
complex complex::negative(){ return complex(-x, -y); }
double complex::abs()const { return sqrt(x*x+y*y); }
double complex::sqr()const { return (x*x+y*y); }
complex complex::conj(){ return complex(x, -y); }
void complex::print(){ printf("%f %f\n", x, y); }

complex complex::operator +(complex const &c){ return complex(x+c.getX(), y+c.getY()); }
complex complex::operator -(complex const &c){ return complex(x-c.getX(), y-c.getY()); }
complex complex::operator *(complex const &c){ return complex((x*c.getX()-y*c.getY()), (x*c.getY()+y*c.getX())); }
complex complex::operator /(complex const &c){ return complex(((x*c.getX()+y*c.getY())/c.sqr()), ((y*c.getX()-x*c.getY())/c.sqr())); }
complex operator +(double a, complex const &b){ return complex(a+b.getX(), b.getY()); }
complex operator -(double a, complex const &b){ return complex(a-b.getX(), -b.getY()); }
complex operator *(double a, complex const &b){ return complex(a*b.getX(), a*b.getY()); }
complex operator /(double a, complex const &b){ return complex((a*b.getX()/b.sqr()), (-a*b.getY())/b.sqr()); }
complex operator +(complex const &a, double b){ return complex(a.getX()+b, a.getY()); }
complex operator -(complex const &a, double b){ return complex(a.getX()-b, a.getY()); }
complex operator *(complex const &a, double b){ return complex(a.getX()*b, a.getY()*b); }
complex operator /(complex const &a, double b){ return complex(a.getX()/b, a.getY()/b); }
