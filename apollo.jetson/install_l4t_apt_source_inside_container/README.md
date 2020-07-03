# Setup L4T apt source for Jetson boards 

## Things U Should Know First
- This script is expected to run insider docker container
- `nvidia-l4t-apt-source_xxx.deb` can be found from JetPack downloads.

## How to run

```
sudo bash ./install_l4t_apt_source_inside_docker.sh
```

## How to install CUDA/CUDNN/TensorRT ...

```
sudo apt-get -y update

sudo apt-get -y install cuda-nvcc-10-2 ...

# CUDNN
sudo apt-get -y install libcudnn8 libcudnn8-dev

# TensorRT
sudo apt-get install tensorrt
```

## Where to get nvidia-l4t-apt-source_xxx.deb

```
$ tar xjvf Jetson_Linux_R32.4.2_aarch64.tbz2
$ ls -l Linux_for_Tegra/nv_tegra/l4t_deb_packages
...
nvidia-l4t-apt-source_32.4.2-20200408182620_arm64.deb
...

```
