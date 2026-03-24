
#ifndef QUAD_HEADER_H
#define QUAD_HEADER_H

#include<math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct points pts;
struct points{
    double x;
    double y;
    double z;
};

typedef struct quadilateral quadilateral;
struct quadilateral{
    pts point1;
    pts point2;
    pts point3;
    pts point4;
};

typedef struct ordered_quad ordered_quad;
struct ordered_quad{
    pts point1;
    pts point2;
    pts point3;
    pts point4;

    double perimeter;
    double area;
    double angles[4]; 
    double sides[4];
};

#endif

