ARG L4T_VERSION=r32.4.3

FROM nvcr.io/nvidia/l4t-base:${L4T_VERSION}
LABEL version="1.2"

ENV DEBIAN_FRONTEND=noninteractive

## ===== Content of nvidia/cuda:11.0-base-ubuntu18.04 for arm64 =====
# https://gitlab.com/nvidia/container-images/cuda/
# /blob/master/dist/11.0/ubuntu18.04-arm64/base/Dockerfile

RUN apt-get update && apt-get install -y --no-install-recommends \
    gnupg2 curl ca-certificates && \
    curl -fsSL https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/sbsa/7fa2af80.pub | apt-key add - && \
    echo "deb https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/sbsa /" > /etc/apt/sources.list.d/cuda.list && \
    echo "deb https://developer.download.nvidia.com/compute/machine-learning/repos/ubuntu1804/sbsa /" > /etc/apt/sources.list.d/nvidia-ml.list && \
    apt-get purge --autoremove -y curl \
    && rm -rf /var/lib/apt/lists/*

# For libraries in the cuda-compat-* package: https://docs.nvidia.com/cuda/eula/index.html#attachment-a
RUN apt-get update && apt-get install -y --no-install-recommends \
    cuda-cudart-11-0=11.0.221-1 \
    && ln -s cuda-11.0 /usr/local/cuda && \
    rm -rf /var/lib/apt/lists/*

# Required for nvidia-docker v1
RUN echo "/usr/local/nvidia/lib" >> /etc/ld.so.conf.d/nvidia.conf && \
    echo "/usr/local/nvidia/lib64" >> /etc/ld.so.conf.d/nvidia.conf

ENV PATH /usr/local/nvidia/bin:/usr/local/cuda/bin:${PATH}
ENV LD_LIBRARY_PATH /usr/local/nvidia/lib:/usr/local/nvidia/lib64

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES compute,utility
ENV NVIDIA_REQUIRE_CUDA "cuda>=11.0"

## ===== Content of nvidia/cuda:11.0-runtime-ubuntu18.04 for arm64 =====
# https://gitlab.com/nvidia/container-images/cuda/
# /blob/master/dist/11.0/ubuntu18.04-arm64/runtime/Dockerfile
 
ENV NCCL_VERSION 2.7.8

RUN apt-get update && apt-get install -y --no-install-recommends \
    cuda-libraries-11-0=11.0.3-1 \
    libnpp-11-0=11.1.0.245-1 \
    cuda-nvtx-11-0=11.0.167-1 \
    libcublas-11-0=11.2.0.252-1 \
    libnccl2=$NCCL_VERSION-1+cuda11.0 \
    && apt-mark hold libnccl2 \
    && rm -rf /var/lib/apt/lists/*

## ===== Content of nvidia/cuda:11.0-devel-ubuntu18.04 for arm64 =====
# https://gitlab.com/nvidia/container-images/cuda/
# /blob/master/dist/11.0/ubuntu18.04-arm64/devel/Dockerfile

RUN apt-get update && apt-get install -y --no-install-recommends \
    cuda-nvml-dev-11-0=11.0.167-1 \
    cuda-command-line-tools-11-0=11.0.3-1 \
    cuda-nvprof-11-0=11.0.221-1 \
    libnpp-dev-11-0=11.1.0.245-1 \
    cuda-libraries-dev-11-0=11.0.3-1 \
    cuda-minimal-build-11-0=11.0.3-1 \
    libnccl-dev=2.7.8-1+cuda11.0 \
    libcublas-dev-11-0=11.2.0.252-1 \
    libcusparse-11-0=11.1.1.245-1 \
    libcusparse-dev-11-0=11.1.1.245-1 \
    && apt-mark hold libnccl-dev \
    && rm -rf /var/lib/apt/lists/*

ENV LIBRARY_PATH /usr/local/cuda/lib64/stubs
