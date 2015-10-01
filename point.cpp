#include <math.h>
#include <stdio.h>
#include "element.h"

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
    //return point(substraction(c).division(complex(1,0).substraction(production(c.conj()))));
    return point(((*this) - c)/(1.0 - (*this)*c.conj()));
}
