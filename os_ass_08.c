#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

// Function prototypes
int fifo(int pages[], int n, int frames);
int lru(int pages[], int n, int frames);
int optimal(int pages[], int n, int frames);

int main() {
    int pages[MAX_PAGES];
    int n, frames;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    // Input the reference string
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Calculate page faults for each algorithm
    int fifo_faults = fifo(pages, n, frames);
    int lru_faults = lru(pages, n, frames);
    int optimal_faults = optimal(pages, n, frames);

    // Display results
    printf("\nPage Faults:\n");
    printf("FIFO: %d\n", fifo_faults);
    printf("LRU: %d\n", lru_faults);
    printf("Optimal: %d\n", optimal_faults);

    return 0;
}

// FIFO Page Replacement Algorithm
int fifo(int pages[], int n, int frames) {
    int page[frames];
    int page_faults = 0, index = 0, found, i;

    for (i = 0; i < frames; i++) {
        page[i] = -1; // Initialize frames
    }

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in frames
        for (int j = 0; j < frames; j++) {
            if (page[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // Page fault occurs
        if (!found) {
            page[index] = pages[i];
            index = (index + 1) % frames; // Move to the next frame
            page_faults++;
        }
    }
    return page_faults;
}

// LRU Page Replacement Algorithm
int lru(int pages[], int n, int frames) {
    int page[frames];
    int page_faults = 0, found, i, j, lru_index, lru_time[MAX_FRAMES] = {0};

    for (i = 0; i < frames; i++) {
        page[i] = -1; // Initialize frames
    }

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in frames
        for (j = 0; j < frames; j++) {
            if (page[j] == pages[i]) {
                found = 1;
                lru_time[j] = i; // Update the last used time
                break;
            }
        }

        // Page fault occurs
        if (!found) {
            // Find the LRU page
            lru_index = 0;
            for (j = 1; j < frames; j++) {
                if (lru_time[j] < lru_time[lru_index]) {
                    lru_index = j;
                }
            }
            page[lru_index] = pages[i]; // Replace the LRU page
            lru_time[lru_index] = i; // Update the last used time
            page_faults++;
        }
    }
    return page_faults;
}

// Optimal Page Replacement Algorithm
int optimal(int pages[], int n, int frames) {
    int page[frames];
    int page_faults = 0, found, i, j, k, farthest;

    for (i = 0; i < frames; i++) {
        page[i] = -1; // Initialize frames
    }

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in frames
        for (j = 0; j < frames; j++) {
            if (page[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // Page fault occurs
        if (!found) {
            // If there is an empty frame
            for (j = 0; j < frames; j++) {
                if (page[j] == -1) {
                    page[j] = pages[i];
                    page_faults++;
                    found = 1;
                    break;
                }
            }
            // If all frames are full, replace the optimal page
            if (!found) {
                farthest = -1;
                int index_to_replace = -1;

                // Find the page that will not be used for the longest period of time
                for (j = 0; j < frames; j++) {
                    for (k = i + 1; k < n; k++) {
                        if (page[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                index_to_replace = j;
                            }
                            break;
                        }
                    }
                    // If the page is not found in the future reference string, replace it
                    if (k == n) {
                        index_to_replace = j;
                        break;
                    }
                }
                page[index_to_replace] = pages[i]; // Replace the optimal page
                page_faults++;
            }
        }
    }
    return page_faults;
}