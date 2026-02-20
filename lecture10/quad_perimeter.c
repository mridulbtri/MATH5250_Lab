#include "quad_header.h"
void compute_perimeter(struct ordered_quad* quad_data) {

    int i;
    pts* points_array[4] = {&quad_data->point1, &quad_data->point2, &quad_data->point3, &quad_data->point4};
    
    // Use (i + 1) % 4 to connect point 4 back to point 1
    quad_data->perimeter = 0;

    for (i = 0; i < 4; i++) {
        int next = (i + 1) % 4;

        // compute distance between consecutive points and sum them up
        // compute difference in each coordinate
        double dx = points_array[next]->x - points_array[i]->x;
        double dy = points_array[next]->y - points_array[i]->y;
        double dz = points_array[next]->z - points_array[i]->z;

        // compute distance using 3D distance formula
        quad_data->perimeter += sqrt(dx * dx + dy * dy + dz * dz);
    }
}