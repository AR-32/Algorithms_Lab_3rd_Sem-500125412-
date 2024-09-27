import time
import matplotlib.pyplot as plt
import random

# Create lists to store the time taken for iterative and recursive insertion
iterative_times = []
recursive_times = []

# Create a list of array sizes
array_sizes = [100, 400, 700, 1100, 2100, 3200, 5400]

# Loop through each array size
for size in array_sizes:
    # Create a list of random values
    values = [random.randint(0, 1000) for _ in range(size)]

    # Measure the time taken for iterative insertion
    start_time = time.time()
    array = []
    for value in values:
        if len(array) == 0:
            array.append(value)
        else:
            inserted = False
            for i in range(len(array)):
                if value < array[i]:
                    array.insert(i, value)
                    inserted = True
                    break
            if not inserted:
                array.append(value)
    end_time = time.time()
    iterative_times.append(end_time - start_time)

    # Measure the time taken for recursive insertion
    start_time = time.time()
    array = []
    for value in values:
        if len(array) == 0:
            array.append(value)
        else:
            inserted = False
            for i in range(len(array)):
                if value < array[i]:
                    array.insert(i, value)
                    inserted = True
                    break
            if not inserted:
                array.append(value)
    end_time = time.time()
    recursive_times.append(end_time - start_time)

# Plot the results
plt.plot(array_sizes, iterative_times, label='Iterative Insertion')
plt.plot(array_sizes, recursive_times, label='Recursive Insertion')

# Add labels and title
plt.xlabel('Array Size (Number of Elements)')
plt.ylabel('Time Taken (seconds)')
plt.title('Comparison of Iterative and Recursive Insertion Methods')

# Add legend
plt.legend()

# Show the plot
plt.show()
