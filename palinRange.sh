#!/bin/bash

# count the number os palindrome numbers present b/w 10 - 500

count=0

iter=10

palin() {
	left=0
	str=$1
	right=$(( ${#str} - 1 ))
	while [ $left -lt $right ]
	do
		if [ ${str:left:1} != ${str:right:1} ]; then
			return 0
		fi
		left=$(( $left + 1))
		right=$(( $right - 1 ))
	done
	return 1 
}


while [ $iter -lt 500 ]
do
	palin $iter

 if [ $? -eq "1" ]; then
		echo "Palindrome: $iter"
	fi

	iter=$(($iter + 1))
done
