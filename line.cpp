#include <math.h>
#include <stdio.h>
#include "element.h"
//inline double absl(double d){ return (d > 0) ? d : (-d); }

//This constructor is private, just meant to simplify the codes in 'mobius' and 'rotate'
line::line(complex _left, complex _right, int _flag){
    left = _left;
    right = _right;
    center = (left.reciprocal() + right.reciprocal()) / 2.0;
    flag = (center.abs() < 1e-6);
}

//Construct the line with a given center
line::line(point _center){
    center = _center.reciprocal();
    //Since the center is given, the line can no longer be a diameter.
    flag = false;
    left = complex(1.0, sqrt(_center.abs2() - 1.0)) / _center.conj();
    right = complex(1.0, -sqrt(_center.abs2() - 1.0)) / _center.conj();
}

//Construct the line with a center given in the form of components
line::line(double _x, double _y){
    complex _center(_x, _y);
    center = _center.reciprocal();
    //Since the center is given, the line can no longer be a diameter.
    flag = false;
    left = complex(1.0, sqrt(_center.abs2() - 1.0)) / _center.conj();
    right = complex(1.0, -sqrt(_center.abs2() - 1.0)) / _center.conj();
}

//Construct the line with two points on it
line::line(complex a, complex b){
    double u = a.getX()*b.getY() - a.getY()*b.getX();
    if (!u){
        //The line is a diameter!!!
        flag = true;
        left = a / a.abs();//A bug may occur, when a is zero
        right = -left;
        center = point();
        return;
    }
    double A = 1 + a.abs2();
    double B = 1 + b.abs2();
    double x = (a.getY()*B-b.getY()*A) / (-2.0*u);
    double y = (a.getX()*B-b.getX()*B) / (-2.0*u);
    point center = point(x,y).reciprocal();
    flag = false;
    left = complex(1.0, sqrt(center.abs2() - 1.0)) / center.conj();
    right = complex(1.0, -sqrt(center.abs2() - 1.0)) / center.conj();
}

bool line::isDiameter(){ return (center.abs() < 1e-6); }

point line::getCenter(){
    if (!isDiameter()) return center.reciprocal();
    //The line is a diameter, we cannot get its center
    printf("Error getting the center of a diameter.\n");
    return complex(0.0, 0.0);
}

double line::getRadius(){
    if (!isDiameter()) return sqrt(1.0/(center.abs2()) - 1.0);
    //The line is a diameter, we cannot get its radius
    printf("Error getting the radius of a diameter.\n");
    return 0.0;
}

point line::getLeft(){ return left; }
point line::getRight(){ return right; }

//To implement the two transforms, we just need to transform its two endpoints
line line::mobius(complex c){ return line(left.mobius(c), right.mobius(c), 0); }
line line::rotate(complex c){ return line(left*c, right*c, 0); }

void line::print(){
    printf("Line: \n");
    printf("\tleft: ");   left.print();
    printf("\tright: "); right.print();
    if (isDiameter()) printf("\tThe line is a diameter.");
    else{
        printf("\tThe line is not a diameter. Its center is ");
        center.print();
    }
    printf("\n");
}
