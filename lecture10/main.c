#include<stdio.h>
#include "quad_header.h"

// Function declarations
void order_points_CCW(struct ordered_quad* quad_data);
void compute_perimeter(struct ordered_quad* quad_data);
void compute_area(struct ordered_quad* quad_data);
void compute_sides(struct ordered_quad* quad_data);
void compute_angles(struct ordered_quad* quad_data);

int main(){

    quadilateral quad; // declaring a variable of type struct quadilateral to store the input points of the quadrilateral

    printf("Please, enter the coordinates of each point one by one in the format x,y,z: \n");
    printf("Point 1: ");
    scanf("%lf %lf %lf", &quad.point1.x, &quad.point1.y, &quad.point1.z);
    printf("Point 2: ");
    scanf("%lf %lf %lf", &quad.point2.x, &quad.point2.y, &quad.point2.z);
    printf("Point 3: ");
    scanf("%lf %lf %lf", &quad.point3.x, &quad.point3.y, &quad.point3.z);
    printf("Point 4: ");
    scanf("%lf %lf %lf", &quad.point4.x, &quad.point4.y, &quad.point4.z);

    // Print the original points
    printf("\n=========================================================================\n");
    printf("The points entered are: \n");
    printf("Point1 = (%.2lf, %.2lf, %.2lf)\n", quad.point1.x, quad.point1.y, quad.point1.z);
    printf("Point2 = (%.2lf, %.2lf, %.2lf)\n", quad.point2.x, quad.point2.y, quad.point2.z);
    printf("Point3 = (%.2lf, %.2lf, %.2lf)\n", quad.point3.x, quad.point3.y, quad.point3.z);
    printf("Point4 = (%.2lf, %.2lf, %.2lf)\n", quad.point4.x, quad.point4.y, quad.point4.z);

    // The ordered quad struct is used to store the points in a consistent order (counter-clockwise) along with the computed properties like perimeter, area, angles, and sides.
    ordered_quad quad_data; // declaring a variable of type struct ordered_quad to store the ordered points and computed properties of the quadrilateral

    quad_data.point1 = quad.point1;
    quad_data.point2 = quad.point2;
    quad_data.point3 = quad.point3;
    quad_data.point4 = quad.point4;

    // Order points naming in counter-clockwise manner
    order_points_CCW(&quad_data);

    // Print the ordered points
    printf("\n=========================================================================\n");
    printf("Reordered points in counter-clockwise manner: \n");
    printf("Point1 = (%.2lf, %.2lf, %.2lf)\n", quad_data.point1.x, quad_data.point1.y, quad_data.point1.z);
    printf("Point2 = (%.2lf, %.2lf, %.2lf)\n", quad_data.point2.x, quad_data.point2.y, quad_data.point2.z);
    printf("Point3 = (%.2lf, %.2lf, %.2lf)\n", quad_data.point3.x, quad_data.point3.y, quad_data.point3.z);
    printf("Point4 = (%.2lf, %.2lf, %.2lf)\n", quad_data.point4.x, quad_data.point4.y, quad_data.point4.z);

    // Compute and print the perimeter of the quadrilateral
    compute_perimeter(&quad_data);
    printf("\n=========================================================================\n");
    printf("The perimeter of the quadrilateral is: %.2lf\n", quad_data.perimeter);

    // Compute and print the area of the quadrilateral
    compute_area(&quad_data);
    printf("\n=========================================================================\n");
    printf("The area of the quadrilateral is: %.2lf\n", quad_data.area);

    // Compute and print the lengths of the sides of the quadrilateral
    compute_sides(&quad_data);
    printf("\n=========================================================================\n");
    printf("The lengths of the sides of the quadrilateral are: \n");
    printf("Side 1 (Point1----Point2) %.2lf\n", quad_data.sides[0]);
    printf("Side 2 (Point2----Point3) %.2lf\n", quad_data.sides[1]);
    printf("Side 3 (Point3----Point4) %.2lf\n", quad_data.sides[2]);
    printf("Side 4 (Point4----Point1) %.2lf\n", quad_data.sides[3]);

    // compute angles between adjacent sides
    compute_angles(&quad_data);
    printf("\n=========================================================================\n");
    printf("The angles between adjacent sides of the quadrilateral are: \n");
    printf("Angle at Point1 (between Side4 and Side1) %.2lf degrees\n", quad_data.angles[0]);   
    printf("Angle at Point2 (between Side1 and Side2) %.2lf degrees\n", quad_data.angles[1]);   
    printf("Angle at Point3 (between Side2 and Side3) %.2lf degrees\n", quad_data.angles[2]);
    printf("Angle at Point4 (between Side3 and Side4) %.2lf degrees\n", quad_data.angles[3]);

    
}