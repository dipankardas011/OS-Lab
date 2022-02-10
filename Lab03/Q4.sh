#!/bin/bash

# assuming 3 digit number
echo "Enter a 3 digit number"

read number

sum=0

for (( iter=$number ; iter > 0 ; ))
do
	digit=`expr $iter \% 10`
	sum=`expr $sum + $digit`
	iter=`expr $iter \/ 10`
done

echo "Digit Sum: $sum"
