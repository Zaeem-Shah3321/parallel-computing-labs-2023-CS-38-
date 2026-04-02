#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value, sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    value = rank + 1;
    sum = value;

    int step;

    // -------- Upward Phase (Reduce) --------
    for (step = 1; step < size; step *= 2)
    {
        if (rank % (2 * step) == 0)
        {
            if (rank + step < size)
            {
                int temp;
                MPI_Recv(&temp, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                sum += temp;
            }
        }
        else
        {
            MPI_Send(&sum, 1, MPI_INT, rank - step, 0, MPI_COMM_WORLD);
            break;
        }
    }

    // -------- Downward Phase (Scan) --------
    for (step /= 2; step > 0; step /= 2)
    {
        if (rank % (2 * step) == 0)
        {
            if (rank + step < size)
            {
                int temp = sum;
                MPI_Send(&temp, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD);
            }
        }
        else
        {
            MPI_Recv(&sum, 1, MPI_INT, rank - step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += value;
        }
    }

    printf("Process %d final sum = %d\n", rank, sum);

    MPI_Finalize();
    return 0;
}