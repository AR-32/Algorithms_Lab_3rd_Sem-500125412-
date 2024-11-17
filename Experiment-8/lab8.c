#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int subsetSum(int set[], int n, int sum) {
    // Create a 2D array to store the results of subproblems
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((sum + 1) * sizeof(int));
    }

    // Initialize the first column, as a sum of 0 can always be achieved with an empty set
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1; // True
    }

    // Fill the subset sum table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            // If the current element is greater than the sum, we cannot include it
            if (set[i - 1] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                // Check if we can get the sum by including or excluding the current element
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
            }
        }
    }

    int result = dp[n][sum]; // The result will be in the last cell of the table

    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result; // Return 1 if subset with given sum exists, otherwise 0
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Example set and target sum
    int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    int n = sizeof(set) / sizeof(set[0]);

    // Measure time for the subset sum algorithm
    clock_t start = clock();
    int result = subsetSum(set, n, sum);
    clock_t end = clock();
    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Output the result
    if (result) {
        printf("Found a subset with the given sum %d.\n", sum);
    } else {
        printf("No subset with the given sum %d exists.\n", sum);
    }
    printf("Time taken: %.6f seconds\n", timeTaken);

    return 0;
}