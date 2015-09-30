#ifndef _ELEMENT_H_
#define _ELEMENT_H_

const double PAI = 3.1415926;

class complex{
protected:
    double x, y;
public:
    complex();
    complex(double _x, double _y);
    void setX(double _x);
    void setY(double _y);
    double getX();
    double getY();

    complex addtion(complex _c);
    complex substraction(complex _c);
    complex production(complex _c);
    complex division(complex _c);
    complex reversion();
    complex negative();
    double abs();
    complex conj();
    void print();
};

class point : public complex{
public:
    point();
    point(double _x, double _y);
    point(complex c);
    point mobius(complex c);
};

class line : public complex{
public:
    line(double _x, double _y);
    line(complex c);
    point getCenter();
    double getRadius();
    double getStartArc();
    double getEndArc();
    line mobius(complex c);
};
#endif
