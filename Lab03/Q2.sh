#!/bin/bash

echo "Enter seconds"
read seconds

hrs=`expr $seconds \/ 3600`

seconds=`expr $seconds \% 3600`

mins=`expr $seconds \/ 60`

seconds=`expr $seconds \% 60`


echo "$hrs : $mins : $seconds"
