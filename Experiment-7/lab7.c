#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEMS 100 // Reduced size for better performance

// Structure to represent an item
typedef struct {
    int value;
    int weight;
} Item;

// Function to compare items based on value-to-weight ratio (used in greedy approach)
int compare(const void *a, const void *b) {
    double ratioA = (double)((Item *)a)->value / ((Item *)a)->weight;
    double ratioB = (double)((Item *)b)->value / ((Item *)b)->weight;
    return (ratioB - ratioA > 0) ? 1 : -1; // Sort in descending order
}

// Greedy approach to 0/1 Knapsack (not optimal)
int greedyKnapsack(Item items[], int n, int capacity) {
    qsort(items, n, sizeof(Item), compare); // Sort items by value-to-weight ratio

    int totalValue = 0;
    for (int i = 0; i < n; i++) {
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        }
    }
    return totalValue;
}

// Dynamic programming approach to 0/1 Knapsack
int dynamicProgrammingKnapsack(Item items[], int n, int capacity) {
    // Allocate memory for the DP table
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
    }

    // Initialize the DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base case
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w])
                           ? items[i - 1].value + dp[i - 1][w - items[i - 1].weight]
                           : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][capacity]; // Maximum value that can be obtained

    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Create a larger dataset for better timing accuracy
    Item items[MAX_ITEMS];
    int n = MAX_ITEMS;
    int capacity = 5000;

    // Initialize items with random values and weights
    for (int i = 0; i < n; i++) {
        items[i].value = rand() % 100 + 1;  // Random value between 1 and 100
        items[i].weight = rand() % 50 + 1;  // Random weight between 1 and 50
    }

    // Measure time for the greedy approach
    clock_t start = clock();
    int greedyValue = greedyKnapsack(items, n, capacity);
    clock_t end = clock();
    double greedyTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Measure time for the dynamic programming approach
    start = clock();
    int dpValue = dynamicProgrammingKnapsack(items, n, capacity);
    end = clock();
    double dpTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the results
    printf("Greedy Approach: Maximum value = %d\n", greedyValue);
    printf("Time taken by Greedy Approach: %f seconds\n", greedyTime);

    printf("Dynamic Programming Approach: Maximum value = %d\n", dpValue);
    printf("Time taken by Dynamic Programming Approach: %f seconds\n", dpTime);

    return 0;
}