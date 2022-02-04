#!/bin/bash

currHour=$(date +%H)
currDate=$(date +%x)
currTime=$(date +%X)

if [ "$currHour" -lt "12" ]; then
	echo "Good Morning"

elif [ "$currHour" -ge "12" -a "$currHour" -le "18" ]; then
	echo "Good Afternoon"

else
	echo "Good Night"
fi

echo "It's $currTime of $currDate"
