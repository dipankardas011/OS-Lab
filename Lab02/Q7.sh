#!/bin/bash

echo "Enter the marks for a subject"

read marks

if [ $marks -ge 90 ]; then
	echo "Grade: 'O'"
elif [ $marks -ge 80 ]; then
	echo "Grade: 'A'"
elif [ $marks -ge 70 ]; then
	echo "Grade: 'B'"
elif [ $marks -ge 60 ]; then
	echo "Grade: 'C'"
elif [ $marks -ge 50 ]; then
	echo "Grade: 'D'"
elif [ $marks -ge 40 ]; then
	echo "Grade: 'E'"
else
	echo "Grade: 'F'"
fi
