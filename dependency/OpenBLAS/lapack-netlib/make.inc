FORTRAN     = gfortran
OPTS        = -O2 -Wall -m64 -fPIC
POPTS       = -Wall -m64 -fPIC -pg -fno-inline
NOOPT       = -O0 -Wall -m64 -fPIC
PNOOPT      = -Wall -m64 -fPIC -pg -fno-inline -O0
LOADOPTS    = -O2 -Wall -m64 -fPIC -lm -lpthread -lgfortran
CC          = gcc
override CFLAGS      = -O2 -DMAX_STACK_ALLOC=2048 -Wall -m64 -DF_INTERFACE_GFORT -fPIC -DSMP_SERVER -DNO_WARMUP -DMAX_CPU_NUMBER=4 -DASMNAME= -DASMFNAME=_ -DNAME=_ -DCNAME= -DCHAR_NAME="_" -DCHAR_CNAME="" -I. -DHAVE_LAPACK_CONFIG_H
ARCH        = ar
ARCHFLAGS   =  -ru
RANLIB      = ranlib
LAPACKLIB   = ../libopenblas_sandybridgep-r0.3.0.dev.a
TMGLIB      = ../libopenblas_sandybridgep-r0.3.0.dev.a
BLASLIB     = ../../../libopenblas_sandybridgep-r0.3.0.dev.a
LAPACKELIB  = ../libopenblas_sandybridgep-r0.3.0.dev.a
LAPACKLIB_P = ../libopenblas_sandybridgep-r0.3.0.dev_p.a
SUFFIX      = o
PSUFFIX     = po
CEXTRALIB   = -lm -lpthread -lgfortran
TIMER       = INT_ETIME
LOADER      = gfortran -pthread
BUILD_DEPRECATED      = 1
SHELL = /bin/sh
PLAT = _LINUX
DRVOPTS  = $(NOOPT)
#ARCHFLAGS= $(ARFLAGS) -ru
#RANLIB   = ranlib

