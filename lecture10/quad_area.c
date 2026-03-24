#include "quad_header.h"

void compute_area(struct ordered_quad* quad_data) {

    // computing area as the sum of area of two triangles
    // Triangle 1: point1, point2, point4
    double u1x = quad_data->point2.x - quad_data->point1.x;
    double u1y = quad_data->point2.y - quad_data->point1.y;
    double u1z = quad_data->point2.z - quad_data->point1.z;

    double v1x = quad_data->point4.x - quad_data->point1.x;
    double v1y = quad_data->point4.y - quad_data->point1.y;
    double v1z = quad_data->point4.z - quad_data->point1.z;

    // Triangle 2: point2, point3, point4
    double u2x = quad_data->point4.x - quad_data->point3.x;
    double u2y = quad_data->point4.y - quad_data->point3.y;
    double u2z = quad_data->point4.z - quad_data->point3.z;

    double v2x = quad_data->point2.x - quad_data->point3.x;
    double v2y = quad_data->point2.y - quad_data->point3.y;
    double v2z = quad_data->point2.z - quad_data->point3.z;

    // Cross product for triangle 1
    double c1x = u1y * v1z - u1z * v1y;
    double c1y = u1z * v1x - u1x * v1z;
    double c1z = u1x * v1y - u1y * v1x;

    // Cross product for triangle 2
    double c2x = u2y * v2z - u2z * v2y;
    double c2y = u2z * v2x - u2x * v2z;
    double c2z = u2x * v2y - u2y * v2x;

    // Calculate triangle areas (0.5 * magnitude of cross product)
    double area_1 = 0.5 * sqrt(c1x*c1x + c1y*c1y + c1z*c1z);
    double area_2 = 0.5 * sqrt(c2x*c2x + c2y*c2y + c2z*c2z);

    // Update the struct member directly
    quad_data->area = area_1 + area_2;
}
