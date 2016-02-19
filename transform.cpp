#include <cmath>
#include <cstdio>
#include "element.h"

using namespace std;

point transform::operator ()(point p){
    return point( unit(th) * (p - c) / (1 - p*c.conj()) );
}

line transform::operator ()(line l){
    return line(l.getLeft().mobius(c).rotate(th), l.getRight().mobius(c).rotate(th));
}

ideal transform::operator ()(ideal q){
    return q.mobius(c).rotate(th);
}

segment transform::operator ()(segment s){
    return s.mobius(c).rotate(th);
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

transform transform::inversion(){
    return transform( -th, -c*unit(th) );
}
