#!/bin/bash


echo "First number"
read a

echo "Second number"
read b

orgA=$a
orgB=$b

echo "org vars    a: $a ; b: $b"

t=$a
a=$b
b=$t

echo "with temp var    a: $a ; b: $b"

# no extra var

orgB=`expr $orgA + $orgB`
orgA=`expr $orgB - $orgA`
orgB=`expr $orgB - $orgA`

echo "without temp var    a: $orgA ; b: $orgB"

