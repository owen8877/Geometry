#include <math.h>
#include <stdio.h>
#include "element.h"

complex::complex():x(0.0), y(0.0){}
complex::complex(double _x, double _y):x(_x), y(_y){}
complex::complex(double _x):x(_x), y(0.0){}
complex::complex(int _x):x(_x), y(0.0){}

void complex::set(double _x, double _y){ x = _x; y = _y; }
void complex::setX(double _x){ x = _x; }
void complex::setY(double _y){ y = _y; }
double complex::getX()const{ return x; }
double complex::getY()const{ return y; }

complex complex::addtion(complex c){ return complex(x + c.x, y + c.y); }
complex complex::substraction(complex c){ return complex(x - c.x, y - c.y); }
complex complex::production(complex c){ return complex((x*c.x - y*c.y), (x*c.y + y*c.x)); }
complex complex::division(complex c){ double sqr = c.abs2(); return complex(((x*c.x + y*c.y)/sqr), ((y*c.x - x*c.y)/sqr)); }
complex complex::reversion(){ double sqr = x*x + y*y; return complex(x/sqr, -y/sqr); }
complex complex::negative(){ return complex(-x, -y); }
double complex::abs()const{ return sqrt(x*x + y*y); }
double complex::abs2()const{ return x*x + y*y; }
complex complex::conj(){ return complex(x, -y); }
void complex::print(){ printf("(%f, %f)\n", x, y); }

complex complex::operator -(){ return complex(-x, -y); }

complex complex::operator +(const complex &c){ return complex(x + c.x, y + c.y); }
complex complex::operator -(const complex &c){ return complex(x - c.x, y - c.y); }
complex complex::operator *(const complex &c){ return complex((x*c.x - y*c.y), (x*c.y + y*c.x)); }
complex complex::operator /(const complex &c){ double sqr = c.abs2(); return complex(((x*c.x + y*c.y)/sqr), ((y*c.x - x*c.y)/sqr)); }
complex operator +(double a, const complex &b){ return complex(a + b.x, b.y); }
complex operator -(double a, const complex &b){ return complex(a - b.x, -b.y); }
complex operator *(double a, const complex &b){ return complex(a*b.x, a*b.y); }
complex operator /(double a, const complex &b){ double sqr = b.abs2(); return complex((a*b.x/sqr), (-a*b.y)/sqr); }
//complex operator +(complex const &a, double b){ return complex(a.x + b, a.y); }
//complex operator -(complex const &a, double b){ return complex(a.x - b, a.y); }
//complex operator *(complex const &a, double b){ return complex(a.x*b, a.y*b); }
//complex operator /(complex const &a, double b){ return complex(a.x/b, a.y/b); }
