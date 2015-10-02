#include <math.h>
#include <stdio.h>
#include "element.h"
inline double absl(double d){ return (d > 0) ? d : (-d); }
/* These codes are old.
line::line(double _x, double _y):complex(_x, _y){}

line::line(complex c):complex(c){}

point line::getCenter(){ return point(x, y); }

double line::getRadius(){ return sqrt(abs2() - 1); }

double line::getStartArc(){
    double middle = atan2(y, x) + M_PI;
    double deflection = asin(1/abs());
    return (middle - deflection);
}
double line::getEndArc(){
    double middle = atan2(y, x) + M_PI;
    double deflection = asin(1/abs());
    return (middle + deflection);
}

line line::mobius(complex c){
    return line(
            ( (*this) - c*2 + conj()*c*c )
            /
            ( 1 + c.abs2() - (*this)*c.conj() - c*conj() )
            );
}

void line::print(){
    printf("Line: ");
    complex::print();
}
*/

line::line(complex _left, complex _right, int _flag){
    left = _left;
    right = _right;
    if (absl(left.getX() + right.getX()) < 1e-6){
        flag = true;
        return;
    }
    flag = false;
    center = 2.0 * left * right / (left + right);
}

line::line(point _center){
    center = _center;
    //Since the center is given, the line can no longer be a diameter.
    flag = false;
    left = complex(1.0, sqrt(_center.abs2() - 1.0)) / _center.conj();
    right = complex(1.0, -sqrt(_center.abs2() - 1.0)) / _center.conj();
}

line::line(double _x, double _y){
    center = complex(_x, _y);
    //Since the center is given, the line can no longer be a diameter.
    flag = false;
    left = complex(1.0, sqrt(center.abs2() - 1.0)) / center.conj();
    right = complex(1.0, -sqrt(center.abs2() - 1.0)) / center.conj();
}

line::line(complex a, complex b){
    double u = a.getX()*b.getY() - a.getY()*b.getX();
    if (!u){
        //The line is a diameter!!!
        flag = true;
        left = a / a.abs();//A bug may occur
        right = -left;
        return;
    }
    double A = 1 + a.abs2();
    double B = 1 + b.abs2();
    double x = (a.getY()*B-b.getY()*A) / (-2.0*u);
    double y = (a.getX()*B-b.getX()*B) / (-2.0*u);
    point center = point(x,y);
    flag = false;
    left = complex(1.0, sqrt(center.abs2() - 1.0)) / center.conj();
    right = complex(1.0, -sqrt(center.abs2() - 1.0)) / center.conj();
}


bool line::isDiameter(){ return (absl(left.getX() + right.getX()) < 1e-6); }

point line::getCenter(){
    if (!isDiameter()){
        //lets calculate the center!
        center = 2.0 * left * right / (left + right);
        return center;
    }
    //The line is a diameter, we cannot get its center;
    printf("Error getting the center of a diameter.\n");
    return complex(0.0, 0.0);
}

double line::getRadius(){
    if (!isDiameter()){
        return sqrt(center.abs2() - 1.0);
    }
    printf("Error getting the radius of a diameter.\n");
    return 0.0;
}

point line::getLeft(){ return left; }
point line::getRight(){ return right; }

line line::mobius(complex c){
    /*return line(
            ( (*this) - c*2 + conj()*c*c )
            /
            ( 1 + c.abs2() - (*this)*c.conj() - c*conj() )
            );*/
    return line(left.mobius(c), right.mobius(c), 0);
}

line line::rotate(complex c){
    return line(left*c, right*c, 0);
}

void line::print(){
    printf("Line: \n");
    printf("\tleft: ");
    left.print();
    printf("\tright: ");
    right.print();
    if (isDiameter()){
        printf("\tThe line is a diameter.");
    }
    else{
        printf("\tThe line is not a diameter. Its center is ");
        center.print();
    }
    printf("\n");
}
