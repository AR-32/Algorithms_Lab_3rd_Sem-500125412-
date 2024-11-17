#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge two sorted arrays
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to implement merge sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Function to partition the array
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Function to implement quick sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int main() {
    int arr1[] = {12, 11, 13, 5, 6, 7};
    int arr2[] = {1, 2, 3, 4, 5, 6};
    int arr3[] = {6, 5, 4, 3, 2, 1};
    int arr4[] = {10, 9, 8, 7, 6, 5};
    int arr5[] = {5, 5, 5, 5, 5, 5};
    int arr6[] = {1, 3, 5, 7, 9, 11};

    int size = sizeof(arr1) / sizeof(arr1[0]);

    clock_t start, end;

    for (int i = 0; i < 6; i++) {
        int arr[6];
        for (int j = 0; j < size; j++) {
            switch (i) {
                case 0:
                    arr[j] = arr1[j];
                    break;
                case 1:
                    arr[j] = arr2[j];
                    break;
                case 2:
                    arr[j] = arr3[j];
                    break;
                case 3:
                    arr[j] = arr4[j];
                    break;
                case 4:
                    arr[j] = arr5[j];
                    break;
                case 5:
                    arr[j] = arr6[j];
                    break;
            }
        }

        printf("Array %d: ", i + 1);
        printArray(arr, size);

        start = clock();
        mergeSort(arr, 0, size - 1);
        end = clock();

        printf("Merge Sort: ");
        printArray(arr, size);
        printf("Time taken: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        quickSort(arr, 0, size - 1);
        end = clock();

        printf("Quick Sort: ");
        printArray(arr, size);
        printf("Time taken: %f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    }

    FILE* file = fopen("results.dat", "w");
    for (int i = 0; i < 4; i++) {
        fprintf(file, "%d %f %f\n", input_sizes[i], merge_sort_times[i], quick_sort_times[i]);
    }
    fclose(file);

    // Use gnuplot to plot the data
    system("gnuplot -persist -e \"set title 'Time Complexity of Merge Sort and Quick Sort'; set xlabel 'Input Size'; set ylabel 'Time (seconds)'; plot 'results.dat' using 1:2 with lines title 'Merge Sort', 'results.dat' using 1:3 with lines title 'Quick Sort'\"");

    return 0;
}    
