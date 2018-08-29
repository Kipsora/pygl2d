#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "src/library.h"

int main() {
    void *window = initWindow(800, 600, "demo");
    if (window == NULL) {
        perror("ERROR");
        return 0;
    }
    setClearColor(0, 0, 0, 0);
    double t = 0.0;
    while (!eventOnClose(window)) {
        pollEvents();
        clear(window);
//        drawTriangle(-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f, 0.7f, 0.5f, 0.2f, 1.0f);
        const int n = 4;
        float x[n] = {-0.5f, -0.5f, 0.5f, 0.5f};
        float y[n] = {-0.5f, 0.5f, 0.5f, -0.5f};
        drawTriangleFan(n, x, y, 0.7f, 0.5f, 0.2f, 1.0f);
        drawLine(0.0f, 0.0f, 1.0f, 1.0f, 2.0f, 0.7f, 0.5f, 0.2f, 1.0f, true);
//        drawPoints(n, x, y, 1.0f, 0.0f, 1.0f, 1.0f);
        display(window);
    }
    terminate();
    return 0;
}