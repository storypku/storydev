# How to Build Fast-DDS from Source

## Foonathan memory

```
wget https://github.com/eProsima/foonathan_memory_vendor/archive/v0.5.0.tar.gz
tar xzvf v0.5.0.tar.gz
cd foonathan_memory_vendor-0.5.0
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release  -DBUILD_SHARED_LIBS=ON 
cmake --build . --target install
```

## Fast CDR
```
wget https://github.com/eProsima/Fast-CDR/archive/v1.0.15.tar.gz
tar xzvf v1.0.15.tar.gz
mkdir build && cd build
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
sudo make install
```

## Fast DDS
```
wget https://github.com/eProsima/Fast-DDS/archive/v2.0.1.tar.gz
tar xzvf v2.0.1.tar.gz
cd Fast-DDS-2.0.1
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release \
  -DCOMPILE_EXAMPLES=OFF -DBUILD_DOCUMENTATION=OFF \
  -DBUILD_TESTING=OFF


```

```
docker pull osrf/ros2:devel
```

