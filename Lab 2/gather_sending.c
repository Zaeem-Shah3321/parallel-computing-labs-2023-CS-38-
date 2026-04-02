#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);               
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (rank != 0)
    {
        
        int send_array[ARRAY_SIZE];
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            send_array[i] = rank * 100 + i; 
        }
        
        MPI_Send(send_array, ARRAY_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        for (int source = 1; source < size; source++)
        {
            int recv_array[ARRAY_SIZE];
            MPI_Status status;
            
            MPI_Recv(recv_array, ARRAY_SIZE, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
            
            printf("Process 0 received from %d: ", status.MPI_SOURCE);
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                printf("%d ", recv_array[i]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}