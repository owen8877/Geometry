#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <math.h>

const double PAI = 3.1415926;

class complex{
protected:
    double x, y;
public:
    complex();
    complex(double _x, double _y);
    complex(double _x);
    complex(int _x);
    void setX(double _x);
    void setY(double _y);
    const double getX() const;
    const double getY() const;

    complex addtion(complex c);
    complex substraction(complex c);
    complex production(complex c);
    complex division(complex c);
    complex reversion();
    complex negative();
    double abs() const;
    double abs2() const;
    complex conj();
    virtual void print();

    complex operator -();

    complex operator +(const complex &c);
    complex operator -(const complex &c);
    complex operator *(const complex &c);
    complex operator /(const complex &c);
    friend complex operator +(double a, const complex &b);
    friend complex operator -(double a, const complex &b);
    friend complex operator *(double a, const complex &b);
    friend complex operator /(double a, const complex &b);
    //friend complex operator +(complex const &a, double b);
    //friend complex operator -(complex const &a, double b);
    //friend complex operator *(complex const &a, double b);
    //friend complex operator /(complex const &a, double b);
};

class point : public complex{
public:
    point();
    point(double _x, double _y);
    point(complex c);
    point mobius(complex c);
    virtual void print();
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
    virtual void print();
};

inline complex unit(double theta){ return complex(cos(theta), sin(theta)); }

point getPointByDistance(point p, line l, bool flag, double d);
#endif
