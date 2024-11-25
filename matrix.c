#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
int rowA, colA, rowB, colB;

typedef struct
{
    int row;
} ThreadData;

void* multiply(void* arg)
{
    ThreadData* data = (ThreadData*) arg;
    int row = data->row;

    for (int i = 0; i < colB; i++)
    {
        C[row][i] = 0;
        for (int j = 0; j < colA; j++)
        {
            C[row][i] += A[row][j] * B[j][i];
        }
    }

    pthread_exit(0);
}

int main()
{
    printf("Enter dimensions of matrix A (rows and columns): ");
    scanf("%d%d", &rowA, &colA);

    printf("Enter dimensions of matrix B (rows and columns): ");
    scanf("%d%d", &rowB, &colB);

    if (colA != rowB)
    {
        printf("Matrix multiplication not possible, columns of A must equal rows of B.\n");
        return 1;
    }

    printf("Enter matrix A:\n");
    
    for (int i = 0; i < rowA; i++)
    {
        for (int j = 0; j < colA; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter matrix B:\n");
    
    for (int i = 0; i < rowB; i++)
    {
        for (int j = 0; j < colB; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    pthread_t threads[MAX];
    ThreadData thread_data[MAX];

    for (int i = 0; i < rowA; i++)
    {
        thread_data[i].row = i;
        pthread_create(&threads[i], NULL, multiply, (void*)&thread_data[i]);
    }

    for (int i = 0; i < rowA; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Result matrix C:\n");
    
    for (int i = 0; i < rowA; i++)
    {
        for (int j = 0; j < colB; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
