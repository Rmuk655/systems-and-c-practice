#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Incorrect usage of shell script. You must pass exactly one argument, i.e., the filename of your code."
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


test(){
  testNo=$1
  testcase=$2
  resActual=$3
  output=$4
  binary=$5
  cat $testcase | ./"$binary" > $output
  res=`diff -i $resActual expenses.txt | wc -l`
  if [ $res -eq 0 ]
  then
  	echo "TESTCASE-$testNo PASSED"
  else
  	echo "TESTCASE-$testNo FAILED"
  fi
}


test 1 input/input_1.txt output/output_1.txt runtime/r1.txt "$input_file.out"
test 2 input/input_2.txt output/output_2.txt runtime/r2.txt "$input_file.out"