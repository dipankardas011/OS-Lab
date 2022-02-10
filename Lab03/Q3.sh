#!/bin/bash

echo "Enter the length"

read L

echo "Enter the breadth"

read B

area=`echo $L \* $B | bc`

echo "Area: $area"
