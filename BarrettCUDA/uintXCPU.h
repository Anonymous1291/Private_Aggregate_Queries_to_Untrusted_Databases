// This file was generated by BarrettCUDA v0.1.
// 
// BarrettCUDA is a fast(ish) implementation of finite field sparse
// matrix-vector multiplication (SpMV) for Nvidia GPU devices, written
// in CUDA C++. BarrettCUDA supports SpMV for matrices expressed in
// the 'compressed column storage' (CCS) sparse matrix representation
// over (i) the field of integers modulo an arbitrary multi-precision
// prime, or (ii) either of the binary fields GF(2^8) or GF(2^16).
// 
// 
// BarrettCUDA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// 
// BarrettCUDA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with BarrettCUDA. If not, see <http://www.gnu.org/licenses/>.

#ifndef __UINT_64_H
#define __UINT_64_H
#include "uintCPU.h"

#ifndef __UINTX__
#define __UINTX__
    typedef uint64 uintX;
#endif

#define LIMBS_PER_UINTX 2

static inline NTL::ZZ to_ZZ(const uint64 & n)
{
    return to_ZZ<uint64>(n);
}

static inline NTL::ZZ_p to_ZZ_p(const uint64 & n)
{
    return NTL::to_ZZ_p(to_ZZ<uint64>(n));
}

static inline void to_uint64(const NTL::ZZ & n, uint64 & ret)
{
    to_uint<uint64>(n, ret);
}

 void normalize(uint64 & a_lo, uint64 & a_hi,
	const uint64 & s_lo, const uint s_hi)
{
    asm("sub.cc.u32	 %0, %0, %4;\n\t"	// r0-= r4
	"subc.cc.u32	 %1, %1, %5;\n\t"	// r1-=( r5+c)
	"subc.cc.u32	 %2, %2, %6;\n\t"	// r2-=( r6+c)
	"subc.u32	 %3, %3, %6;\n\t"	// r3-=( r6+c)
	: "+r"(a_lo.x), "+r"(a_lo.y), "+r"(a_hi.x), "+r"(a_hi.y)
	: "r"(s_lo.x), "r"(s_lo.y), "r"(s_hi));
}

 uint sub(uint64 & a_lo, uint64 & a_hi,
	const uintXp<uint64> & r)
{
    asm("sub.cc.u32	 %0, %0, %3;\n\t"	// r0-= r3
	"subc.cc.u32	 %1, %1, %4;\n\t"	// r1-=( r4+c)
	"subc.u32	 %2, %2, %5;\n\t"	// r2-=( r5+c)
	: "+r"(a_lo.x), "+r"(a_lo.y), "+r"(a_hi.x)
	: "r"(r.lo.x), "r"(r.lo.y), "r"(r.hi));
    return a_hi.x;
}

 uintXp<uint64> get_q(const uint64 & a_lo,
	const uint64 & a_hi, const uintXp<uint64> & mu)
{
    uint __attribute__((unused)) tmp0;
    uintXp<uint64> q = {0};
    asm("mul.hi.u32	 %2, %4, %7    ;\n\t"	// r2 =[ r4* r7].hi   (r-1=>r2)
	"mad.lo.cc.u32	 %2, %5, %7, %2;\n\t"	// r2+=[ r5* r7].lo   (r-1=>r2)
	"madc.lo.u32	 %3, %6, %7,  0;\n\t"	// r3 =[ r6* r7].lo+c
	"mad.lo.cc.u32	 %2, %4, %8, %2;\n\t"	// r2+=[ r4* r8].lo   (r-1=>r2)
	"madc.lo.cc.u32	 %3, %5, %8, %3;\n\t"	// r3+=[ r5* r8].lo+c
	"madc.lo.u32	 %0, %6, %8,  0;\n\t"	// r0 =[ r6* r8].lo+c
	"mad.hi.cc.u32	 %3, %5, %7, %3;\n\t"	// r3+=[ r5* r7].hi  
	"madc.hi.cc.u32	 %0, %6, %7, %0;\n\t"	// r0+=[ r6* r7].hi+c
	"madc.hi.u32	 %1, %6, %8,  0;\n\t"	// r1 =[ r6* r8].hi+c
	"mad.hi.cc.u32	 %3, %4, %8, %3;\n\t"	// r3+=[ r4* r8].hi  
	"madc.hi.cc.u32	 %0, %5, %8, %0;\n\t"	// r0+=[ r5* r8].hi+c
	"addc.cc.u32	 %1, %1,  0    ;\n\t"	// r1+= c
	"addc.u32	 %2,  0,  0    ;\n\t"	// r2 = c
	"mad.lo.cc.u32	 %3, %4, %9, %3;\n\t"	// r3+= r4* r9
	"madc.lo.cc.u32	 %0, %5, %9, %0;\n\t"	// r0+= r5* r9+c
	"madc.lo.cc.u32	 %1, %6, %9,%1;\n\t"	// r1+= r6* r9+c
	"addc.u32	 %2, %2,  0    ;\n\t"	// r2+=c
	: "+r"(q.lo.x), "=r"(q.lo.y), "=r"(q.hi), "=r"(tmp0)
	: "r"(a_lo.y ), "r"(a_hi.x), "r"(a_hi.y), "r"(mu.lo.x),
	  "r"(mu.lo.y), "r"(mu.hi));

    return q;
}

 uintXp<uint64> get_r2(const uintXp<uint64> & q,
	const uint64 & modulus)
{
    uintXp<uint64> r = {0};
    asm("mad.lo.u32	 %0, %3, %6,  0;\n\t"	// r0 =[ r3* r6].lo  
	"mad.lo.u32	 %1, %3, %7,  0;\n\t"	// r1 =[ r3* r7].lo  
	"mad.lo.cc.u32	 %1, %4, %6, %1;\n\t"	// r1+=[ r4* r6].lo  
	"madc.lo.u32	 %2, %4, %7,  0;\n\t"	// r2 =[ r4* r7].lo+c
	"mad.hi.cc.u32	 %1, %3, %6, %1;\n\t"	// r1+=[ r3* r6].hi  
	"madc.hi.cc.u32	 %2, %3, %7, %2;\n\t"	// r2+=[ r3* r7].hi+c
	"mad.lo.cc.u32	 %2, %5, %6, %2;\n\t"	// r2+=[ r5* r6].lo  
	"mad.hi.cc.u32	 %2, %4, %6, %2;\n\t"	// r2+=[ r4* r6].hi  
	: "+r"(r.lo.x), "=r"(r.lo.y), "=r"(r.hi)
	: "r"(q.lo.x), "r"(q.lo.y), "r"(q.hi), "r"(modulus.x),
	  "r"(modulus.y));

    return r;
}

 void sub_modulus(uintXp<uint64> & r, const uint64 & m)
{
    asm("sub.cc.u32	 %0, %0, %3;\n\t"	// r0-= r3
	"subc.cc.u32	 %1, %1, %4;\n\t"	// r1-=( r4+c)
	"subc.u32	 %2, %2,  0;\n\t"	// r2-=(    c)
	: "+r"(r.lo.x), "+r"(r.lo.y), "+r"(r.hi)
	: "r"(m.x), "r"(m.y));
}

 void mad(uint64 & a_lo, uint64 & a_hi,
	uint & overflow, const uint64 & b, const uint64 & c)
{
    asm("mad.lo.cc.u32	 %0, %5, %7, %0;\n\t"	// r0+=[ r5* r7].lo  
	"madc.hi.cc.u32	 %1, %5, %7, %1;\n\t"	// r1+=[ r5* r7].hi  
	"madc.lo.cc.u32	 %2, %6, %8, %2;\n\t"	// r2+=[ r6* r8].lo+c
	"madc.hi.cc.u32	 %3, %6, %8, %3;\n\t"	// r3+=[ r6* r8].hi+c
	"addc.u32	 %4, %4,  0    ;\n\t"	// r4+=c
	"mad.lo.cc.u32	 %1, %6, %7, %1;\n\t"	// r1+=[ r6* r7].lo  
	"madc.hi.cc.u32	 %2, %6, %7, %2;\n\t"	// r2+=[ r6* r7].hi  
	"addc.cc.u32	 %3, %3,  0    ;\n\t"	// r3+=c
	"addc.u32	 %4, %4,  0    ;\n\t"	// r4+=c
	"mad.lo.cc.u32	 %1, %5, %8, %1;\n\t"	// r1+=[ r5* r8].lo  
	"madc.hi.cc.u32	 %2, %5, %8, %2;\n\t"	// r2+=[ r5* r8].hi  
	"addc.cc.u32	 %3, %3,  0    ;\n\t"	// r3+=c
	"addc.u32	 %4, %4,  0    ;\n\t"	// r4+=c
	: "+r"(a_lo.x), "+r"(a_lo.y), "+r"(a_hi.x), "+r"(a_hi.y),
	  "+r"(overflow)
	: "r"(b.x), "r"(b.y), "r"(c.x), "r"(c.y));
}

#endif