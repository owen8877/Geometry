#ifndef ELEMENT_H_
#define ELEMENT_H_
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
        complex normal();
        double abs() const;
        double abs2() const;
        double arg() const;
        complex conj();

        complex operator -();
        complex operator +(const complex &c);
        complex operator -(const complex &c);
        complex operator *(const complex &c);
        complex operator /(const complex &c);
        friend complex operator +(double a, const complex &b);
        friend complex operator -(double a, const complex &b);
        friend complex operator *(double a, const complex &b);
        friend complex operator /(double a, const complex &b);

        //bool operator ==(const complex &c);

        virtual void print();
};

// The class of points on the Poincare disk
class point : public complex{
    public:
        point();
        point(double _x, double _y);
        point(complex c);

        point mobius(complex c);
        point rotate(double theta);

        virtual void print();
};

// The class of ideal points (points on the edge of the Poincare disk)
// Each ideal point as a radius 1
class ideal : public complex{
    private:
    public:
        ideal():complex(1.0, 0.0){}
        ideal(double theta):complex(cos(theta), sin(theta)){}
        ideal(complex c);
        ideal(double _x, double _y);

        ideal mobius(complex c);
        ideal rotate(double theta);

        virtual void print();
};

//Rewritten class line
class line{
    private:
        ideal left, right;
    public:
        line(ideal a, ideal b):left(a), right(b){}
        line(point a, point b);
        line(ideal a, point b);
        line(point a, ideal b);
        line(complex center);
        line(double x, double y);

        ideal getLeft();
        ideal getRight();

        bool isDiameter();
        complex getCenter();
        double getRadius();

        line mobius(complex c);
        line rotate(double theta);

        virtual void print();
};

class segment : public line{
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
        ideal operator ()(ideal q);
        transform operator ()(transform t);
        transform operator *(transform t);
        transform inversion();
};

// returns a complex with radius 1 and argument theta
inline complex unit(double theta){
    return complex(cos(theta), sin(theta));
}

point getPointByDistance(point p, ideal q, double d);
point rotateByPoint(point p, point center, double phi);
line getLineByAngle(point p, ideal q, double phi);

#endif
