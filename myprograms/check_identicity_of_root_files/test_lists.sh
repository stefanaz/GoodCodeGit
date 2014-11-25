#!/bin/sh
while read line
do
# echo $line

while read line2
do
if [ "$line" = "$line2" ]; 
then
echo "good $line"
fi
done < 05edata_cninfo.txt

done < 05edata.txt