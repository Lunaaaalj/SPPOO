#!/bin/bash

# Compile the program
g++ -std=c++17 -Wall -Wextra -o main main.cpp

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Compilation successful."

# Run the program with optional test input
if [ -f "test_input.txt" ]; then
    echo "Running program with test_input.txt..."
    ./main < test_input.txt
else
    echo "Running program (interactive mode)..."
    ./main
fi