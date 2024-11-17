#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Naive String Matching Algorithm
void naiveSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++)
            if (text[i + j] != pattern[j])
                break;
        if (j == m)
            printf("Naive: Pattern found at index %d\n", i);
    }
}

// Rabin-Karp Algorithm
void rabinKarp(char *text, char *pattern, int d, int q) {
    int n = strlen(text);
    int m = strlen(pattern);
    int h = 1; // d^(m-1) % q
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j;
            for (j = 0; j < m; j++)
                if (text[i + j] != pattern[j])
                    break;
            if (j == m)
                printf("Rabin-Karp: Pattern found at index %d\n", i);
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t += q;
        }
    }
}

// KMP Algorithm
void KMPSearch(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    
    // Create LPS array
    int *lps = (int *)malloc(m * sizeof(int));
    int j = 0; // length of previous longest prefix suffix
    int i = 1;
    
    // Preprocess the pattern to create LPS array
    lps[0] = 0;
    while (i < m) {
        if (pattern[i] == pattern[j]) {
            j++;
            lps[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    // Search for the pattern
    i = 0; // index for text
    j = 0; // index for pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            printf("K MP: Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    free(lps);
}

int main() {
    char text[] = "ABABDABACDABABCABABCBADABCDABAB";
    char pattern[] = "ABAB";
    int d = 26; // Number of characters in the input alphabet
    int q = 31; // A prime number for hashing

    // Open file to save results
    FILE* file = fopen("result1.dat", "w");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    // Timing Naive Search
    clock_t start = clock();
    naiveSearch(text, pattern);
    clock_t end = clock();
    double time_spent_naive = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(file, "Naive %f\n", time_spent_naive);

    // Timing Rabin-Karp
    start = clock();
    rabinKarp(text, pattern, d, q);
    end = clock();
    double time_spent_rabin = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(file, "Rabin-Karp %f\n", time_spent_rabin);

    // Timing KMP
    start = clock();
    KMPSearch(text, pattern);
    end = clock();
    double time_spent_kmp = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(file, "KMP %f\n", time_spent_kmp);

    // Close the file
    fclose(file);
    return 0;
}