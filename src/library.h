#ifndef PYGL2D_LIBRARY_H
#define PYGL2D_LIBRARY_H

#include <stdbool.h>

void *initWindow(int, int, const char *);
void setClearColor(float, float, float, float);
void clear(void *);
int eventOnClose(void *);
void pollEvents();
void terminate();
void drawTriangle(float, float, float, float, float, float, float, float, float, float);
void drawTriangleFan(int, const float *, const float *, float, float, float, float);
void drawLine(float, float, float, float, float, float, float, float, float, bool);
void display(void *);

#endif