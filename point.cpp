#include <math.h>
#include <stdio.h>
#include "element.h"

point::point():complex(0.0){}

point::point(double _x, double _y):complex(_x, _y){}

point::point(complex c):complex(c){}

point point::mobius(complex c){
    //return point(substraction(c).division(complex(1,0).substraction(production(c.conj()))));
    return point(((*this) - c)/(1.0 - (*this)*c.conj()));
}

void point::print(){
	printf("Point: ");
	complex::print();
}
