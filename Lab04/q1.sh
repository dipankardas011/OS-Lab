#!/bin/bash

echo enter the number

read num


newNum=0

while [ $num -gt 0 ]
do
	newNum=$(( $newNum * 10 + $num % 10 ))
	num=$(( $num / 10))
done

echo new number $newNum
