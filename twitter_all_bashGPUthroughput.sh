#!/bin/bash
DV=1
FILE="twitter_all_final"
FILE_NAME="ResGPUThroughput_$FILE.txt"
string="twitter_likeCount_333286_1004129 twitter_retweet_333286_1004129"
#gpu
Q_MIN=$((7))
Q_MAX=$((7))
T_MAX=$((100))

#cpu
# R_MIN=$((6))
# R_MAX=$((30))
# p=$((4))
# Q_MIN=$((7))
# Q_MAX=$((9))
# T_MAX=$((100))
# u=$((2))


for ((q=$Q_MIN; q<=$Q_MAX;q+=1));
do
    cd BarrettCUDA

    ./genuint $((2**$q/32)) > uintX.h

    cd ..
    echo "making batch"
    ./createindex $((2**$q/8)) indexes.txt $string
    
    cd BarrettCUDA
    echo "making barrett"
    make barrett
    echo "after barrett"
    echo "q: 2^$q" >> $FILE_NAME
    for ((v =0; v<$T_MAX; v+=1));
    do				
        ./barrett ../val.22 ../out.row ../out.col >> $FILE_NAME	
    done
    cd ..
done

echo "Finished Script"
