#!/bin/bash
DV=1
string="twitter_filtered"
FILE_NAME="BatchRes_$string.txt"
Q_MIN=$((7))
Q_MAX=$((7))
T_MAX=$((1))
files="twitter_filtered_likeCount_2714_1004129 twitter_filtered_retweet_2714_1004129"

for ((q=$Q_MIN;q<=$Q_MAX;q+=1));
do
    echo "start bash"
    echo "making batch"
    echo "q=2^$q in miliseconds:" >> $FILE_NAME
    for((t=0;t<$T_MAX;t+=1));
    do
        ./createindex $((2**$q/8)) indexes.txt $files >> $FILE_NAME
    done
    echo "trails done for 2^$q"
    mv -v out.col out_$string.col
done
echo "Finished Script"
