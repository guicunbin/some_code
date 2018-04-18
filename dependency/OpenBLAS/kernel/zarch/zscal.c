/***************************************************************************
Copyright (c) 2013 - 2017, The OpenBLAS Project
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

 

static void  __attribute__ ((noinline))  zscal_kernel_8(BLASLONG n, FLOAT *alpha, FLOAT *x) {
    __asm__(

            "pfd 1, 0(%1) \n\t"
            "sllg %%r0,%0,4       \n\t"
            "agr  %%r0,%2  \n\t"
            "vlrepg %%v24,0(%1)  \n\t"
            "vlrepg %%v25,8(%1)  \n\t"
            ".align 16 \n\t"
            "1: \n\t"
            "pfd 2, 256(%2 ) \n\t"

            "vleg %%v20 ,  0(%2),0  \n\t" 
            "vleg %%v21 ,  8(%2),0  \n\t"
            "vleg %%v20 , 16(%2),1  \n\t"
            "vleg %%v21 , 24(%2),1  \n\t"

            "vleg %%v22 , 32(%2),0  \n\t" 
            "vleg %%v23 , 40(%2),0  \n\t"
            "vleg %%v22 , 48(%2),1  \n\t"
            "vleg %%v23 , 56(%2),1  \n\t"

            "vfmdb %%v16,  %%v21, %%v25  \n\t"
            "vfmdb %%v17,  %%v20, %%v25  \n\t"
            "vfmdb %%v18,  %%v23, %%v25  \n\t"
            "vfmdb %%v19,  %%v22, %%v25  \n\t"

            "vfmsdb %%v16, %%v20, %%v24 ,%%v16  \n\t"
            "vfmadb %%v17, %%v21, %%v24, %%v17  \n\t"
            "vfmsdb %%v18, %%v22, %%v24, %%v18  \n\t"
            "vfmadb %%v19, %%v23, %%v24, %%v19  \n\t"

            "vsteg %%v16 ,  0(%2),0  \n\t" 
            "vsteg %%v17 ,  8(%2),0  \n\t"
            "vsteg %%v16 , 16(%2),1  \n\t"
            "vsteg %%v17 , 24(%2),1  \n\t"

            "vsteg %%v18 , 32(%2),0  \n\t" 
            "vsteg %%v19 , 40(%2),0  \n\t"
            "vsteg %%v18 , 48(%2),1  \n\t"
            "vsteg %%v19 , 56(%2),1  \n\t"
            
            "vleg %%v20 ,  64(%2),0  \n\t" 
            "vleg %%v21 , 72(%2),0   \n\t"
            "vleg %%v20 , 80(%2),1   \n\t"
            "vleg %%v21 , 88(%2),1   \n\t"

            "vleg %%v22 , 96(%2),0   \n\t" 
            "vleg %%v23 , 104(%2),0  \n\t"
            "vleg %%v22 , 112(%2),1  \n\t"
            "vleg %%v23 , 120(%2),1  \n\t"

            "vfmdb %%v16,  %%v21, %%v25  \n\t"
            "vfmdb %%v17,  %%v20, %%v25  \n\t"
            "vfmdb %%v18,  %%v23, %%v25  \n\t"
            "vfmdb %%v19,  %%v22, %%v25  \n\t"

            "vfmsdb %%v16, %%v20, %%v24 ,%%v16  \n\t"
            "vfmadb %%v17, %%v21, %%v24, %%v17  \n\t"
            "vfmsdb %%v18, %%v22, %%v24, %%v18  \n\t"
            "vfmadb %%v19, %%v23, %%v24, %%v19  \n\t"

            "vsteg %%v16 , 64(%2),0  \n\t" 
            "vsteg %%v17 , 72(%2),0  \n\t"
            "vsteg %%v16 , 80(%2),1  \n\t"
            "vsteg %%v17 , 88(%2),1  \n\t"

            "vsteg %%v18 ,  96(%2),0 \n\t" 
            "vsteg %%v19 , 104(%2),0 \n\t"
            "vsteg %%v18 , 112(%2),1 \n\t"
            "vsteg %%v19 , 120(%2),1 \n\t"
   
            "la %2,128(%2)     \n\t"
            "clgrjl %2,%%r0,1b \n\t"
            :
            : "r"(n), "a"(alpha), "a"(x)
            : "cc", "memory","r0","v16","v17","v18","v19","v20","v21","v22","v23","v24","v25"
            );


}
 
static void   __attribute__ ((noinline))  zscal_kernel_8_zero_r(BLASLONG n, FLOAT *alpha, FLOAT *x) {
 
        __asm__ (   "pfd 2, 0(%1)   \n\t" 
                    "ld %%f0,8(%2)  \n\t"
                    "lcdbr %%f1,%%f0     \n\t"
                    "lgdr %%r0,%%f1      \n\t"
                    "vlvgg %%v0,%%r0,1   \n\t"
                    "vlr %%v16,%%v0      \n\t"
                    "vlr %%v17 ,%%v0     \n\t"
                    "vlr %%v1,%%v0       \n\t" 
                    "sllg %%r0,%0,4      \n\t"  
                    "agr %%r0,%1  \n\t"
                    ".align 16    \n\t"    
                    "1: \n\t"  
                    "vl     %%v24, 0(%1)      \n\t"
                    "vfmdb  %%v24,%%v24,%%v0  \n\t"
                    "vsteg  %%v24, 0(%1),1    \n\t" 
                    "vsteg  %%v24, 8(%1),0    \n\t" 
                    "vl     %%v25, 16(%1)     \n\t"
                    "vfmdb  %%v25,%%v25,%%v1  \n\t"  
                    "vsteg  %%v25, 16(%1),1   \n\t" 
                    "vsteg  %%v25, 24(%1),0   \n\t" 
                    "vl     %%v26, 32(%1)     \n\t"
                    "vfmdb  %%v26,%%v26,%%v16 \n\t"
                    "vsteg  %%v26, 32(%1),1   \n\t" 
                    "vsteg  %%v26, 40(%1),0   \n\t"   
                    "vl     %%v27, 48(%1)     \n\t" 
                    "vfmdb  %%v27,%%v27,%%v17 \n\t"  
                    "vsteg  %%v27, 40(%1),1   \n\t" 
                    "vsteg  %%v27, 48(%1),0   \n\t" 
                    "vl     %%v28, 64(%1)     \n\t"
                    "vfmdb  %%v28,%%v28,%%v0  \n\t"
                    "vsteg  %%v28, 64(%1),1   \n\t" 
                    "vsteg  %%v28, 72(%1),0   \n\t" 
                    "vl     %%v29, 80(%1)     \n\t"
                    "vfmdb  %%v29,%%v29,%%v1  \n\t"  
                    "vsteg  %%v29, 80(%1),1   \n\t" 
                    "vsteg  %%v29, 88(%1),0   \n\t" 
                    "vl     %%v30, 96(%1)     \n\t"
                    "vfmdb  %%v30,%%v30,%%v16 \n\t"
                    "vsteg  %%v27,  96(%1),1  \n\t" 
                    "vsteg  %%v27, 104(%1),0  \n\t"  
                    "vl     %%v31, 112(%1)    \n\t" 
                    "vfmdb  %%v31,%%v31,%%v17 \n\t"  
                    "vsteg  %%v31, 112(%1),1  \n\t" 
                    "vsteg  %%v31, 120(%1),0  \n\t" 
                    "la %1,128(%1) \n\t"
                    "clgrjl %1,%%r0,1b \n\t"
                    : 
                    :"r"(n),"a"(x) ,"a"(alpha)
                    :"cc", "memory","r0","f0", "f1","v0","v1","v18","v19","v24","v25","v26","v27","v28","v29","v30","v31" 
                 );


}

static void  __attribute__ ((noinline)) zscal_kernel_8_zero_i(BLASLONG n, FLOAT *alpha, FLOAT *x) {
           __asm__ ("pfd 2, 0(%1) \n\t"      
                    "vlrepg %%v18,0(%2) \n\t"
                    "vlr %%v19,%%v18    \n\t"
                    "vlr %%v16 ,%%v18   \n\t"
                    "vlr %%v17,%%v18    \n\t" 
                    "sllg %%r0,%0,4     \n\t"  
                    "agr %%r0,%1  \n\t"
                    ".align 16 \n\t"    
                    "1: \n\t"  
                    "vl     %%v24, 0(%1)      \n\t"
                    "vfmdb  %%v24,%%v24,%%v18 \n\t"
                    "vst    %%v24, 0(%1)      \n\t" 
                    "vl     %%v25, 16(%1)     \n\t"
                    "vfmdb  %%v25,%%v25,%%v19 \n\t"  
                    "vst    %%v25, 16(%1)     \n\t" 
                    "vl     %%v26, 32(%1)     \n\t"
                    "vfmdb  %%v26,%%v26,%%v16 \n\t"
                    "vst    %%v26, 32(%1)     \n\t"  
                    "vl     %%v27, 48(%1)     \n\t" 
                    "vfmdb  %%v27,%%v27,%%v17 \n\t"  
                    "vst    %%v27, 48(%1)     \n\t"  
                    "vl     %%v28, 64(%1)     \n\t"
                    "vfmdb  %%v28,%%v28,%%v18 \n\t"
                    "vst    %%v28, 64(%1)     \n\t" 
                    "vl     %%v29, 80(%1)     \n\t"
                    "vfmdb  %%v29,%%v29,%%v19 \n\t"  
                    "vst    %%v29, 80(%1)     \n\t" 
                    "vl     %%v30, 96(%1)     \n\t"
                    "vfmdb  %%v30,%%v30,%%v16 \n\t"
                    "vst    %%v30, 96(%1)     \n\t"  
                    "vl     %%v31, 112(%1)    \n\t" 
                    "vfmdb  %%v31,%%v31,%%v17 \n\t"  
                    "vst    %%v31, 112(%1)    \n\t"
                    "la    %1,128(%1)         \n\t"
                    "clgrjl %1,%%r0,1b        \n\t"
                    : 
                    :"r"(n),"a"(x) ,"a"(alpha)
                    :"cc", "memory","r0","v16", "v17","v18","v19","v24","v25","v26","v27","v28","v29","v30","v31" 
                 );

}

static void  __attribute__ ((noinline)) zscal_kernel_8_zero(BLASLONG n,  FLOAT *x) {

     __asm__ (      "pfd 2, 0(%1)    \n\t"      
                    "vzero %%v24     \n\t"
                    "vzero %%v25     \n\t"
                    "vzero %%v26     \n\t"
                    "vzero %%v27     \n\t" 
                    "sllg  %%r0,%0,4 \n\t"  
                    "agr   %%r0,%1   \n\t"
                    ".align 16 \n\t"    
                    "1: \n\t" 
                    "pfd 2, 256( %1)      \n\t"     
                    "vst  %%v24,  0( %1)  \n\t" 
                    "vst  %%v25, 16( %1)  \n\t" 
                    "vst  %%v26, 32( %1)  \n\t"   
                    "vst  %%v27, 48( %1)  \n\t"  
                    "vst  %%v24, 64( %1)  \n\t" 
                    "vst  %%v25, 80( %1)  \n\t" 
                    "vst  %%v26, 96( %1)  \n\t"  
                    "vst  %%v27,112( %1)  \n\t"  
              
                    "la     %1,128(%1) \n\t"
                    "clgrjl %1,%%r0,1b \n\t"
                    : 
                    :"r"(n),"a"(x) 
                    :"cc" , "memory" ,"r0","v24","v25","v26","v27"
                 );

}



static void zscal_kernel_inc_8(BLASLONG n, FLOAT *alpha, FLOAT *x, BLASLONG inc_x) __attribute__ ((noinline));

static void zscal_kernel_inc_8(BLASLONG n, FLOAT *alpha, FLOAT *x, BLASLONG inc_x) {

    BLASLONG i;
    BLASLONG inc_x2 = 2 * inc_x;
    BLASLONG inc_x3 = inc_x2 + inc_x;
    FLOAT t0, t1, t2, t3;
    FLOAT da_r = alpha[0];
    FLOAT da_i = alpha[1];

    for (i = 0; i < n; i += 4) {
        t0 = da_r * x[0] - da_i * x[1];
        t1 = da_r * x[inc_x] - da_i * x[inc_x + 1];
        t2 = da_r * x[inc_x2] - da_i * x[inc_x2 + 1];
        t3 = da_r * x[inc_x3] - da_i * x[inc_x3 + 1];

        x[1] = da_i * x[0] + da_r * x[1];
        x[inc_x + 1] = da_i * x[inc_x] + da_r * x[inc_x + 1];
        x[inc_x2 + 1] = da_i * x[inc_x2] + da_r * x[inc_x2 + 1];
        x[inc_x3 + 1] = da_i * x[inc_x3] + da_r * x[inc_x3 + 1];

        x[0] = t0;
        x[inc_x] = t1;
        x[inc_x2] = t2;
        x[inc_x3] = t3;

        x += 4 * inc_x;

    }


}

int CNAME(BLASLONG n, BLASLONG dummy0, BLASLONG dummy1, FLOAT da_r, FLOAT da_i, FLOAT *x, BLASLONG inc_x, FLOAT *y, BLASLONG inc_y, FLOAT *dummy, BLASLONG dummy2) {
    BLASLONG i = 0, j = 0;
    FLOAT temp0;
    FLOAT temp1;
    FLOAT alpha[2];

    if (inc_x != 1) {
        inc_x <<= 1;

        if (da_r == 0.0) {

            BLASLONG n1 = n & -2;

            if (da_i == 0.0) {

                while (j < n1) {

                    x[i] = 0.0;
                    x[i + 1] = 0.0;
                    x[i + inc_x] = 0.0;
                    x[i + 1 + inc_x] = 0.0;
                    i += 2 * inc_x;
                    j += 2;

                }

                while (j < n) {

                    x[i] = 0.0;
                    x[i + 1] = 0.0;
                    i += inc_x;
                    j++;

                }

            } else {

                while (j < n1) {

                    temp0 = -da_i * x[i + 1];
                    x[i + 1] = da_i * x[i];
                    x[i] = temp0;
                    temp1 = -da_i * x[i + 1 + inc_x];
                    x[i + 1 + inc_x] = da_i * x[i + inc_x];
                    x[i + inc_x] = temp1;
                    i += 2 * inc_x;
                    j += 2;

                }

                while (j < n) {

                    temp0 = -da_i * x[i + 1];
                    x[i + 1] = da_i * x[i];
                    x[i] = temp0;
                    i += inc_x;
                    j++;

                }



            }

        } else {


            if (da_i == 0.0) {
                BLASLONG n1 = n & -2;

                while (j < n1) {

                    temp0 = da_r * x[i];
                    x[i + 1] = da_r * x[i + 1];
                    x[i] = temp0;
                    temp1 = da_r * x[i + inc_x];
                    x[i + 1 + inc_x] = da_r * x[i + 1 + inc_x];
                    x[i + inc_x] = temp1;
                    i += 2 * inc_x;
                    j += 2;

                }

                while (j < n) {

                    temp0 = da_r * x[i];
                    x[i + 1] = da_r * x[i + 1];
                    x[i] = temp0;
                    i += inc_x;
                    j++;

                }

            } else {

                BLASLONG n1 = n & -8;
                if (n1 > 0) {
                    alpha[0] = da_r;
                    alpha[1] = da_i;
                    zscal_kernel_inc_8(n1, alpha, x, inc_x);
                    j = n1;
                    i = n1 * inc_x;
                }

                while (j < n) {

                    temp0 = da_r * x[i] - da_i * x[i + 1];
                    x[i + 1] = da_r * x[i + 1] + da_i * x[i];
                    x[i] = temp0;
                    i += inc_x;
                    j++;

                }

            }

        }

        return (0);
    }


    BLASLONG n1 = n & -8;
    if (n1 > 0) {

        alpha[0] = da_r;
        alpha[1] = da_i;

        if (da_r == 0.0)
            if (da_i == 0)
                zscal_kernel_8_zero(n1,  x);
            else
                zscal_kernel_8_zero_r(n1, alpha, x);
        else
            if (da_i == 0)
            zscal_kernel_8_zero_i(n1, alpha, x);
        else
            zscal_kernel_8(n1, alpha, x);

        i = n1 << 1;
        j = n1;
    }


    if (da_r == 0.0) {

        if (da_i == 0.0) {

            while (j < n) {

                x[i] = 0.0;
                x[i + 1] = 0.0;
                i += 2;
                j++;

            }

        } else {

            while (j < n) {

                temp0 = -da_i * x[i + 1];
                x[i + 1] = da_i * x[i];
                x[i] = temp0;
                i += 2;
                j++;

            }

        }

    } else {

        if (da_i == 0.0) {

            while (j < n) {

                temp0 = da_r * x[i];
                x[i + 1] = da_r * x[i + 1];
                x[i] = temp0;
                i += 2;
                j++;

            }

        } else {

            while (j < n) {

                temp0 = da_r * x[i] - da_i * x[i + 1];
                x[i + 1] = da_r * x[i + 1] + da_i * x[i];
                x[i] = temp0;
                i += 2;
                j++;

            }

        }

    }

    return (0);
}


