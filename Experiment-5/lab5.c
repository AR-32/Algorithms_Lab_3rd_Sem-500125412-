#include <stdio.h>
#include <limits.h>
#include <time.h> // Include time.h for clock()

#define MAX 100

// Function to print the optimal parenthesization
void printOptimalParenthesis(int s[MAX][MAX], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Function to compute the minimum cost of matrix multiplication
int matrixChainOrder(int p[], int n) {
    int m[MAX][MAX]; // Cost table
    int s[MAX][MAX]; // Split table

    // m[i][i] = 0; cost is zero when multiplying one matrix
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // l is the chain length
    for (int l = 2; l <= n; l++) { // l = chain length
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1; // Ending index of chain
            m[i][j] = INT_MAX; // Initialize to a large number

            // Try all possible splits
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                // Print the calculation for this split
                printf("Calculating cost for matrices from A%d to A%d\n", i, j);
                printf("Split at A%d: Cost = %d\n", k, q);

                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k; // Store the split point
                }
            }
            printf("Minimum cost for multiplying A%d to A%d is %d\n\n", i, j, m[i][j]);
        }
    }

    printf("Optimal Parenthesization is: ");
    printOptimalParenthesis(s, 1, n);
    printf("\nMinimum number of multiplications is %d\n", m[1][n]);
    
    return m[1][n]; // Return the minimum cost
}

int main() {
    // Example dimensions of matrices
    int p[] = {1, 2, 3, 4}; // Dimensions for 6 matrices
    int n = sizeof(p) / sizeof(p[0]) - 1; // Number of matrices

    // Start time measurement
    clock_t start = clock();

    int minCost = matrixChainOrder(p, n);

    // End time measurement
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate time in seconds

    printf("Time taken to compute optimal parenthesization: %f seconds\n", time_taken);

    return 0;
}