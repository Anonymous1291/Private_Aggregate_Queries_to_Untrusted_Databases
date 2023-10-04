#python run.py 8 10 5000 10000 13

#ran diff. nstreams:
#nstreams = 1: 32 SpMV,  0.03125s
#nstreams = 4: 128 SpMV, 0.0078125s
#nstreams = 14:448 SpMV, 0.0022321s
#nstreams = 16:512 SpMV, 0.00195313s
#nstreams = 18:576 SpMV, 0.0017361s
#nstreams = 20:640 SpMV, 0.0015625s
import os
import sys

if sys.argv[1] == '-h':
    print("python run.py $p $r $num_blocks $block_size $val.<#>")
else:
    p = sys.argv[1]
    r = sys.argv[2]
    num_blocks = sys.argv[3]
    block_size = sys.argv[4]

    # os.system("g++ -std=c++11 -o ccs ../createCCSfiles.cc -lntl -lpthread -lgmp")
    # os.system("mv ccs ..")

    os.system("../ccs a " + str(p) + " " + str(r) + " 1")
    os.system("../ccs b " + str(p) + " " + str(r) + " 1")
    os.system("../ccs c " + str(p) + " " + str(r) + " 1")
    os.system("../ccs d " + str(p) + " " + str(r) + " 1")
    os.system("mv *.row ..")
    os.system("mv *.col ..")

    print("Start Creating Indexes...")
    os.system("../createindex 64 ../indexes.txt ../a ../b ../c ../d")
    os.system("mv val.* ..")
    print("Indexes Created")

    os.system("mv out.* ..")
 
    os.system("make barrett")
    os.system("./barrett ../val."+ str(sys.argv[5]) +" ../out.row ../out.col")

