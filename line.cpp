#include <math.h>
#include <stdio.h>
#include "element.h"

//Construct the line with a given center
line::line(complex center){
    left = ideal(complex(1.0, sqrt(center.abs2() - 1.0)) / center.conj());
    right = ideal(complex(1.0, -sqrt(center.abs2() - 1.0)) / center.conj());
}

//Construct the line with a center given in the form of components
line::line(double x, double y){
    complex center(x, y);
    left = ideal(complex(1.0, sqrt(center.abs2() - 1.0)) / center.conj());
    right = ideal(complex(1.0, -sqrt(center.abs2() - 1.0)) / center.conj());
}

//Construct the line with two points on it
line::line(point a, point b){
    complex u = a.conj()*b - a*b.conj();
    double v = ( (a - b) * (1 - a.conj()*b) ).abs();
    complex w = a.conj() * (1 + b.abs2()) - b.conj() * (1 + a.abs2());
    left = (u + v)/w;
    right = (u - v)/w;
}

bool line::isDiameter(){ return ((left + right).abs() < 1e-6); }

complex line::getCenter(){
    if (isDiameter()) throw "Error getting the center of a diameter.\n";
    return 2 / (1/left + 1/right);
}

double line::getRadius(){
    if (isDiameter()) throw "Error getting the radius of a diameter.\n";
    return ((left - right)/(left + right)).abs();
}

ideal line::getLeft(){ return left; }
ideal line::getRight(){ return right; }

//To implement the two transforms, we just need to transform its two endpoints
line line::mobius(complex c){ return line(left.mobius(c), right.mobius(c)); }
line line::rotate(double theta){ return line(left.rotate(theta), right.rotate(theta)); }

void line::print(){
    printf("Line: \n");
    printf("\tleft: ");   left.print();
    printf("\tright: "); right.print();
    if (isDiameter()) printf("\tThe line is a diameter.");
    else{
        printf("\tThe line is not a diameter. Its center is ");
        getCenter().print();
    }
    printf("\n");
}
