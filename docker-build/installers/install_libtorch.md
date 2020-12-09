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

## Clone PyTorch Repo

```
git clone --recursive --branch v1.7.0 http://github.com/pytorch/pytorch pytorch.git
cd pytorch.git
git submodule update --init --recursive
sudo -H pip3 install -r requirements.txt
```

## LibTorch: CPU Build

### Build

```
export USE_NCCL=0
export USE_DISTRIBUTED=0

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

And Summary:

```text
-- Building with NumPy bindings
-- Not using cuDNN
-- Not using CUDA
-- Using MKLDNN
-- Not using CBLAS in MKLDNN
-- Not using NCCL
-- Building without distributed package
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

export BLAS="MKL" # OpenBLAS

# For CUDA 10.2 + PyTorch 1.6.0
export TORCH_CUDA_ARCH_LIST="3.7 5.2 6.0 6.1 7.0 7.5"

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

Summary:

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

### Package

```
cd /apollo/pytorch.git/build/lib.linux-x86_64-3.6/torch
mkdir libtorch_gpu-1.7.0-cu111-linux-x86_64
mv include lib share libtorch_gpu-1.7.0-cu111-linux-x86_64
tar czvf libtorch_gpu-1.7.0-cu111-linux-x86_64.tar.gz libtorch_gpu-1.7.0-cu111-linux-x86_64
```
