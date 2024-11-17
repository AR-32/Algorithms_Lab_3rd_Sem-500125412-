#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity
struct Activity {
    int start;
    int finish;
};

// Function to compare two activities based on their finish time
int compare(const void *a, const void *b) {
    return ((struct Activity *)a)->finish - ((struct Activity *)b)->finish;
}

// Function to select activities
void selectActivities(struct Activity activities[], int n) {
    // Sort activities by finish time
    qsort(activities, n, sizeof(activities[0]), compare);

    printf("Selected Activities:\n");

    // The first activity always gets selected
    int lastSelected = 0;
    printf("Activity %d (Start: %d, Finish: %d)\n", lastSelected + 1, activities[lastSelected].start, activities[lastSelected].finish);

    // Consider the rest of the activities
    for (int i = 1; i < n; i++) {
        // If this activity starts after or when the last selected activity finishes
        if (activities[i].start >= activities[lastSelected].finish) {
            printf("Activity %d (Start: %d, Finish: %d)\n", i + 1, activities[i].start, activities[i].finish);
            lastSelected = i; // Update the last selected activity
        }
    }
}

int main() {
    // Example activities (start, finish)
    struct Activity activities[] = {
        {1, 3},
        {2, 5},
        {4, 6},
        {6, 7},
        {5, 8},
        {8, 9}
    };
    
    int n = sizeof(activities) / sizeof(activities[0]);

    selectActivities(activities, n);

    return 0;
}