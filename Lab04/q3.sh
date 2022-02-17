#!/bin/bash

a=$1
b=$2

res=0

if [ $(( $a % $b )) -eq 0 ]; then
	res=$(( $a / $b ))
elif [ $(( $b % 5 )) -eq 0 ]; then
	res=$(( $a * $b ))
elif [ $a -gt $b ]; then
	res=$(( $a - $b ))
else
	res=$(( $a + $b ))
fi

echo res: $res
