#!/bin/bash
DV=1
FILE_NAME="test_Fig3.txt"
#gpu
P_MIN=$((1))
P_MAX=$((17))
r=$((20))

Q_MIN=$((7))
Q_MAX=$((9))
T_MAX=$((2))
u=$((4))

# cpu
# P_MIN=$((1))
# P_MAX=$((12))
# r=$((12))

# Q_MIN=$((7))
# Q_MAX=$((9))
# T_MAX=$((100))
# u=$((2))

for ((p=$P_MIN;p<=$P_MAX;p+=2));
do
    echo "start bash"
    ./ccs a $p $r $((2**$u))
    ./ccs b $p $r $((2**$u))		
    ./ccs c $p $r $((2**$u))
    ./ccs d $p $r $((2**$u))
    ./ccs e $p $r $((2**$u))
    ./ccs f $p $r $((2**$u))
    echo "created files for $p"
	
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

		./genuint $((2**$q/32)) > uintX.h #./genuint 4 > uintX.h

		cd ..
		echo "making batch"
		./createindex $((2**$q/8)) indexes.txt a b c d e f
		
		cd BarrettCUDA
		echo "making barrett"
		make barrett
		echo "after barrett"
		echo "q: 2^$q p: $p" >> $FILE_NAME
		for ((v =0; v<$T_MAX; v+=1));
		do				
			./barrett ../val.22 ../out.row ../out.col >> $FILE_NAME	
		done
		cd ..
	done
done
echo "Finished Script"