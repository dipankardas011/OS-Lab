#!/bin/bash

echo "Enter first number"
read A

echo "Enter second number"
read B

# addition
resA=`echo $A + $B | bc`

# subtraction
resS=`echo $A - $B | bc`


# multiplication
resM=`echo $A \* $B | bc`

# division
resD=`echo $A \/ $B | bc`

echo "Addition: $resA"
echo "Subtraction: $resS"
echo "Multiplication: $resM"
echo "Division: $resD"

