#include "header_poly.h"

void WriteToFile(const node* P, const node* Q, const node* R)
{
    FILE* fp = fopen("poly_data.csv", "w");

    if (fp == NULL)
    {
        printf("Error: could not open file poly_data.csv\n");
        return;
    }

    /* write header row */
    fprintf(fp, "x,P(x),Q(x),P+Q(x)\n");

    /* evaluate from -50 to 50 in steps of 0.5 */
    double x;
    for (x = -1.0; x <= 1.0; x += 0.01)
    {
        fprintf(fp, "%.2lf,%.6lf,%.6lf,%.6lf\n",
                x,
                EvaluatePoly(P, x),
                EvaluatePoly(Q, x),
                EvaluatePoly(R, x));
    }

    fclose(fp);
    printf("\n Data written to poly_data.csv\n");
}