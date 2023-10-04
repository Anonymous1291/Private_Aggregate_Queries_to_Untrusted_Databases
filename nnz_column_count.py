import random
from collections import Counter
files = ['out_2.col', 'out_4.col','out_8.col','out_16.col','out_32.col','out_64.col','out_128.col','out_256.col', 'out_512.col', 'out_1024.col']
#files=['out.col', 'out.row', 'val.22']
#files=['out.col']
files1=['twitter_likeCount_333286_1004129.col', 'twitter_retweet_333286_1004129.col']

for k in files:
    with open(k) as f:
        first_line = f.readline()
    first_line = list(map(int,first_line.split()))
    first_element = first_line[0]
    first_line = first_line[1:]
    #print(first_line)
    zcount =0
    nnzcount = 0
    zero_column_indexes = []
    for i in range(0,len(first_line)-1):
        sub=first_line[i+1]-first_line[i]
        #print("sub: ", sub)
        #if i == 50000:break
        if sub > 0:
            nnzcount+=1
        else:
            zcount+=1
            zero_column_indexes.append(zcount)
            #print(i)
    print("-----")
    print(k,": ")
    print("non zero: ", nnzcount)
    print("zero count: ", zcount)
    #print("zero_column_index: ", zero_column_indexes)
    file=k+".txt"
    my_str = ', '.join(str(item) for item in zero_column_indexes)
    with open(file, 'w') as g:
        g.write(my_str)
    print("number of columns: ", len(first_line[1:]))
    total = nnzcount+zcount

    if total == first_element:
        print("True")
        print("NonZero percent: ", ((nnzcount/total)*100))
    else:
        print("False")

# file = 'out.col'
# file2 = 'twitter_sum_likes_users_25k_x_100k.col'
# file3 = 'twitter_count_nz_users_25k_x_100k.col'
# first_line=''
# j=file
# with open(j) as f:
#     first_line = f.readline()
# first_line = list(map(int,first_line.split()))
# first_element = first_line[0]
# first_line = first_line[1:]
# #print(first_line)
# zcount =0
# nnzcount = 0
# zero_column_indexes = []
# for i in range(0,len(first_line)-1):
#     sub=first_line[i+1]-first_line[i]
#     #print("sub: ", sub)
#     #if i == 50000:break
#     if sub > 0:
#         nnzcount+=1
#     else:
#         zcount+=1
#         zero_column_indexes.append(zcount)
#         #print(i)
# my_str = "{"
# my_str = ', '.join(str(item) for item in zero_column_indexes)
# my_str+="};"
# my_file = 'mimic_batch_file.txt'
# with open(my_file, 'w') as g:
#     g.write(my_str)
# print(j)
# print("non zero: ", nnzcount)
# print("zero count: ", zcount)
# #print("zero_column_index: ", zero_column_indexes)
# print("number of columns: ", len(first_line[1:]))
# total = nnzcount+zcount

# if total == first_element:
#     print("True")
#     print("NonZero percent: ", (nnzcount/total))
# else:
#     print("False")




# print("length of col line: ",len(first_line))
# nondup = list(dict.fromkeys(first_line))
# print("length of non-duplicated line: ",len(nondup))
# lengthNon = len(nondup)
# print(first_line[-1])
# skipset = (Counter(first_line)-Counter(set(first_line))).keys()
# print("length skipset: ", len(skipset))
# my_str = ','.join(str(item) for item in skipset)
# file = j+'_skiparray'
# with open(file, 'w') as g:
#     g.write(my_str)
    

# this_file = 'test1.col'
# with open(this_file) as f:
#     first_line = f.readline()
# first_line = list(map(int,first_line.split()))
# first_line = first_line[1:]
# print(this_file,":")
# print(len(first_line))
# nondup = list(dict.fromkeys(first_line))
# print(len(nondup))
# nondup = []
# first_line=[]


