#!/bin/bash

# assuming 3 digit number
echo "Enter a 3 digit number"

read number

sum=0

digit=`expr $number \% 10`
sum=`expr $sum + $digit`
number=`expr $number / 10`


digit=`expr $number \% 10`
sum=`expr $sum + $digit`
number=`expr $number \/ 10`


digit=`expr $number \% 10`
sum=`expr $sum + $digit`
number=`expr $number \/ 10`


echo "Digit Sum: $sum"