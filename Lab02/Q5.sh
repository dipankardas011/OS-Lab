#!/bin/sh

echo "enter the username"

read usr

currUsr=$(whoami)

if [ "$usr" = "$currUsr" ]
then
	echo "Currently logged in"
else
	echo "Currently not logged in"
fi
