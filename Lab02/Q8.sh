#!/bin/bash

# marks=$(sed -ne 3,7p file.txt)
# echo "$marks"

m1=$(sed -ne '3,3p' file.txt)
m2=$(sed -ne '4,4p' file.txt)
m3=$(sed -ne '5,5p' file.txt)
m4=$(sed -ne '6,6p' file.txt)
m5=$(sed -ne '7,7p' file.txt)

echo "Hello, $(sed -ne '1,2p' file.txt)"

total=`expr $m1 + $m2 + $m3 + $m4 + $m5`
per=`echo $total \/ 5 | bc -l`
echo "Total: $total"
echo "Percentage: $per%"
