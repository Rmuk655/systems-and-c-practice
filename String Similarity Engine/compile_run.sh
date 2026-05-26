#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Incorrect usage of shell script. You must pass exactly two arguments, the first being the filename of your code, and the second, the number of test files."
    exit 1
fi

input_file=$1
num_testcases=$2

# Check if input file exists
if [ ! -f "$input_file" ] ; then
    echo "Input code must exist."
    exit 1
fi

# Check if gcc is installed
if command -v gcc &> /dev/null
then
    echo "gcc is installed"
else
    echo "Install GCC"
    echo "Exiting..."
    exit 1
fi

# Compile the input file
echo "Compiling..."
gcc $input_file -o $input_file.out
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi
echo "Compilation successful!"

./"$input_file.out" < "$num_testcases"

# Iterate over all test case IDs
for ((id=0; id<num_testcases; id++)); do
    input_file="input/input_${id}.txt"
    ref_file="output/output_${id}.txt"
    output_file="solution/output_${id}.txt"

    # Check if input and reference files exist
    if [ ! -f "$input_file" ]; then
        echo "Test case $id: $input_file does not exist."
        continue
    fi
    if [ ! -f "$ref_file" ]; then
        echo "Test case $id: $ref_file does not exist."
        echo "exiting..."
        exit 1
    fi

    # Compare the output with the reference file
    if cmp -s "$ref_file" "$output_file"; then
        echo "Test case $id passed!"
    else
        echo "Test case $id Failed. Showing mismatches..."
        diff -u "$output_file" "$ref_file" | grep -n '^@@'
    fi
done
