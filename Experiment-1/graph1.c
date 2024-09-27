#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to insert an element into a sorted array iteratively
void iterative_insertion(int* array, int* size, int value) {
    int i;
    for (i = 0; i < *size; i++) {
        if (value < array[i]) {
            // Shift elements to the right
            for (int j = *size; j > i; j--) {
                array[j] = array[j - 1];
            }
            array[i] = value;
            (*size)++;
            return;
        }
    }
    array[*size] = value;
    (*size)++;
}

// Function to insert an element into a sorted array recursively
void recursive_insertion(int* array, int* size, int value, int index) {
    if (index == *size) {
        array[*size] = value;
        (*size)++;
        return;
    }
    if (value < array[index]) {
        // Shift elements to the right
        for (int i = *size; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        (*size)++;
        return;
    }
    recursive_insertion(array, size, value, index + 1);
}

int main() {
    // Create lists to store the time taken for iterative and recursive insertion
    double iterative_times[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double recursive_times[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    // Create a list of array sizes
    int array_sizes[] = {100, 400, 700, 1100, 2100, 3200, 5400};

    // Loop through each array size
    for (int i = 0; i < 7; i++) {
        int size = array_sizes[i];
        int* values = (int*)malloc(size * sizeof(int));
        int* array = (int*)malloc((size + 1) * sizeof(int));

        // Generate random values
        for (int j = 0; j < size; j++) {
            values[j] = rand() % 1000;
        }

        // Measure the time taken for iterative insertion
        clock_t start_time = clock();
        int array_size = 0;
        for (int j = 0; j < size; j++) {
            iterative_insertion(array, &array_size, values[j]);
        }
        clock_t end_time = clock();
        iterative_times[i] = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        // Measure the time taken for recursive insertion
        start_time = clock();
        array_size = 0;
        for (int j = 0; j < size; j++) {
            recursive_insertion(array, &array_size, values[j], 0);
        }
        end_time = clock();
        recursive_times[i] = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        free(values);
        free(array);
    }

    // Write the results to a file
    FILE* file = fopen("results.dat", "w");
    for (int i = 0; i < 7; i++) {
        fprintf(file, "%d %f %f\n", array_sizes[i], iterative_times[i], recursive_times[i]);
    }
    fclose(file);

    // Use gnuplot to plot the data
    system("gnuplot -persist -e \"set title 'Comparison of Iterative and Recursive Insertion Methods'; set xlabel 'Array Size (Number of Elements)'; set ylabel 'Time Taken (seconds)'; plot 'results.dat' using 1:2 with lines title 'Iterative Insertion', 'results.dat' using 1:3 with lines title 'Recursive Insertion'\"");

    return 0;
}