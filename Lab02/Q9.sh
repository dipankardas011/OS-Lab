#!/bin/bash

echo "Enter the fileName"

read fname

if [ -f "$fname" ]; then
	echo "File Exist"
	echo "Contents:"
	txt=`cut -d " " -f 5 $fname | sort`
	echo "$txt"

else
	echo "File Does not exist"
fi

