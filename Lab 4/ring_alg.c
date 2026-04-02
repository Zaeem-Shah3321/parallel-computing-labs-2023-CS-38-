#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// Custom allgather using ring algorithm
void my_Allgather(int *sendbuf, int sendcount, int *recvbuf, int rank, int size)
{
    int i, step;
    int prev = (rank - 1 + size) % size;
    int next = (rank + 1) % size;

    // Copy own data to correct position in recvbuf
    for (i = 0; i < sendcount; i++)
        recvbuf[rank * sendcount + i] = sendbuf[i];

    // Temporary buffer to receive incoming data
    int *tempbuf = (int *)malloc(sendcount * sizeof(int));

    // Ring steps
    int send_rank = rank;
    for (step = 0; step < size - 1; step++)
    {
        // Determine which rank's data we are sending this step
        int send_pos = (rank - step + size) % size;

        // Send our latest data to next process
        MPI_Send(&recvbuf[send_pos * sendcount], sendcount, MPI_INT, next, 0, MPI_COMM_WORLD);

        // Receive data from previous process
        MPI_Recv(tempbuf, sendcount, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Determine which position to store received data
        int recv_pos = (rank - step - 1 + size) % size;
        for (i = 0; i < sendcount; i++)
            recvbuf[recv_pos * sendcount + i] = tempbuf[i];
    }

    free(tempbuf);
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sendcount = 1; // each process sends 1 integer
    int *sendbuf = (int *)malloc(sendcount * sizeof(int));
    sendbuf[0] = rank + 1; // just some test data

    int *recvbuf = (int *)malloc(size * sendcount * sizeof(int));

    // Time custom allgather
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();
    my_Allgather(sendbuf, sendcount, recvbuf, rank, size);
    MPI_Barrier(MPI_COMM_WORLD);
    double end = MPI_Wtime();

    // Print results
    printf("Rank %d received: ", rank);
    for (int i = 0; i < size * sendcount; i++)
        printf("%d ", recvbuf[i]);
    printf("\n");

    if (rank == 0)
        printf("ring_Allgather Time: %f seconds\n", end - start);

    // Compare with MPI_Allgather
    int *mpi_recvbuf = (int *)malloc(size * sendcount * sizeof(int));
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    MPI_Allgather(sendbuf, sendcount, MPI_INT, mpi_recvbuf, sendcount, MPI_INT, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0)
        printf("MPI_Allgather Time: %f seconds\n", end - start);

    free(sendbuf);
    free(recvbuf);
    free(mpi_recvbuf);

    MPI_Finalize();
    return 0;
}