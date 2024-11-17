#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Dynamic Programming Approach
int knapsackDP(int W, int wt[], int val[], int n) {
    int i, w;
    int **K = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++)
        K[i] = (int *)malloc((W + 1) * sizeof(int));

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    int result = K[n][W];
    for (i = 0; i <= n; i++)
        free(K[i]);
    free(K);
    return result;
}

// Backtracking Approach
int maxProfit = 0;

void knapsackBacktrack(int W, int wt[], int val[], int n, int currentWeight, int currentValue, int index) {
    if (index == n) {
        if (currentValue > maxProfit)
            maxProfit = currentValue;
        return;
    }
    // Include the current item
    if (currentWeight + wt[index] <= W) {
        knapsackBacktrack(W, wt, val, n, currentWeight + wt[index], currentValue + val[index], index + 1);
    }
    // Exclude the current item
    knapsackBacktrack(W, wt, val, n, currentWeight, currentValue, index + 1);
}

int knapsackBacktracking(int W, int wt[], int val[], int n) {
    maxProfit = 0;
    knapsackBacktrack(W, wt, val, n, 0, 0, 0);
    return maxProfit;
}

// Branch & Bound Approach
typedef struct {
    int level;
    int profit;
    int weight;
    float bound;
} Node;

float bound(Node u, int W, int wt[], int val[], int n) {
    if (u.weight >= W) return 0; // No more weight capacity
    float profitBound = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;

    while (j < n && totalWeight + wt[j] <= W) {
        totalWeight += wt[j];
        profitBound += val[j];
        j++;
    }
    if (j < n) {
        profitBound += (W - totalWeight) * (float)val[j] / wt[j]; // Fractional part
    }
    return profitBound;
}

int knapsackBranchBound(int W, int wt[], int val[], int n) {
    Node *queue = (Node *)malloc(10000 * sizeof(Node)); // Adjust size as needed
    int front = 0, rear = 0;
    queue[rear++] = (Node){-1, 0, 0, 0.0}; // Start with root node

    int maxProfit = 0;

    while (front < rear) {
        Node current = queue[front++];

        if (current.level == n - 1) continue; // If last level, skip

        // Include the next item
        Node next;
        next.level = current.level + 1;
        next.weight = current.weight + wt[next.level];
        next.profit = current.profit + val[next.level];

        if (next.weight <= W) {
            if (next.profit > maxProfit) {
                maxProfit = next.profit; // Update maxProfit
            }
            next.bound = bound(next, W, wt, val, n);
            if (next.bound > maxProfit) {
                queue[rear++] = next; // Only add if bound is promising
            }
        }

        // Exclude the next item
        next.level = current.level + 1; // Move to next item
        next.weight = current.weight;
        next.profit = current.profit;
        next.bound = bound(next, W, wt, val, n);
        if (next.bound > maxProfit) {
            queue[rear++] = next; // Only add if bound is promising
        }
    }

    free(queue);
    return maxProfit;
}

// Main function to test all approaches
int main() {
    int W = 100; // Increased maximum weight of the knapsack
    int n = 10;  // Increased number of items
    int wt[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Weights of items
    int val[] = {60, 100, 120, 150, 200, 240, 300, 350, 400, 450}; // Values of items

    clock_t start, end;

    // Dynamic Programming
    start = clock();
    int dpResult = knapsackDP(W, wt, val, n);
    end = clock();
    printf("Dynamic Programming: %d (Time taken: %f seconds)\n", dpResult, (double)(end - start) / CLOCKS_PER_SEC);

    // Backtracking
    start = clock();
    int backtrackResult = knapsackBacktracking(W, wt, val, n);
    end = clock();
    printf("Backtracking: %d (Time taken: %f seconds)\n", backtrackResult, (double)(end - start) / CLOCKS_PER_SEC);

    // Branch & Bound
    start = clock();
    int branchBoundResult = knapsackBranchBound(W, wt, val, n);
    end = clock();
    printf("Branch & Bound: %d (Time taken: %f seconds)\n", branchBoundResult, (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
