#!/bin/bash
DV=1
FILE_NAME="testFig1.txt"
#gpu
R_MIN=$((16))
R_MAX=$((24))
p=$((16))
Q_MIN=$((7))
Q_MAX=$((9))
T_MAX=$((1))
u=$((2))

#cpu
# R_MIN=$((6))
# R_MAX=$((30))
# p=$((4))
# Q_MIN=$((7))
# Q_MAX=$((9))
# T_MAX=$((100))
# u=$((2))

for ((r=$R_MIN;r<=$R_MAX;r+=2));
do
    echo "start bash"
    ./ccs a $p $r $((2**$u))
    ./ccs b $p $r $((2**$u))		
    ./ccs c $p $r $((2**$u))
    ./ccs d $p $r $((2**$u))
    ./ccs e $p $r $((2**$u))
    ./ccs f $p $r $((2**$u))
    echo "created files for $r"
	
    # for ((q=3; q<=4;q+=1));
	# do
	# 	cd BarrettCUDA
	# 	echo "genuint compile"
	# 	./genuint $((2**$q/32)) > uintX.h

	# 	cd ..
	# 	echo "create index"
	# 	./createindex $((2**$q/8)) ./indexes.txt ./a ./b ./c ./d ./e ./f
		
	# 	cd BarrettCUDA
	# 	make barrett
	# 	echo "after barrett"
	# 	echo "q: 2^$q r: $r" >> $FILE_NAME
	# 	for ((v=0; v<$T_MAX; v+=1));
	# 	do				
	# 		./barrett ../val.22 ../out.row ../out.col >> $FILE_NAME	
	# 	done
	# 	cd ..
	# done
	
	for ((q=$Q_MIN; q<=$Q_MAX;q+=1));
	do
		cd BarrettCUDA

		./genuint $((2**$q/32)) > uintX.h

		cd ..
		echo "making batch"
		./createindex $((2**$q/8)) indexes.txt a b c d e f
		
		cd BarrettCUDA
		echo "making barrett"
		make barrett
		echo "after barrett"
		echo "q: 2^$q r: $r" >> $FILE_NAME
		for ((v =0; v<$T_MAX; v+=1));
		do				
			./barrett ../val.22 ../out.row ../out.col >> $FILE_NAME	
		done
		cd ..
	done
done
echo "Finished Script"