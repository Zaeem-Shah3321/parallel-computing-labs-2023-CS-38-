#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value, sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process starts with value = rank + 1
    value = rank + 1;
    sum = value;

    if (rank != 0)
    {
        // Receive sum from previous process
        MPI_Recv(&sum, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Add own value
        sum += value;
    }

    if (rank != size - 1)
    {
        // Send updated sum to next process
        MPI_Send(&sum, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    // Print final result
    printf("Process %d final sum = %d\n", rank, sum);

    MPI_Finalize();
    return 0;
}