#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int N = 8; // total elements
    int local_n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_n = N / size;

    int *local = (int *)malloc(local_n * sizeof(int));

    // Initialize data (example)
    for (int i = 0; i < local_n; i++)
        local[i] = rank * local_n + i + 1;

    // -------- Step 1: Local Prefix --------
    for (int i = 1; i < local_n; i++)
        local[i] += local[i - 1];

    // -------- Step 2: Local Sum --------
    int local_sum = local[local_n - 1];

    // -------- Step 3: MPI_Scan --------
    int scan_sum;
    MPI_Scan(&local_sum, &scan_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    int offset = scan_sum - local_sum;

    // -------- Step 4: Add Offset --------
    for (int i = 0; i < local_n; i++)
        local[i] += offset;

    // Print result
    printf("Process %d: ", rank);
    for (int i = 0; i < local_n; i++)
        printf("%d ", local[i]);
    printf("\n");

    free(local);
    MPI_Finalize();
    return 0;
}