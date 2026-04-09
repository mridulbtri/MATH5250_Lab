#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

void get_input(int argc, char* argv[],
               const int my_rank,
               const int comm_sz,
               int* N);
void usage(const char* prog_name);

int main(int argc, char* argv[])
{
    // Setup MPI
    int comm_sz, my_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Grab N from command line and broadcast to all ranks
    int N;
    get_input(argc, argv, my_rank, comm_sz, &N);

    // Each rank gets its own chunk of points
    int N_local = N / comm_sz;

    // Seed using system time + rank so every rank gets
    // a different sequence every single run
    srand((unsigned int)(time(NULL) + my_rank * 1000));

    // Timing
    double time_start;
    if (my_rank == 0)
    { time_start = MPI_Wtime(); }

    // Each rank throws its points one by one
    // x and y are in [0, 1] — unit square
    // we check if point falls in the quarter circle of radius 1
    int count_local = 0;
    for (int i = 0; i < N_local; i++)
    {
        // Generate random (x, y) in [0, 1]
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        // quarter circle condition: x^2 + y^2 <= 1
        double dist = x*x + y*y;

        if (dist <= 1.0)
        { count_local++; }
    }

    // Gather all local counts to rank 0
    int count_total = 0;
    if (my_rank != 0)
    {
        MPI_Send(&count_local, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        count_total = count_local;
        for (int i = 1; i < comm_sz; i++)
        {
            MPI_Recv(&count_local, 1, MPI_INT, i, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count_total += count_local;
        }
    }

    // Rank 0 computes and prints pi
    if (my_rank == 0)
    {
        double time_end     = MPI_Wtime();
        double time_elapsed = time_end - time_start;

        double pi_estimate = 4.0 * count_total / N;

        printf("Processors  = %d\n",   comm_sz);
        printf("N           = %d\n",   N);
        printf("Pi estimate = %.10f\n", pi_estimate);
        printf("Actual pi   = %.10f\n", M_PI);
        printf("Error       = %.10f\n", fabs(pi_estimate - M_PI));
        printf("Time        = %.6f seconds\n", time_elapsed);
    }

    MPI_Finalize();
    return 0;
}

void get_input(int argc, char* argv[],
               const int my_rank,
               const int comm_sz,
               int* N)
{
    if (my_rank == 0)
    {
        if (argc != 2) { usage(argv[0]); }

        *N = strtol(argv[1], NULL, 10);
        if (*N <= 0)           { usage(argv[0]); }
        if (*N % comm_sz != 0) { usage(argv[0]); }

        for (int i = 1; i < comm_sz; i++)
        {
            MPI_Send(N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

void usage(const char* prog_name)
{
    fprintf(stderr, "usage: %s <N>\n",          prog_name);
    fprintf(stderr, "  N must be positive\n");
    fprintf(stderr, "  N must be divisible by number of processors\n");
    exit(1);
}