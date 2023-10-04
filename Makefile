

CXXFLAGS=-Wall -g -O2 -pedantic -std=c++11
NVCCFLAGS=-std=c++11 -D_MWAITXINTRIN_H_INCLUDED -D_FORCE_INLINES -D__STRICT_ANSI__

queryindex: vectormatrixcompcudactreams.cu
	nvcc $(NVCCFLAGS) -o $@ $^

createindex: createindex.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ -lntl -lgmp -lpthread -L/usr/local/lib -I/usr/local/lib

createindex_gf28: createindex_gf28.cc 
	$(CXX) $(CXXFLAGS) -o $@ $^ gf2e.cc -L/usr/local/lib -I/usr/local/lib

clean:
	-rm -f createindex queryindex
