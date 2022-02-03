#!/bin/sh

a=$1
b=$2

res=`echo $a *\ $b | bc`
echo "Res: $res"
