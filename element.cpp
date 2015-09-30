#include <math.h>
#include <stdio.h>
#include "element.h"

const double PAI = 3.1415926;

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


point::point(){
    x = 0;
    y = 0;
}

point::point(double _x, double _y){
    x = _x;
    y = _y;
}

point::point(complex c){
    x = c.getX();
    y = c.getY();
}

point point::mobius(complex c){
    return point(substraction(c).division(complex(1,0).substraction(production(c.conj()))));
}

line::line(double _x, double _y){
    x = _x;
    y = _y;
}

line::line(complex c){
    x = c.getX();
    y = c.getY();
}

point line::getCenter(){ return point(x, y); }

double line::getRadius(){ return sqrt(x*x+y*y-1); }
double line::getStartArc(){
    double middle = atan(y/x);
    double deflection = asin(1/sqrt(x*x+y*y));
    if (x >= 0) return (middle - deflection + ((y > 0) ? -1 : 1) * PAI);
    return (middle - deflection);
}
double line::getEndArc(){
    double middle = atan(y/x);
    double deflection = asin(1/sqrt(x*x+y*y));
    if (x >= 0) return (middle + deflection + ((y > 0) ? -1 : 1) * PAI);
    return (middle + deflection);
}

line line::mobius(complex c){
    return line
            (
                substraction
                (
                    c.production
                    (
                        complex(2,0)
                    )
                )
                .addtion
                (
                    conj()
                    .production(c)
                    .production(c)
                )
                .division
                (
                    complex(1,0)
                    .addtion
                    (
                        complex(c.abs()*c.abs(),0)
                        .substraction
                        (
                            production
                            (
                                c.conj()
                            )
                        )
                        .substraction
                        (
                            c.production
                            (
                                conj()
                            )
                        )

                    )
                )
        );
}
