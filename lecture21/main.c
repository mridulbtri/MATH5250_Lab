#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[])
{
    // Setup MPI
    int comm_sz, my_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int token;
    int src  = (my_rank - 1 + comm_sz) % comm_sz;
    int dest = (my_rank + 1) % comm_sz;

    if (my_rank == 0)
    {
        // Initialize token from command line, default 1000
        token = (argc == 2) ? strtol(argv[1], NULL, 10) : 1000;

        printf("Starting token = %d across %d processors\n\n", token, comm_sz);

        MPI_Send(&token, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        printf("Rank %d sent token %d to Rank %d\n", my_rank, token, dest);

        MPI_Recv(&token, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %d received token %d from Rank %d\n", my_rank, token, src);

        printf("\nFinal token = %d\n", token);
    }
    else
    {
        MPI_Recv(&token, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %d received token %d from Rank %d\n", my_rank, token, src);

        token += 1;

        MPI_Send(&token, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        printf("Rank %d sent token %d to Rank %d\n", my_rank, token, dest);
    }

    MPI_Finalize();
    return 0;
}