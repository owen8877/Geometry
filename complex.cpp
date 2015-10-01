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

complex complex::addtion(complex _c){ return complex(x + _c.x, y + _c.y); }
complex complex::substraction(complex _c){ return complex(x - _c.x, y - _c.y); }
complex complex::production(complex _c){ return complex((x*_c.x - y*_c.y), (x*_c.y + y*_c.x)); }
complex complex::division(complex _c){ double sqr = _c.abs2(); return complex(((x*_c.x + y*_c.y)/sqr), ((y*_c.x - x*_c.y)/sqr)); }
complex complex::reversion(){ double sqr = x*x + y*y; return complex(x/sqr, -y/sqr); }
complex complex::negative(){ return complex(-x, -y); }
double complex::abs()const{ return sqrt(x*x + y*y); }
double complex::abs2()const{ return x*x + y*y; }
complex complex::conj(){ return complex(x, -y); }
void complex::print(){ printf("%f %f\n", x, y); }

complex complex::operator +(complex const &c){ return complex(x + c.x, y + c.y); }
complex complex::operator -(complex const &c){ return complex(x - c.x, y - c.y); }
complex complex::operator *(complex const &c){ return complex((x*c.x - y*c.y), (x*c.y + y*c.x)); }
complex complex::operator /(complex const &c){ double sqr = c.abs2(); return complex(((x*c.x + y*c.y)/sqr), ((y*c.x - x*c.y)/sqr)); }
complex operator +(double a, complex const &b){ return complex(a + b.x, b.y); }
complex operator -(double a, complex const &b){ return complex(a - b.x, -b.y); }
complex operator *(double a, complex const &b){ return complex(a*b.x, a*b.y); }
complex operator /(double a, complex const &b){ double sqr = b.abs2(); return complex((a*b.x/sqr), (-a*b.y)/sqr); }
complex operator +(complex const &a, double b){ return complex(a.x + b, a.y); }
complex operator -(complex const &a, double b){ return complex(a.x - b, a.y); }
complex operator *(complex const &a, double b){ return complex(a.x*b, a.y*b); }
complex operator /(complex const &a, double b){ return complex(a.x/b, a.y/b); }
