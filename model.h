#ifndef MODEL_H
#define MODEL_H

#define LEFT_MOUSE_BUTTON    0x0001
#define MIDDLE_MOUSE_BUTTON  0x0002
#define RIGHT_MOUSE_BUTTON   0x0004

void initModel();
void update(int kbstat[]);
void renewMouseStat(double x, double y, int button);

#endif
