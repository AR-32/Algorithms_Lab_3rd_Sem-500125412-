# Set the terminal type to PNG
set terminal pngcairo size 800,600

# Set the output file name
set output 'matrix_multiplication_times.png'

# Set the title and labels
set title "Matrix Multiplication Time Comparison"
set xlabel "Matrix Size (n x n)"
set ylabel "Time (seconds)"
set grid

# Set x and y range
set xrange [0:*]
set yrange [0:*]

# Plot the data
plot 'results.txt' using 1:2 with linespoints title 'Traditional Method', \
     '' using 1:3 with linespoints title 'Strassen Method'

# Close the output
set output