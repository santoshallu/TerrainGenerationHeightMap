/*
* view.h
* Author : Srinivasa Santosh Kumar Allu
* A-number : A01900937
*/

#ifndef VIEW_H
#define VIEW_H

void view_init(); // initializes camera angle and view position to look at
void view_update(int viewx, int viewy, int viewz, int posx, int posy, int posz);// updates the point to look at using glulookat

#endif  /* end VIEW_H */