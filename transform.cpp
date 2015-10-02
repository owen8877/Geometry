#include <math.h>
#include <stdio.h>
#include "element.h"

point transform::operator ()(point p){
    return point( unit(th) * (p - c) / (1 - p*c.conj()) );
}

line transform::operator ()(line l){
    return line( unit(th) * (l + l.conj()*c*c - 2*c) / (1 + c.abs2() - l*c.conj() - l.conj()*c) );
}

transform transform::operator ()(transform t){
    complex e = unit(t.th);
    return transform( th + ( (e + t.c.conj()*c) / (1 + t.c*c.conj()*e) ).arg() ,
                    (e*t.c + c) / (e + t.c.conj()*c) );
}

transform transform::operator *(transform t){
    complex e = unit(t.th);
    return transform( th + ( (e + t.c.conj()*c) / (1 + t.c*c.conj()*e) ).arg() ,
                    (e*t.c + c) / (e + t.c.conj()*c) );
}
