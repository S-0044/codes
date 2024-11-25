#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n)
{
    int temp;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main()
{
    int n;
    printf("Enter number of integers to sort: ");
    scanf("%d", &n);
    
    int arr[n], arr_child[n];
    printf("Enter the integers:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        arr_child[i] = arr[i];
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("\nChild : Sorting array using Selection Sort...\n");
        
        selectionSort(arr_child, n);
        
        printf("Child : Sorted array (Selection Sort): ");
        
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr_child[i]);
        }
        printf("\n");

        sleep(5); 
        printf("Child : I am an orphan process now. My parent has terminated.\n");

    }
    else
    {
        printf("\nParent : Sorting array using Bubble Sort...\n");
        
        bubbleSort(arr, n);
        
        printf("Parent : Sorted array (Bubble Sort): ");
        
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        printf("Parent : Waiting for the child process to finish...\n");
        
        wait(NULL);
        
        printf("Parent : Child process has terminated. No zombie state.\n");

        pid_t zombie_pid = fork();
        
        if (zombie_pid == 0)
        {
            printf("Second Child : I will finish quickly and become a zombie...\n");
            exit(0);
        }
        else
        {
            sleep(10);
            printf("Parent : Observing second child as a zombie for 10 seconds...\n");
            wait(NULL);
            printf("Parent : Second child process reaped. No more zombie.\n");
        }

        printf("Parent : Parent process exiting...\n");
    }

    return 0;
}