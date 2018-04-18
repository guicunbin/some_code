/***************************************************************************
Copyright (c) 2017, The OpenBLAS Project
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.
3. Neither the name of the OpenBLAS project nor the names of
its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE OPENBLAS PROJECT OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/
 

#include "common.h"
#include <math.h>
 
#define ABS fabs 
#define CABS1(x,i)    ABS(x[i])+ABS(x[i+1])

 

static BLASLONG __attribute__((noinline)) ziamax_kernel_8_TUNED(BLASLONG n, FLOAT *x, FLOAT *maxf) { 

    __asm__(
            "pfd 1, 0(%1) \n\t" 
            "VLEIG  %%v16,0,0  \n\t"
            "VLEIG  %%v16,1,1  \n\t"
            "VLEIG  %%v17,2,0  \n\t"
            "VLEIG  %%v17,3,1  \n\t"
            "VLEIG  %%v18,4,0  \n\t"
            "VLEIG  %%v18,5,1  \n\t"
            "VLEIG  %%v19,6,0  \n\t"
            "VLEIG  %%v19,7,1  \n\t" 
            "VLEIG  %%v20,8,0  \n\t"
            "VLEIG  %%v20,9,1  \n\t"
            "VLEIG  %%v21,10,0 \n\t"
            "VLEIG  %%v21,11,1 \n\t"
            "VLEIG  %%v22,12,0 \n\t"
            "VLEIG  %%v22,13,1 \n\t"
            "VLEIG  %%v23,14,0 \n\t"
            "VLEIG  %%v23,15,1 \n\t" 
    
    
            "sllg %%r0,%0,4 \n\t"
            "agr %%r0,%1    \n\t" 
            "vzero %%v6     \n\t"
            "vzero %%v7     \n\t"
            "VREPIG %%v4,16 \n\t"
            "vzero %%v5     \n\t"
            ".align 16 \n\t"
            "1: \n\t"
            "pfd 1, 256(%1 ) \n\t"
        
            "vleg %%v24 ,  0( %1),0 \n\t" 
            "vleg %%v25 ,  8( %1),0 \n\t"
            "vleg %%v24 , 16( %1),1 \n\t" 
            "vleg %%v25 , 24( %1),1 \n\t"
            "vleg %%v26 , 32( %1),0 \n\t"  
            "vleg %%v27 , 40( %1),0 \n\t"
            "vleg %%v26 , 48( %1),1 \n\t" 
            "vleg %%v27 , 56( %1),1 \n\t" 
            "vleg %%v28 , 64( %1),0 \n\t" 
            "vleg %%v29 , 72( %1),0 \n\t" 
            "vleg %%v28 , 80( %1),1 \n\t"
            "vleg %%v29 , 88( %1),1 \n\t" 
            "vleg %%v30 , 96( %1),0 \n\t"  
            "vleg %%v31 ,104( %1),0 \n\t"
            "vleg %%v30 ,112( %1),1 \n\t"
            "vleg %%v31 ,120( %1),1 \n\t"  
            "vflpdb  %%v24, %%v24   \n\t" 
            "vflpdb  %%v25, %%v25   \n\t" 
            "vflpdb  %%v26, %%v26   \n\t" 
            "vflpdb  %%v27, %%v27   \n\t" 
            "vflpdb  %%v28, %%v28   \n\t" 
            "vflpdb  %%v29, %%v29   \n\t"
            "vflpdb  %%v30, %%v30   \n\t" 
            "vflpdb  %%v31, %%v31   \n\t"    
     
            "vfadb %%v0,%%v24,%%v25 \n\t"
            "vfadb %%v1,%%v26,%%v27 \n\t"
            "vfadb %%v2,%%v28,%%v29 \n\t"
            "vfadb %%v3,%%v30,%%v31 \n\t"
     
    
            "vleg %%v24 , 128( %1),0  \n\t" 
            "vleg %%v25 , 136( %1),0  \n\t"
            "vleg %%v24 , 144( %1),1  \n\t" 
            "vleg %%v25 , 152( %1),1  \n\t"
            "vleg %%v26 , 160( %1),0  \n\t"  
            "vleg %%v27 , 168( %1),0  \n\t"
            "vleg %%v26 , 176( %1),1  \n\t" 
            "vleg %%v27 , 184( %1),1  \n\t" 
            "vleg %%v28 , 192( %1),0  \n\t" 
            "vleg %%v29 , 200( %1),0  \n\t" 
            "vleg %%v28 , 208( %1),1  \n\t"
            "vleg %%v29 , 216( %1),1  \n\t" 
            "vleg %%v30 , 224( %1),0  \n\t"  
            "vleg %%v31 , 232( %1),0  \n\t"
            "vleg %%v30 , 240( %1),1  \n\t"
            "vleg %%v31 , 248( %1),1  \n\t"  
            "vflpdb  %%v24, %%v24 \n\t" 
            "vflpdb  %%v25, %%v25 \n\t" 
            "vflpdb  %%v26, %%v26 \n\t" 
            "vflpdb  %%v27, %%v27 \n\t" 
            "vflpdb  %%v28, %%v28 \n\t" 
            "vflpdb  %%v29, %%v29 \n\t"
            "vflpdb  %%v30, %%v30 \n\t" 
            "vflpdb  %%v31, %%v31 \n\t"    
     
            "vfadb %%v24,%%v24,%%v25  \n\t"
            "vfadb %%v26,%%v26,%%v27  \n\t"
            "vfadb %%v28,%%v28,%%v29  \n\t"
            "vfadb %%v30,%%v30,%%v31  \n\t"
    
            "vfchdb  %%v25,%%v1,%%v0  \n\t" 
            "vsel  %%v29,%%v17,%%v16,%%v25 \n\t"
            "vsel  %%v31,%%v1,%%v0,%%v25   \n\t"  
    
            "vfchdb  %%v27,%%v3,%%v2 \n\t "   
            "vsel  %%v0,%%v19,%%v18,%%v27 \n\t"
            "vsel  %%v1,%%v3,%%v2,%%v27   \n\t"  
    
            "vfchdb  %%v25,%%v26,%%v24  \n\t " 
            "vsel  %%v2,%%v21,%%v20,%%v25 \n\t"
            "vsel  %%v3,%%v26,%%v24,%%v25 \n\t" 
    
            "vfchdb  %%v27,%%v30,%%v28 \n\t "   
            "vsel  %%v25,%%v23,%%v22,%%v27 \n\t"
            "vsel  %%v27,%%v30,%%v28,%%v27 \n\t"  
    
            "vfchdb %%v24, %%v1,%%v31      \n\t" 
            "vsel  %%v26,%%v0,%%v29,%%v24  \n\t" 
            "vsel  %%v28,%%v1,%%v31,%%v24  \n\t"
    
            "vfchdb %%v30, %%v27,%%v3      \n\t" 
            "vsel  %%v29,%%v25,%%v2,%%v30  \n\t" 
            "vsel  %%v31,%%v27,%%v3 ,%%v30 \n\t" 
    
            "la %1,256(%1)      \n\t"  
           
            "vfchdb %%v0, %%v31,%%v28     \n\t" 
            "vsel  %%v25,%%v29,%%v26,%%v0 \n\t" 
            "vsel  %%v27,%%v31,%%v28,%%v0 \n\t"
    
            "VAG %%v25,%%v25,%%v5 \n\t"
    
             //cmp with previous
            "vfchdb %%v30, %%v27,%%v6    \n\t"
            "vsel  %%v7,%%v25,%%v7,%%v30 \n\t" 
            "vsel  %%v6,%%v27,%%v6,%%v30 \n\t"
    
            "VAG %%v5,%%v5,%%v4 \n\t" 
    
            "clgrjl %1,%%r0,1b \n\t"

            //xtract index
            "vrepg %%v26,%%v6,1      \n\t"
            "vrepg %%v5,%%v7,1       \n\t"
            "wfcdb  %%v26,%%v6       \n\t"
            "jne 2f  \n\t"
            "VSTEG   %%v6,0(%2),0  \n\t"
            "VMNLG  %%v1,%%v5,%%v7 \n\t"
            "VLGVG  %%r2,%%v1,0  \n\t"
            "br %%r14  \n\t"
            "2: \n\t"
            "wfchdb  %%v16,%%v26,%%v6      \n\t"
            "vsel    %%v1,%%v5,%%v7,%%v16  \n\t"
            "vsel    %%v0,%%v26,%%v6,%%v16 \n\t"
            "VLGVG  %%r2,%%v1,0  \n\t"
            "std %%f0,0(%2)    \n\t"

            :
            : "r"(n), "a"(x), "a"(maxf)
            : "cc", "memory","r0","r1","r2","f0","v0","v1","v2","v3","v4","v5","v6","v7","v16",
            "v17","v18","v19","v20","v21","v22","v23","v24","v25","v26","v27","v28","v29","v30","v31"

            );

}


  

 
 

BLASLONG CNAME(BLASLONG n, FLOAT *x, BLASLONG inc_x)
{
    BLASLONG i = 0;
    BLASLONG ix = 0;
    FLOAT maxf = 0;
    BLASLONG max = 0;
    BLASLONG inc_x2;

    if (n <= 0 || inc_x <= 0) return(max);
     
    if (inc_x == 1) {

      BLASLONG n1 = n & -8;
      if (n1 > 0) {

            max = ziamax_kernel_8_TUNED(n1, x, &maxf);

            i = n1;
      }

      while(i < n)
    {
        if( CABS1(x,ix) > maxf )
        {
            max = i;
            maxf = CABS1(x,ix);
        }
        ix += 2;
        i++;
    }
        return (max + 1);

    } else {
 
      inc_x2 = 2 * inc_x;

    maxf = CABS1(x,0);
    ix += inc_x2;
    i++;

    while(i < n)
    {
        if( CABS1(x,ix) > maxf )
        {
            max = i;
            maxf = CABS1(x,ix);
        }
        ix += inc_x2;
        i++;
    }
        return (max + 1);
    }
 
}


