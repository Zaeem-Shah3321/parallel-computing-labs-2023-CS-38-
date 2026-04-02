#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int data;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();
    if (rank == 0)
    {
        // Root process initializes data
        data = 1000;
        printf("Process %d sending value %d\n", rank, data);

        // Send data to process 1
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        // Process 1 receives data
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received data = %d\n", rank, data);
    }
    end_time = MPI_Wtime();
    MPI_Finalize();
    if (rank == 0)
    {
        printf("Execution time with %d processes: %f seconds\n", size, end_time - start_time);
    }

    return 0;
}