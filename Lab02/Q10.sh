#!/bin/bash

echo "Enter [ 1 ] List files"
echo "Enter [ 2 ] create dir"
echo "Enter [ 3 ] change dir"
echo "Enter [ 4 ] remove dir"
echo "Enter [ 5 ] create file"
echo "Enter [ 6 ] copy file"
echo "Enter [ 7 ] remove file"

read choice

if [ $choice -eq 1 ]; then
# assuming it is the curr dir
	ls -la

elif [ $choice -eq 2 ]; then
	echo "Enter the directory name"
	read dirN
	`mkdir $dirN`
	ls -la

elif [ $choice -eq 3 ]; then
	echo "Enter the directory name"
	read dirN
	cd $dirN
	pwd

elif [ $choice -eq 4 ]; then
	echo "Enter the directory name"
	read dirN
	`rm -Ri $dirN`
	ls -la

elif [ $choice -eq 5 ]; then
	echo "Enter the file name"
	read fileN
	`touch $fileN`		
	ls -l

elif [ $choice -eq 6 ]; then
	echo "Enter the file name"
	read fileN
	`cp -v $fileN copy_$fileN`
	ls -l
elif [ $choice -eq 7 ]; then
	echo "Enter the file name"
	read fileN
	`rm -i $fileN`
	ls -l
else
	echo "Wrong Choice"
fi
