#!/bin/bash
# 
#   ** Simple script to compile the code SOPPE v1.0 **
#
#      The installations paths to the CUDA toolkit and SDK (http://www.nvidia.com/cuda) and the MPI 
#      library path may have to be adapted before runing the script!
#      The zlib.h library is used to allow gzip-ed input files.
# 
#      Default paths:
#         CUDA:  /usr/local/cuda
#         SDK:   /usr/local/cuda/samples
#         MPI:   /usr/include/openmpi

# -- Compile GPU code for compute capability 1.3 and 2.0, with MPI:

echo " "
echo " -- Compiling SOPPE v1.0 for both compute capability 2.0 and 3.0 (64 bits), with MPI:"
echo "    To run a simulation in parallel with openMPI execute:"
echo "      $ time mpirun --tag-output -v -x LD_LIBRARY_PATH -hostfile hostfile_gpunodes -n 22 /GPU_cluster/SOPPE_v1.0.x /GPU_cluster/SOPPE_v1.0.in | tee SOPPE_v1.0.out"
echo " "
echo "nvcc SOPPE_v1.0.cu -o SOPPE_v1.0.x -m64 -O3 -use_fast_math -DUSING_CUDA -DUSING_MPI -I. -I/usr/local/cuda/include -I/usr/local/cuda/samples/common/inc -I/usr/local/cuda/samples/shared/inc/ -I/usr/include/openmpi -L/usr/lib/ -lmpi -lz --ptxas-options=-v -gencode=arch=compute_20,code=sm_20 -gencode=arch=compute_30,code=sm_30"
nvcc SOPPE_v1.0.cu -o SOPPE_v1.0.x -m64 -O3 -use_fast_math -DUSING_CUDA -DUSING_MPI -I. -I/usr/local/cuda/include -I/usr/local/cuda/samples/common/inc -I/usr/local/cuda/samples/shared/inc/ -I/usr/include/openmpi -L/usr/lib/ -lmpi -lz --ptxas-options=-v -gencode=arch=compute_20,code=sm_20 -gencode=arch=compute_30,code=sm_30

# -gencode=arch=compute_13,code=sm_13 -gencode=arch=compute_35,code=sm_35 -gencode=arch=compute_35,code=compute_35




# -- CPU compilation:
 
# ** GCC (with MPI):
# gcc -x c -DUSING_MPI SOPPE_v1.0.cu -o SOPPE_v1.0_gcc_MPI.x -Wall -O3 -ffast-math -ftree-vectorize -ftree-vectorizer-verbose=1 -funroll-loops -static-libgcc -I./ -lm -I/usr/include/openmpi -I/usr/lib/openmpi/include/openmpi/ -L/usr/lib/openmpi/lib -lmpi

     
# ** Intel compiler (with MPI):
# icc -x c -O3 -ipo -no-prec-div -msse4.2 -parallel -Wall -DUSING_MPI SOPPE_v1.0.cu -o SOPPE_v1.0_icc_MPI.x -I./ -lm -I/usr/include/openmpi -L/usr/lib/openmpi/lib/ -lmpi


# ** PGI compiler:
# pgcc -fast,sse -O3 -Mipa=fast -Minfo -csuffix=cu -Mconcur SOPPE_v1.0.cu -I./ -lm -o SOPPE_v1.0_PGI.x

