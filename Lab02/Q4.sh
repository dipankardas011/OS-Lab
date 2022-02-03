#!/bin/sh

echo "Enter 3 number"

read a
read b
read c

if [ $a -lt $b ]
then
	if [ $a -lt $c ]
	then
		echo "smallest: $a"
	else
		echo "smallest: $c"
	fi

else
	if [ $b -lt $c ]
	then
		echo "smallest: $b"
	else
		echo "smallest: $c"
	fi
fi

if [ $a -gt $b ]
then
	if [ $a -gt $c ]
	then
		echo "largest: $a"
	else
		echo "largest: $c"
	fi

else
	if [ $b -gt $c ]
	then
		echo "largest: $b"
	else
		echo "largest: $c"
	fi
fi

