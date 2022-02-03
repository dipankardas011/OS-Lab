#!/bin/sh

num1=10
read a
num2=20

res=`expr $num1 + $num2`

res1=`echo $num1 + $a | bc`

echo "Number1: $num1"
echo "Number2: $num2"
echo "a: $a"
echo "res: $res"
echo "res1: $res1"


echo "value of arg[0]: $0"
echo "value of arg[1]: $1"
