#!/bin/bash

echo Enter the string

read str


left=0
right=$(( ${#str} - 1 ))

#echo left $left right $right

# echo ${str:4:1}

while [ $left -lt $right ]
do
	if [ ${str:left:1} != ${str:right:1} ]; then
		echo Not a palnidrome
		exit 0
	fi

	left=$(( $left + 1))
	right=$(( $right - 1 ))
done

echo it is palindrome

