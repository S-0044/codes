#include <stdio.h>
#include <stdlib.h>

// Function for SSTF (Shortest Seek Time First)
int findShortestSeekTime(int head, int *requests, int n, int *visited) {
    int min = 1e9, index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int distance = abs(requests[i] - head);
            if (distance < min) {
                min = distance;
                index = i;
            }
        }
    }
    return index;
}

void sstf(int *requests, int n, int head) {
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    int totalSeekTime = 0;
    printf("SSTF Disk Scheduling Order:\n");
    for (int i = 0; i < n; i++) {
        int index = findShortestSeekTime(head, requests, n, visited);
        visited[index] = 1;
        printf("%d ", requests[index]);
        totalSeekTime += abs(requests[index] - head);
        head = requests[index];
    }
    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

// Function for SCAN 
void scan(int *requests, int n, int head, int disk_size) {
    int totalSeekTime = 0;
    printf("SCAN Disk Scheduling Order:\n");

    
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }

 
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            for (int j = i; j < n; j++) {
                printf("%d ", requests[j]);
                totalSeekTime += abs(requests[j] - head);
                head = requests[j];
            }
            totalSeekTime += abs(disk_size - 1 - head); 
            head = disk_size - 1;
            break;
        }
    }

    
    for (int i = n - 1; i >= 0; i--) {
        if (requests[i] < head) {
            printf("%d ", requests[i]);
            totalSeekTime += abs(requests[i] - head);
            head = requests[i];
        }
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

// Function for C-LOOK (Circular LOOK)
void clook(int *requests, int n, int head) {
    int totalSeekTime = 0;
    printf("C-LOOK Disk Scheduling Order:\n");

  
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }


    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            for (int j = i; j < n; j++) {
                printf("%d ", requests[j]);
                totalSeekTime += abs(requests[j] - head);
                head = requests[j];
            }
            
            totalSeekTime += abs(requests[0] - head);
            head = requests[0];
            break;
        }
    }

  
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            printf("%d ", requests[i]);
            totalSeekTime += abs(requests[i] - head);
            head = requests[i];
        }
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

int main() {
    int n, disk_size, choice;
    int head = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter the total disk size (for SCAN and C-LOOK): ");
    scanf("%d", &disk_size);

   
    printf("\nChoose Disk Scheduling Algorithm:\n");
    printf("1. SSTF\n");
    printf("2. SCAN\n");
    printf("3. C-LOOK\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sstf(requests, n, head);
            break;
        case 2:
            scan(requests, n, head, disk_size);
            break;
        case 3:
            clook(requests, n, head);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

return 0;
}