#include "quad_header.h"

void order_points_CCW(struct ordered_quad* quad_data) {

    pts* p[4] = {&quad_data->point1, &quad_data->point2, &quad_data->point3, &quad_data->point4};

    // Calculate the centroid
    double cx = (p[0]->x + p[1]->x + p[2]->x + p[3]->x) / 4.0;
    double cy = (p[0]->y + p[1]->y + p[2]->y + p[3]->y) / 4.0;

    // Get the angle for each point
    double angles[4];
    for(int i = 0; i < 4; i++) {
        angles[i] = atan2(p[i]->y - cy, p[i]->x - cx);
    }

    // Swaps the actual data in the original struct memory
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3 - i; j++) {
            if (angles[j] > angles[j + 1]) {
                // Swap angles
                double tempA = angles[j];
                angles[j] = angles[j + 1];
                angles[j + 1] = tempA;

                // Swap the actual 'pts' data using the pointers
                pts tempP = *p[j];
                *p[j] = *p[j + 1];
                *p[j + 1] = tempP;
            }
        }
    }
}