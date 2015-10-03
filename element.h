#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <math.h>

// The class of complex numbers, use as intended.
class complex{
    protected:
        double x, y;
    public:
        complex();
        complex(double _x, double _y);
        complex(double _x);
        complex(int _x);
        void set(double _x, double _y);
        void setX(double _x);
        void setY(double _y);
        double getX() const;
        double getY() const;

        complex addtion(complex c);
        complex substraction(complex c);
        complex production(complex c);
        complex division(complex c);
        complex reciprocal();
        complex negative();
        double abs() const;
        double abs2() const;
        double arg() const;
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

        //bool operator ==(const complex &c);
};

// The class of points on the Poincare disk
class point : public complex{
    public:
        point();
        point(double _x, double _y);
        point(complex c);
        point mobius(complex c);
        virtual void print();
};

//Rewritten class line
class line{
    private:
        point left, right;
        //flag: true means the line is a diameter; false means the line is NOT a diameter.
        bool flag;
        //if flag is true, the variable center is invalid.
        point center;
        line(complex _left, complex _right, int _flag);
    public:
        line(point _center);
        line(double _x, double _y);
        line(complex a, complex b);
        bool isDiameter();
        point getCenter();
        double getRadius();
        point getLeft();
        point getRight();
        line mobius(complex c);
        line rotate(complex c);
        virtual void print();
};

// The class of isometries (transforms that preserves distance) on the Poincare disk
// Transform point z to e^(i*th)*(z-c)/(1-z*c.conj())
class transform{
    private:
        double th;
        complex c;
    public:
        transform(double theta):th(theta), c(0.0){}
        transform(complex center):th(0.0), c(center){}
        transform(double theta, complex center):th(theta), c(center){}
        point operator ()(point p);
        line operator ()(line l);
        transform operator ()(transform t);
        transform operator *(transform t);
};

// returns a complex with radius 1 and argument theta
inline complex unit(double theta){ return complex(cos(theta), sin(theta)); }

point getPointByDistance(point p, line l, double d);
#endif
