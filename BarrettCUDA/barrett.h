

#ifndef __BARRETT_H_
#define __BARRETT_H_

#include <NTL/vec_vec_ZZ_p.h>

#include "uint.h"
#include "gf2e.h"

// for uintX
__constant__ void * d_modulus;
__constant__ void * d_mu;
__constant__ void * d_subtrahends;
// for GF28
__constant__ GF28_Element * d_GF28_mult_table[256];
// for GF216
__constant__ GF216_Element * d_GF216_exp_table;
__constant__ GF216_Element * d_GF216_log_table;

template<typename T>
struct BarrettParams
{
    T * d_modulus;
    uintXp<T> * d_mu;
    T * d_subtrahends;
    NTL::ZZ l_modulus;
    NTL::ZZ l_mu;
    NTL::vec_ZZ l_subtrahends;
};

template<typename T>
struct SparseMatrix
{
    uint nvals;
    uint nrows;
    uint ncols;
    T * d_vals;
    uint * d_cols;
    uint * d_rows;
    T * l_vals;
    uint * l_cols;
    uint * l_rows;
};

// template wizardry to support function specialization
template <typename T, int U>
struct _SpMV_specializer
{
    static __device__ void device_SpMV(T * response, const T * query,
	const uint nvals, const T * vals, const uint ncols, const uint * cols,
	const uint * rows);
};

template <typename T, int U>
struct _truncateBits_specializer
{
    static void truncateBits( T * vals, const  NTL::ZZ tmp);
};

template <typename T, int U>
struct _maxOverflow_specializer
{
    static uint maxOverflow(const uint ncols, const uint * cols, const uint nvals, const GF216_Element * vals, NTL::ZZ & modulus);
};


template <typename T>
__global__ void SpMV_kernel(T * response, const T * query, const uint nvals,
    const T * vals, const uint ncols, const uint * cols, const uint * rows)
{
    _SpMV_specializer<T,0>::device_SpMV(response, query, nvals, vals, ncols,
	cols, rows);
}

template <typename T>
void initMatrix(const char * valfile, const char * rowfile,
    const char * colfile, NTL::ZZ & modulus, struct SparseMatrix<T> & matrix,
    uint & max_overflow);

template <typename T>
void freeMatrix(struct SparseMatrix<T> & matrix);

template <typename T>
void initBarrett(const NTL::ZZ & modulus_zz, struct BarrettParams<T> & barrett,
    const uint max_overflow);

template<typename T>
void freeBarrett(struct BarrettParams<T> & barrett);

// Adapted from: http://stackoverflow.com/questions/14038589/what-is-the-canonical-way-to-check-for-errors-using-the-cuda-runtime-api
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char * file, int line)
{
    if (code != cudaSuccess) 
    {
	fprintf(stderr,"Error: %s (line %d of %s)\n", cudaGetErrorString(code),
	    line, file);
	exit(-1);
    }
}

void initGF28();
void freeGF28();
void initGF216();
void freeGF216();

#endif
