import time
import matplotlib.pyplot as plt
import sys

sys.setrecursionlimit(10000)

def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    return merge(left, right)

def merge(left, right):
    result = []
    i, j = 0, 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    result.extend(left[i:])
    result.extend(right[j:])

    return result

def quick_sort(arr):
    if len(arr) <= 1:
        return arr

    pivot = arr[0]
    less = [x for x in arr[1:] if x <= pivot]
    greater = [x for x in arr[1:] if x > pivot]

    return quick_sort(less) + [pivot] + quick_sort(greater)

def iterative_merge_sort(arr):
    if len(arr) <= 1:
        return arr

    width = 1
    while width < len(arr):
        for i in range(0, len(arr), 2 * width):
            left = arr[i:i + width]
            right = arr[i + width:i + 2 * width]
            arr[i:i + 2 * width] = merge(left, right)
        width *= 2

    return arr

input_sizes = [100, 200, 400, 800, 1600, 3200, 6400]
merge_sort_times = []
quick_sort_times = []

input_arrays = [
    [12, 11, 13, 5, 6, 7] * 16,
    [1, 2, 3, 4, 5, 6] * 32,
    [6, 5, 4, 3, 2, 1] * 64,
    [10, 9, 8, 7, 6, 5] * 128,
    [5, 5, 5, 5, 5, 5] * 256,
    [1, 3, 5, 7, 9, 11] * 512,
    [12, 11, 13, 5, 6, 7] * 1024
]

for i, arr in enumerate(input_arrays):
    start = time.time()
    iterative_merge_sort(arr)
    end = time.time()
    merge_sort_times.append(end - start)

    start = time.time()
    quick_sort(arr)
    end = time.time()
    quick_sort_times.append(end - start)

plt.plot(input_sizes, merge_sort_times, label='Merge Sort')
plt.plot(input_sizes, quick_sort_times, label='Quick Sort')
plt.xlabel('Input Size')
plt.ylabel('Time (seconds)')
plt.title('Time Complexity of Merge Sort and Quick Sort')
plt.legend()
plt.show()
