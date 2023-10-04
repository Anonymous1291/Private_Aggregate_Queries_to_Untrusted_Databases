#include <atomic>
#include <chrono>
#include <ratio>
#include <fstream>

#include "barrett.h"
#include "uintX.h"

#define DEBUG true

#define THREADS_PER_BLOCK(n) (n >= 512 ? 512 : n)
#define NUM_BLOCKS(n) ((n + THREADS_PER_BLOCK(n) - 1) / THREADS_PER_BLOCK(n))

NTL_CLIENT

template <typename T>
void SpMV_ntl(NTL::vec_ZZ_p & response, const T * query, 
    const SparseMatrix<T> & matrix)
{
    for (int i = 0; i < matrix.ncols; i++)
    {
	response[i] = NTL::to_ZZ_p(0);
	for (int j = matrix.l_cols[i]; j < matrix.l_cols[i+1]; ++j)
	{
	    response[i] += to_ZZ_p(matrix.l_vals[j])
			 * to_ZZ_p(query[matrix.l_rows[j]]);
	}
    }
}

int main(){

    NTL::ZZ test = NTL::to_ZZ(88422157670822715692177757436365425828612815991736910012594334003137717389107);
    std::cout<<test;
    return 0;
}