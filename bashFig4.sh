#!/bin/bash
DV=1
FILE_NAME="test_Fig4.txt"
#gpu
R_MIN=$((14))
r=$((16))
p=$((14))
U_MIN=$((1))
U_MAX=$((9))
Q_MIN=$((8))
Q_MAX=$((8))
T_MAX=$((2))

#cpu
# R_MIN=$((14))
# r=$((8))
# p=$((4))
# U_MIN=$((1))
# U_MAX=$((11))
# Q_MIN=$((8))
# Q_MAX=$((8))
# T_MAX=$((100))
for ((u=$U_MIN; u<=$U_MAX;u+=1));
do
	echo "start"

    ./ccs a $p $r $((2**$u))
    ./ccs b $p $r $((2**$u))		
    ./ccs c $p $r $((2**$u))
    ./ccs d $p $r $((2**$u))
    ./ccs e $p $r $((2**$u))
    ./ccs f $p $r $((2**$u))
    cd BarrettCUDA

    ./genuint $((2**$Q_MAX/32)) > uintX.h

    cd ..
    ./createindex $((2**$Q_MAX/8)) indexes.txt a b c d e f
    
    cd BarrettCUDA
    make barrett
    echo "after barrett"
    echo "u: $u r: $r" >> $FILE_NAME
    for ((v =0; v<$T_MAX; v+=1));
    do				
        ./barrett ../val.22 ../out.row ../out.col >> $FILE_NAME	
    done
    cd ..

done
echo "Finished Script"