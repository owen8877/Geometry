#ifndef DRAW_H_
#define DRAW_H_

void drawCircle(point center, double radius);
void drawArc(point center, double radius, double startarc, double endarc);
void drawLine(line l);
void drawPoint(point p);
void drawPoint(point p, double size);
void drawPoint(point p, int r, int g, int b);
void reshape(int width, int height);
void initDisplay();
void display();

#endif
