# How to Install LibTorch from Source on Ubuntu 18.04


## Pre-Requisite

### Step 1: APT

```bash
sudo apt-get update && sudo apt-get -y install --no-install-recommends \
  libopenblas-dev \
  libopenmpi-dev \
  libeigen3-dev \
  libnuma-dev \
  libfftw3-dev \
  libmpfr-dev \
  libjpeg-dev \
  libpng-dev \
  gfortran

sudo -H pip3 install scikit-build ninja

# x86_64 only
sudo -H pip3 install mkl mkl-devel
```

Note:
> Don't apt install pybind11-dev !

### Workaround for TsingHua Pypi Mirror Read Timeout

```bash
python3 -m pip config set global.index-url http://mirrors.aliyun.com/pypi/simple
pip3_install --trusted-host mirrors.aliyun.com mkl==2021.1.1
```

### Alternative Option for MKL Library Installation
https://software.intel.com/content/www/us/en/develop/articles/installing-intel-oneapi-toolkits-via-apt.html

```
# use wget to fetch the Intel repository public key
cd /tmp
wget https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB
# add to your apt sources keyring so that archives signed with this key will be trusted.
sudo apt-key add GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB
# remove the public key
rm GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB
echo "deb https://apt.repos.intel.com/oneapi all main" | sudo tee /etc/apt/sources.list.d/oneAPI.list
sudo apt update
sudo apt-get -y install intel-oneapi-mkl
```

## Clone PyTorch Repo

```
git clone --recursive --branch v1.7.0 http://github.com/pytorch/pytorch pytorch.git
cd pytorch.git
git submodule update --init --recursive
sudo -H pip3 install -r requirements.txt
## AArch64 ONLY
patch -p1 < path/to/pytorch-1.6-rc2-jetpack-4.4-GA.patch
```

## LibTorch: CPU Build

### Build

```
export USE_NCCL=0
export USE_DISTRIBUTED=0

## AArch64 ONLY START
export USE_QNNPACK=0
export USE_PYTORCH_QNNPACK=0
## AArch64 ONLY END

## 二者均为跟构建版本相关的环境变量
export PYTORCH_BUILD_VERSION="1.7.0"
export PYTORCH_BUILD_NUMBER=1

## BUILD_CUSTOM_PROTOBUF=OFF:
##  Use freshly installed protobuf already in CyberRT container
##  Rather than the one from pytorch.git/third_party

BUILD_TORCH=ON \
    USE_CUDA=0 \
    BUILD_CUSTOM_PROTOBUF=OFF \
    python3 setup.py build # or install
```

**Note**:

**Terminal Output**

```bash
cmake -GNinja -DBUILD_PYTHON=True -DBUILD_TEST=True -DBUILD_TORCH=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/apollo/pytorch.git/torch -DCMAKE_PREFIX_PATH=/usr/lib/python3/dist-packages -DNUMPY_INCLUDE_DIR=/usr/local/lib/python3.6/dist-packages/numpy/core/include -DPYTHON_EXECUTABLE=/usr/bin/python3 -DPYTHON_INCLUDE_DIR=/usr/include/python3.6m -DPYTHON_LIBRARY=/usr/lib/libpython3.6m.so.1.0 -DTORCH_BUILD_VERSION=1.7.0 -DUSE_CUDA=0 -DUSE_DISTRIBUTED=0 -DUSE_GPU_HOST=1 -DUSE_GPU_TARGET=1 -DUSE_NUMPY=True /apollo/pytorch.git
```

And Summary for x86_64

```text
-- Building with NumPy bindings
-- Not using cuDNN
-- Not using CUDA
-- Using MKLDNN
-- Not using CBLAS in MKLDNN
-- Not using NCCL
-- Building without distributed package
```

Summary for AArch64 using `BUILD_TORCH=ON USE_CUDA=0 BUILD_CUSTOM_PROTOBUF=OFF python3 tools/build_libtorch.py`

```text
-- ******** Summary ********
-- General:
--   CMake version         : 3.16.8
--   CMake command         : /opt/apollo/sysroot/bin/cmake
--   System                : Linux
--   C++ compiler          : /usr/bin/c++
--   C++ compiler id       : GNU
--   C++ compiler version  : 7.5.0
--   BLAS                  : OpenBLAS
--   CXX flags             :  -Wno-deprecated -fvisibility-inlines-hidden -DUSE_PTHREADPOOL -fopenmp -DNDEBUG -DUSE_XNNPACK -DUSE_VULKAN_WRAPPER -O2 -fPIC -Wno-narrowing -Wall -Wextra -Werror=return-type -Wno-missing-field-initializers -Wno-type-limits -Wno-array-bounds -Wno-unknown-pragmas -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-result -Wno-unused-local-typedefs -Wno-strict-overflow -Wno-strict-aliasing -Wno-error=deprecated-declarations -Wno-stringop-overflow -Wno-error=pedantic -Wno-error=redundant-decls -Wno-error=old-style-cast -fdiagnostics-color=always -faligned-new -Wno-unused-but-set-variable -Wno-maybe-uninitialized -fno-math-errno -fno-trapping-math -Werror=format -Wno-stringop-overflow
--   Build type            : Release
--   Compile definitions   : ONNX_ML=1;ONNXIFI_ENABLE_EXT=1;ONNX_NAMESPACE=onnx_torch;HAVE_MMAP=1;_FILE_OFFSET_BITS=64;HAVE_SHM_OPEN=1;HAVE_SHM_UNLINK=1;HAVE_MALLOC_USABLE_SIZE=1;USE_EXTERNAL_MZCRC;MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
--   CMAKE_PREFIX_PATH     : /usr/lib/python3/dist-packages
--   CMAKE_INSTALL_PREFIX  : /apollo/pytorch.git/torch
-- 
--   TORCH_VERSION         : 1.6.0
--   CAFFE2_VERSION        : 1.6.0
--   BUILD_CAFFE2_MOBILE   : OFF
--   USE_STATIC_DISPATCH   : OFF
--   BUILD_BINARY          : OFF
--   BUILD_CUSTOM_PROTOBUF : OFF
--     Protobuf compiler   : 
--     Protobuf includes   : 
--     Protobuf libraries  : 
--   BUILD_DOCS            : OFF
--   BUILD_PYTHON          : False
--   BUILD_CAFFE2_OPS      : ON
--   BUILD_SHARED_LIBS     : ON
--   BUILD_TEST            : True
--   BUILD_JNI             : OFF
--   INTERN_BUILD_MOBILE   : 
--   USE_ASAN              : OFF
--   USE_CUDA              : 0
--   USE_ROCM              : OFF
--   USE_EIGEN_FOR_BLAS    : 
--   USE_FBGEMM            : OFF
--     USE_FAKELOWP          : OFF
--   USE_FFMPEG            : OFF
--   USE_GFLAGS            : OFF
--   USE_GLOG              : OFF
--   USE_LEVELDB           : OFF
--   USE_LITE_PROTO        : OFF
--   USE_LMDB              : OFF
--   USE_METAL             : OFF
--   USE_MKL               : 
--   USE_MKLDNN            : OFF
--   USE_NCCL              : 0
--   USE_NNPACK            : ON
--   USE_NUMPY             : True
--   USE_OBSERVERS         : OFF
--   USE_OPENCL            : OFF
--   USE_OPENCV            : OFF
--   USE_OPENMP            : ON
--   USE_TBB               : OFF
--   USE_VULKAN            : OFF
--   USE_PROF              : OFF
--   USE_QNNPACK           : 0
--   USE_PYTORCH_QNNPACK   : 0
--   USE_REDIS             : OFF
--   USE_ROCKSDB           : OFF
--   USE_ZMQ               : OFF
--   USE_DISTRIBUTED       : 0
--   Public Dependencies  : Threads::Threads;/usr/lib/aarch64-linux-gnu/libopenblas.so
--   Private Dependencies : pthreadpool;cpuinfo;nnpack;XNNPACK;/usr/lib/aarch64-linux-gnu/libnuma.so;fp16;aten_op_header_gen;foxi_loader;rt;fmt::fmt-header-only;gcc_s;gcc;dl
CMake Warning:
  Manually-specified variables were not used by the project:
    BUILD_TORCH
    NUMPY_INCLUDE_DIR
    PYTHON_INCLUDE_DIR
    USE_GPU_HOST
    USE_GPU_TARGET
```

Summary for AArch64 using `BUILD_TORCH=ON USE_CUDA=0 BUILD_CUSTOM_PROTOBUF=OFF python3 setup.py build`:

```text
@@ -24,7 +24,13 @@
      Protobuf includes   :
      Protobuf libraries  :
    BUILD_DOCS            : OFF
-   BUILD_PYTHON          : False
+   BUILD_PYTHON          : True
+     Python version      : 3.6.9
+     Python executable   : /usr/bin/python3
+     Pythonlibs version  : 3.6.9
+     Python library      : /usr/lib/libpython3.6m.so.1.0
+     Python includes     : /usr/include/python3.6m
+     Python site-packages: lib/python3/dist-packages
    BUILD_CAFFE2_OPS      : ON
    BUILD_SHARED_LIBS     : ON
    BUILD_TEST            : True
@@ -47,8 +53,8 @@
    USE_MKLDNN            : OFF
    USE_NCCL              : 0
    USE_NNPACK            : ON
-   USE_NUMPY             : True
-   USE_OBSERVERS         : OFF
+   USE_NUMPY             : ON
+   USE_OBSERVERS         : ON
    USE_OPENCL            : OFF
    USE_OPENCV            : OFF
    USE_OPENMP            : ON
```

### Package

```
cd /apollo/pytorch.git/build/lib.linux-x86_64-3.6/torch
mkdir libtorch_cpu-1.7.0-linux-x86_64
mv include lib share libtorch_cpu-1.7.0-linux-x86_64
tar czvf libtorch_cpu-1.7.0-linux-x86_64.tar.gz libtorch_cpu-1.7.0-linux-x86_64
```

## LibTorch: GPU Build

```
rm -rf /apollo/pytorch.git/build

export USE_NCCL=0
export USE_DISTRIBUTED=0

export PYTORCH_BUILD_VERSION="1.7.0"
export PYTORCH_BUILD_NUMBER=1

export BLAS="MKL" # OpenBLAS for ARM64

# For CUDA 10.2 + PyTorch 1.6.0
export TORCH_CUDA_ARCH_LIST="3.7 5.2 6.0 6.1 7.0 7.5"
export TORCH_CUDA_ARCH_LIST="5.3 6.2 7.2"

# For CUDA 11.1
export TORCH_CUDA_ARCH_LIST="5.2 6.0 6.1 7.0 7.5 8.0 8.6+PTX"

export TORCH_NVCC_FLAGS="-Xfatbin -compress-all"

USE_CUDA=1 \
    USE_CUDNN=1 \
    USE_TENSORRT=1 \
    BUILD_CUSTOM_PROTOBUF=OFF \
    python3 setup.py build
```

Terminal Output

```bash
cmake -GNinja -DBLAS=MKL -DBUILD_CUSTOM_PROTOBUF=OFF -DBUILD_PYTHON=True -DBUILD_TEST=True -DBUILD_TORCH=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/apollo/pytorch.git/torch -DCMAKE_PREFIX_PATH=/usr/lib/python3/dist-packages -DNUMPY_INCLUDE_DIR=/usr/local/lib/python3.6/dist-packages/numpy/core/include -DPYTHON_EXECUTABLE=/usr/bin/python3 -DPYTHON_INCLUDE_DIR=/usr/include/python3.6m -DPYTHON_LIBRARY=/usr/lib/libpython3.6m.so.1.0 -DTORCH_BUILD_VERSION=1.7.0 -DUSE_CUDA=1 -DUSE_CUDNN=1 -DUSE_DISTRIBUTED=0 -DUSE_GPU_HOST=1 -DUSE_GPU_TARGET=1 -DUSE_NCCL=0 -DUSE_NUMPY=True -DUSE_TENSORRT=1 /apollo/pytorch.git
```

Summary for x86_64:

```text
-- ******** Summary ********
--   CMake version         : 3.16.8
--   CMake command         : /opt/apollo/sysroot/bin/cmake
--   System                : Linux
--   C++ compiler          : /usr/bin/c++
--   C++ compiler version  : 7.5.0
--   CXX flags             :  -Wno-deprecated -fvisibility-inlines-hidden -DUSE_PTHREADPOOL -fopenmp -DTENSORRT_VERSION_MAJOR=7 -DTENSORRT_VERSION_MINOR=2 -Wnon-virtual-dtor
--   Build type            : Release
--   Compile definitions   : TH_BLAS_MKL;ONNX_ML=1;ONNXIFI_ENABLE_EXT=1
--   CMAKE_PREFIX_PATH     : /usr/lib/python3/dist-packages;/usr/local/cuda
--   CMAKE_INSTALL_PREFIX  : /apollo/pytorch.git/torch
--   CMAKE_MODULE_PATH     : /apollo/pytorch.git/cmake/Modules;/apollo/pytorch.git/cmake/public/../Modules_CUDA_fix
--
--   ONNX version          : 1.7.0
--   ONNX NAMESPACE        : onnx_torch
--   ONNX_BUILD_TESTS      : OFF
--   ONNX_BUILD_BENCHMARKS : OFF
--   ONNX_USE_LITE_PROTO   : OFF
--   ONNXIFI_DUMMY_BACKEND : OFF
--   ONNXIFI_ENABLE_EXT    : OFF
--
--   Protobuf compiler     :
--   Protobuf includes     :
--   Protobuf libraries    :
--   BUILD_ONNX_PYTHON     : OFF
```

Summary for AArch64:


### Package

```
cd /apollo/pytorch.git/build/lib.linux-x86_64-3.6/torch
mkdir libtorch_gpu-1.7.0-cu111-linux-x86_64
mv include lib share libtorch_gpu-1.7.0-cu111-linux-x86_64
tar czvf libtorch_gpu-1.7.0-cu111-linux-x86_64.tar.gz libtorch_gpu-1.7.0-cu111-linux-x86_64
```
