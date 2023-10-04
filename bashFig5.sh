#!/bin/bash
DV=1
FILE_NAME="test_Fig5.txt"
#gpu
r=$((16))
p=$((14))
u=$((4))
q=$((8))
t=$((2))
files_min=$((1))
files=$((10))
prev=$((0))

#cpu
# r=$((8))
# p=$((4))
# u=$((4))
# q=$((6))
# t=$((100))
# files_min=$((1))
# files=$((8))
# prev=$((0))


for ((f=$files_min; f<=$files;f+=1));
do
	echo "start"
    
    for((i=0;i<2**$f;i+=1));
    do
        ./ccs $i $p $r $((2**$u))
        string+=$i" "
    done

    echo "files: $string" >> $FILE_NAME
    for ((v =0; v<$t; v+=1));
    do				
        ./createindex $((2**$q/8)) indexes.txt $string >> $FILE_NAME
        
    done
    mv -v val.22 "val_$i.22"

    for((k=0;k<2**$f;k+=1));
    do
        file1=$k".row"
        file2=$k".col"
        rm $file1
        rm $file2
    done
    unset string
    echo "removed $(($k+1)) files"
    mv -v out.col "out_$i.col"
    echo "done with set"
done
echo "Finished Script"