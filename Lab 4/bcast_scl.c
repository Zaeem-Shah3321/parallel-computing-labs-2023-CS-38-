#include <mpi.h>
#include <stdio.h>

#define SIZE 10000

int main(int argc, char *argv[])
{
    int rank, size;
    int data[SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start, end;

    // ---------------- MPI_Bcast ----------------
    if (rank == 0)
    {
        for (int i = 0; i < SIZE; i++)
            data[i] = i;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    MPI_Bcast(data, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0)
        printf("MPI_Bcast Time: %f\n", end - start);

    // ---------------- Manual Broadcast ----------------
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Send(data, SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(data, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0)
        printf("Manual Broadcast Time: %f\n", end - start);

    MPI_Finalize();
    return 0;
}