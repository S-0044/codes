#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
sem_t wrt;
int read_count = 0;

int shared_data = 0;

int waiting_writers = 0;
int waiting_readers = 0;

void *writer(void *arg)
{
    int writer_id = *((int *)arg);

    printf("Writer %d is waiting.\n", writer_id);
    waiting_writers++;

    sem_wait(&wrt);

    waiting_writers--;

    shared_data += 10;
    printf("Writer %d is writing to the shared resource. Updated value: %d\n", writer_id, shared_data);
    sleep(1);

    printf("Writer %d has finished writing.\n", writer_id);

    sem_post(&wrt);
    return NULL;
}

void *reader(void *arg)
{
    int reader_id = *((int *)arg);

    printf("Reader %d is waiting.\n", reader_id);
    waiting_readers++;

    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    waiting_readers--;
    printf("Reader %d is reading the shared resource. Value: %d\n", reader_id, shared_data);

    sleep(1);

    printf("Reader %d has finished reading.\n", reader_id);

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void display_status()
{
    printf("\n--- Current Status ---\n");
    printf("Waiting Writers: %d\n", waiting_writers);
    printf("Waiting Readers: %d\n", waiting_readers);
    printf("----------------------\n");
}

int main()
{

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int num_readers, num_writers;
    printf("Enter number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter number of writers: ");
    scanf("%d", &num_writers);

    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    for (int i = 0; i < num_writers; i++)
    {
        writer_ids[i] = i + 1;
    }
    for (int i = 0; i < num_readers; i++)
    {
        reader_ids[i] = i + 1;
    }

    int choice;
    while (1)
    {
        display_status();
        printf("\nChoose an action:\n");
        printf("1. Let a writer enter (choose writer ID)\n");
        printf("2. Let a reader enter (choose reader ID)\n");
        printf("3. Exit program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {

            int writer_id;
            printf("Enter writer ID to enter: ");
            scanf("%d", &writer_id);
            if (writer_id > 0 && writer_id <= num_writers)
            {
                pthread_create(&writers[writer_id - 1], NULL, writer, &writer_ids[writer_id - 1]);
            }
            else
            {
                printf("Invalid writer ID!\n");
            }
        }
        else if (choice == 2)
        {

            int reader_id;
            printf("Enter reader ID to enter: ");
            scanf("%d", &reader_id);
            if (reader_id > 0 && reader_id <= num_readers)
            {
                pthread_create(&readers[reader_id - 1], NULL, reader, &reader_ids[reader_id - 1]);
            }
            else
            {
                printf("Invalid reader ID!\n");
            }
        }
        else if (choice == 3)
        {
            // Exit program
            break;
        }
        else
        {
            printf("Invalid choice! Please try again.\n");
        }

        sleep(1);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}