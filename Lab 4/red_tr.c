#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value, result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    value = rank + 1;

    double start, end;

    // -------- MPI_Reduce --------
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0)
        printf("MPI_Reduce Result: %d Time: %f\n", result, end - start);

    // -------- Manual Tree Reduction --------
    int temp = value;

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    for (int step = 1; step < size; step *= 2)
    {
        if (rank % (2 * step) == 0)
        {
            if (rank + step < size)
            {
                int recv_val;
                MPI_Recv(&recv_val, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                temp += recv_val;
            }
        }
        else
        {
            MPI_Send(&temp, 1, MPI_INT, rank - step, 0, MPI_COMM_WORLD);
            break;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0)
        printf("Manual Reduce Result: %d Time: %f\n", temp, end - start);

    MPI_Finalize();
    return 0;
}