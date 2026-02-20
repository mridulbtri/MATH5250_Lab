#include "quad_header.h"
void compute_angles(struct ordered_quad* quad_data) {
    int i;
    pts* points_array[4] = {&quad_data->point1, &quad_data->point2, &quad_data->point3, &quad_data->point4};

    for (i = 0; i < 4; i++) {
        int prev = (i + 3) % 4; // Previous point index
        int next = (i + 1) % 4; // Next point index

        // Vectors from current point to previous and next points
        double ux = points_array[prev]->x - points_array[i]->x;
        double uy = points_array[prev]->y - points_array[i]->y;
        double uz = points_array[prev]->z - points_array[i]->z;

        double vx = points_array[next]->x - points_array[i]->x;
        double vy = points_array[next]->y - points_array[i]->y;
        double vz = points_array[next]->z - points_array[i]->z;

        // Dot product and magnitudes for angle calculation
        double dot_product = ux * vx + uy * vy + uz * vz;
        double mag_u = sqrt(ux * ux + uy * uy + uz * uz);
        double mag_v = sqrt(vx * vx + vy * vy + vz * vz);

        // Calculate angle in radians and convert to degrees
        quad_data->angles[i] = acos(dot_product / (mag_u * mag_v)) * (180.0 / M_PI);
    }
}