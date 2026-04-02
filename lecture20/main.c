#include "header.h"

int main(int argc, char* argv[])
{
    void   usage(const char* prog_name);
    double AdaptiveInt(const double a,
                       const double b,
                       const double TOL,
                       char* filename);

    if (argc != 3) { usage(argv[0]); }
    const int    thread_count = strtol(argv[1], NULL, 10);
    const double TOL          = strtod(argv[2], NULL);
    if (thread_count < 0 || TOL < 5.0e-16) { usage(argv[0]); }

    {
        FILE* file = fopen("thread_count.data", "w");
        fprintf(file, "%i\n", thread_count);
        fclose(file);
    }

    double t_start, t_end;

    /* ---- Problem 1: Electrostatic Potential ---- */
    const double a_elec = -1.0;
    const double b_elec =  1.0;
    const int    Npts   = 201;

    double x0arr[201];
    double Varr [201];
    for (int i = 0; i < Npts; i++)
        x0arr[i] = a_elec + (b_elec - a_elec) * (i + 0.5) / Npts;

    for (int i = 1; i <= thread_count; i++)
    {
        char filename[36] = "potential";
        char file_add[36] = ".data";
        char str[36]; sprintf(str, "%i", i);
        strcat(filename, str);
        strcat(filename, file_add);
        FILE* file = fopen(filename, "w");
        fclose(file);
    }

    t_start = omp_get_wtime();
#pragma omp parallel num_threads(thread_count)
    {
        const int my_rank = omp_get_thread_num();
        char filename[36] = "potential";
        char file_add[36] = ".data";
        char str[36]; sprintf(str, "%i", my_rank + 1);
        strcat(filename, str);
        strcat(filename, file_add);

        const double width   = (double)Npts / (double)thread_count;
        const int    i_start = (int)( my_rank      * width);
        const int    i_end   = (my_rank == thread_count - 1) ? Npts
                             : (int)((my_rank + 1) * width);

        const double TOL_local = TOL / (double)thread_count;
        PROBLEM = 0;

        for (int i = i_start; i < i_end; i++)
        {
            X0 = x0arr[i];

            FILE* fp = fopen(filename, "a");
            fprintf(fp, " %24.15e %24.15e\n", a_elec, b_elec);
            fclose(fp);

            double I_reg = AdaptiveInt(a_elec, b_elec, TOL_local, filename);
            double I_log = exp(-x0arr[i]*x0arr[i])
                           * log((b_elec - x0arr[i]) / (x0arr[i] - a_elec));
            Varr[i] = I_reg + I_log;
        }
    }
    t_end = omp_get_wtime();

    FILE* fout1 = fopen("potential.data", "w");
    for (int i = 0; i < Npts; i++)
        fprintf(fout1, " %24.15e %24.15e\n", x0arr[i], Varr[i]);
    fclose(fout1);

    printf("\n");
    printf(" Problem 1: Electrostatic Potential\n");
    printf(" thread_count = %i\n",       thread_count);
    printf(" TOL          = %24.15e\n",  TOL);
    printf(" wall time    = %24.15e s\n", t_end - t_start);
    printf("\n");

    /* ---- Problem 2: Bessel Function ---- */
    const int Nx = 501;
    double xbarr[501];
    double J0arr[501];
    for (int i = 0; i < Nx; i++)
        xbarr[i] = 50.0 * i / (Nx - 1);

    for (int i = 1; i <= thread_count; i++)
    {
        char filename[36] = "bessel";
        char file_add[36] = ".data";
        char str[36]; sprintf(str, "%i", i);
        strcat(filename, str);
        strcat(filename, file_add);
        FILE* file = fopen(filename, "w");
        fclose(file);
    }

    t_start = omp_get_wtime();
#pragma omp parallel num_threads(thread_count)
    {
        const int my_rank = omp_get_thread_num();
        char filename[36] = "bessel";
        char file_add[36] = ".data";
        char str[36]; sprintf(str, "%i", my_rank + 1);
        strcat(filename, str);
        strcat(filename, file_add);

        const double width   = (double)Nx / (double)thread_count;
        const int    i_start = (int)( my_rank      * width);
        const int    i_end   = (my_rank == thread_count - 1) ? Nx
                             : (int)((my_rank + 1) * width);

        const double TOL_local = TOL / (double)thread_count;
        PROBLEM = 1;

        for (int i = i_start; i < i_end; i++)
        {
            XVAL = xbarr[i];

            FILE* fp = fopen(filename, "a");
            fprintf(fp, " %24.15e %24.15e\n", 0.0, M_PI);
            fclose(fp);

            J0arr[i] = AdaptiveInt(0.0, M_PI, TOL_local, filename);
        }
    }
    t_end = omp_get_wtime();

    FILE* fout2 = fopen("bessel.data", "w");
    for (int i = 0; i < Nx; i++)
        fprintf(fout2, " %24.15e %24.15e\n", xbarr[i], J0arr[i]);
    fclose(fout2);

    printf(" Problem 2: Bessel Function J0\n");
    printf(" thread_count = %i\n",       thread_count);
    printf(" TOL          = %24.15e\n",  TOL);
    printf(" wall time    = %24.15e s\n", t_end - t_start);
    printf("\n");

    system("python3 plot.py");

    return 0;
}