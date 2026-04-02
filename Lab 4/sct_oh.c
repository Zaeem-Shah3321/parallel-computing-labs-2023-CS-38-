#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_TESTS 3

int main(int argc, char *argv[])
{
    int rank, size;
    int *data = NULL;
    int *recv = NULL;
    int Ns[NUM_TESTS] = {1000, 10000, 100000}; // Different total sizes

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int t = 0; t < NUM_TESTS; t++)
    {
        int N = Ns[t];
        int chunk = N / size;

        // Allocate memory for root data
        if (rank == 0)
        {
            data = (int *)malloc(N * sizeof(int));
            for (int i = 0; i < N; i++)
                data[i] = i;
        }

        // Allocate recv buffer for each process
        recv = (int *)malloc(chunk * sizeof(int));

        double start, end;

        // ---------- MPI_Scatter ----------
        MPI_Barrier(MPI_COMM_WORLD);
        start = MPI_Wtime();

        MPI_Scatter(data, chunk, MPI_INT, recv, chunk, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Barrier(MPI_COMM_WORLD);
        end = MPI_Wtime();

        if (rank == 0)
            printf("N=%d MPI_Scatter Time: %f seconds\n", N, end - start);

        // ---------- Manual Scatter ----------
        MPI_Barrier(MPI_COMM_WORLD);
        start = MPI_Wtime();

        if (rank == 0)
        {
            // Send chunks to other processes
            for (int i = 1; i < size; i++)
                MPI_Send(&data[i * chunk], chunk, MPI_INT, i, 0, MPI_COMM_WORLD);

            // Copy own chunk
            for (int i = 0; i < chunk; i++)
                recv[i] = data[i];
        }
        else
        {
            MPI_Recv(recv, chunk, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        MPI_Barrier(MPI_COMM_WORLD);
        end = MPI_Wtime();

        if (rank == 0)
            printf("N=%d Manual Scatter Time: %f seconds\n\n", N, end - start);

        free(recv);
        if (rank == 0)
            free(data);
    }

    MPI_Finalize();
    return 0;
}